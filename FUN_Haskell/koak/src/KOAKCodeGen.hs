{-# LANGUAGE RecursiveDo #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE OverloadedStrings #-}

module KOAKCodeGen where

import           Data.Maybe
import           Data.String
import qualified Data.Map                        as Map
import           Control.Monad.State

import           LLVM.AST                        (Operand(..), Module(..))
import           LLVM.AST.Name                   (mkName)
import           LLVM.AST.Type                   as AST
import qualified LLVM.AST.IntegerPredicate       as IP
import qualified LLVM.AST.FloatingPointPredicate as FP
import qualified LLVM.AST.Constant               as C
import qualified LLVM.IRBuilder                  as IRB

import KOAKData

type Env = Map.Map String Operand
type LLVM = IRB.ModuleBuilderT (State Env)
type Codegen = IRB.IRBuilderT LLVM


addOperand :: MonadState Env m => String -> Operand -> m ()
addOperand name op = modify $ \env -> Map.insert name op env

getOperand :: MonadState Env m => String -> m Operand
getOperand name = gets $ \env -> (Map.!) env name

typeOf :: KOAKData.Type -> AST.Type
typeOf TVoid = AST.void
typeOf TInt = AST.i32
typeOf TDouble = AST.double

defaultValue :: KOAKData.Type -> Operand
defaultValue TVoid = ConstantOperand $ C.Undef AST.void
defaultValue TInt = IRB.int32 0
defaultValue TDouble = IRB.double 0

locally :: MonadState Env m => m Operand -> m Operand
locally function = get >>= (\env -> function >>= (\r -> put env >> (return r)))

boolToInt :: Codegen Operand -> Codegen Operand
boolToInt function = function >>= \r -> IRB.select r (IRB.int32 1) (IRB.int32 0)

intToBool :: Codegen Operand -> Codegen Operand
intToBool function = function >>= \r -> IRB.icmp IP.NE r (IRB.int32 0)

codegenExpr :: KOAKData.Expr -> Codegen Operand
codegenExpr (Nb i) = return $ IRB.int32 i
codegenExpr (NbF f) = return $ IRB.double f
codegenExpr (Var str) = getOperand str >>= \op -> IRB.load op 0
codegenExpr (Exprs ((expr,_):[])) = codegenExpr expr
codegenExpr (Exprs ((expr,_):exprs)) = codegenExpr expr >> codegenExpr (Exprs exprs)

codegenExpr (UnOp ope (exp, t)) = do
    exp' <- codegenExpr exp
    case ope of
        "!" -> case t of
            TInt -> boolToInt $ IRB.icmp IP.EQ exp' (IRB.int32 0)
            TDouble -> boolToInt $ IRB.fcmp FP.OEQ exp' (IRB.double 0.0)
        "-" -> case t of
            TInt -> IRB.sub (IRB.int32 0) exp'
            TDouble -> IRB.fsub (IRB.double 0) exp'
 
codegenExpr BinOp { binLft = (Var s,_), binName = "=", binRgt = (v,t) } = do
    v' <- codegenExpr v
    env <- get
    unless (Map.member s env)
        (IRB.alloca (typeOf t) Nothing 0 >>= \ptr -> addOperand s ptr)
    var <- getOperand s
    IRB.store var 0 v'
    return v'

codegenExpr BinOp { binLft = (v1, t1), binName = ope, binRgt = (v2, t2) } = do
    v1' <- codegenExpr v1
    v2' <- codegenExpr v2
    case ope of
        "==" -> boolToInt $ (selectF t1 (IRB.icmp IP.EQ) (IRB.fcmp FP.OEQ)) v1' v2'
        "!=" -> boolToInt $ (selectF t1 (IRB.icmp IP.NE) (IRB.fcmp FP.ONE)) v1' v2'
        "<" -> boolToInt $ (selectF t1 (IRB.icmp IP.SLT) (IRB.fcmp FP.OLT)) v1' v2'
        ">" -> boolToInt $ (selectF t1 (IRB.icmp IP.SGT) (IRB.fcmp FP.OGT)) v1' v2'
        "+" -> (selectF t1 (IRB.add) (IRB.fadd)) v1' v2'
        "-" -> (selectF t1 (IRB.sub) (IRB.fsub)) v1' v2'
        "*" -> (selectF t1 (IRB.mul) (IRB.fmul)) v1' v2'
        "/" -> (selectF t1 (IRB.sdiv) (IRB.fdiv)) v1' v2'
    where
        selectF TInt f _ = f
        selectF TDouble _ f = f

codegenExpr IfExpr { ifCond = (ec, _), ifThen = (et, tt), ifElse = ifelse } = mdo
    res <- intToBool $ codegenExpr ec
    IRB.condBr res thenBlock elseBlock
    thenBlock <- IRB.block `IRB.named` "then"
    thenBody <- codegenExpr et
    IRB.br endBlock
    elseBlock <- IRB.block `IRB.named` "else"
    elseBody <- case ifelse of
        Just (ee,_) -> codegenExpr ee
        Nothing -> return $ defaultValue tt
    IRB.br endBlock
    endBlock <- IRB.block `IRB.named` "end"
    IRB.phi [(thenBody,thenBlock), (elseBody,elseBlock)]

codegenExpr WhileExpr { whileCond = (ec,_), whileBody = (eb, tb) } = mdo
    IRB.br condBlock
    condBlock <- IRB.block `IRB.named` "cond"
    initCond <- intToBool $ codegenExpr ec
    IRB.condBr initCond whileBlock endBlock
    whileBlock <- IRB.block `IRB.named` "while"
    body <- codegenExpr eb
    cond <- intToBool $ codegenExpr ec
    IRB.condBr cond whileBlock endBlock
    endBlock <- IRB.block `IRB.named` "end"
    IRB.phi [
        (defaultValue tb,condBlock),
        (body,whileBlock)]

codegenExpr ForExpr { forVar = (v, (ev, tv)), forCond = (ec,_), forStep = (es,_), forBody = (eb, tb) } = mdo
    initVar <- codegenExpr ev
    var <- IRB.alloca (typeOf tv) Nothing 0
    IRB.store var 0 initVar
    addOperand v var--TODO: Do not stock on the environnement, or remove at the end
    IRB.br initCondBlock
    initCondBlock <- IRB.block `IRB.named` "initCond"
    initCond <- intToBool $ codegenExpr ec
    IRB.condBr initCond bodyBlock endBlock
    bodyBlock <- IRB.block `IRB.named` "body"
    body <- codegenExpr eb
    IRB.br headerBlock
    headerBlock <- IRB.block `IRB.named` "incr_cond"
    codegenExpr $ BinOp {
        binLft = (Var v, tv),
        binName = "=",
        binRgt = (BinOp {
            binLft = (Var v, tv),
            binName = "+",
            binRgt = (es, tv)
        }, tv)}
    cond <- intToBool $ codegenExpr ec
    IRB.condBr cond bodyBlock endBlock
    endBlock <- IRB.block `IRB.named` "end"
    IRB.phi [
        (defaultValue tb,initCondBlock),
        (body,headerBlock)]

codegenExpr KOAKData.Call { callName = name, callArgs = args } = do
    function <- getOperand name
    args' <- (\(e,_) -> codegenExpr e) `mapM` args
    IRB.call function $ (\arg -> (arg,[])) `map` args'


codegen :: KOAKData.Kdefs -> LLVM ()
codegen (Expression exp ty) = mdo
    addOperand "main" function
    function <- locally $ IRB.function (mkName "main") [] AST.i32
        (\_ -> IRB.block `IRB.named` "entry" >> codegenExpr exp >>= (\r -> printOperand r))
    return ()
    where
        printOperand ope = case ty of
            TVoid -> IRB.ret (IRB.int32 0)
            TInt -> do
                printf <- getOperand "printf"
                s <- IRB.globalStringPtr "%d\n" "s"
                IRB.call printf [(ConstantOperand s,[]),(ope,[])]
                IRB.ret (IRB.int32 0)
            TDouble -> do
                printf <- getOperand "printf"
                s <- IRB.globalStringPtr "%g\n" "s"
                IRB.call printf [(ConstantOperand s,[]),(ope,[])]
                IRB.ret (IRB.int32 0)

codegen Function { functName = name, functArgs = args, functReturn = ret, functBody = body } = mdo
    addOperand name function
    function <- locally $ do
        args <- mapM (\(n,t) -> pure (typeOf t, IRB.ParameterName $ fromString n)) args
        IRB.function (mkName name) args (typeOf ret) genBody
    return ()
        where
            genBody :: [Operand] -> Codegen ()
            genBody ops = do
                _entry <- IRB.block `IRB.named` "entry"
                forM_ (zip ops args) $ \(op, (n, t)) -> do
                    addr <- IRB.alloca (typeOf t) Nothing 0
                    IRB.store addr 0 op
                    addOperand n addr
                v <- codegenExpr body
                case ret of
                    TVoid -> IRB.retVoid
                    _ -> IRB.ret v


koakCodeGen :: KOAKData.AST -> Module
koakCodeGen ast = evalState (IRB.buildModuleT "koak" (
        IRB.externVarArgs (mkName "printf") [AST.ptr AST.i8] AST.i32 >>= 
        \printf -> addOperand "printf" printf >>
        mapM_ codegen ast
    )) Map.empty