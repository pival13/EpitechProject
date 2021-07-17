    {-# LANGUAGE FlexibleContexts #-}

module KOAKVerifier where

import Control.Monad.Except
import Control.Monad.State
import Data.Maybe
import qualified Data.Map as Map

import KOAKData


type Vars = Map.Map String Type
type Functs = Map.Map String Kdefs

type Env = (Vars, Functs)
type Checker = ExceptT String (State Env)

locally :: MonadState Env map => map a -> map a
locally function = get >>= (\env -> function >>= (\r -> put env >> (return r)))

tryInsertVar :: String -> Type -> Checker ()
tryInsertVar name TVoid = throwError "Illegal void type variable"
tryInsertVar name t = gets fst >>= (\vs -> case Map.lookup name vs of
    Nothing -> modify (\(var, fs) -> (Map.insert name t var, fs))
    Just tSave -> unless (t == tSave) (throwError "Assignation with a different type"))

tryInsertFunction :: Kdefs -> Checker Kdefs
tryInsertFunction f =
    gets snd >>= (\fs ->
    when (Map.member (functName f) fs)
        (throwError $ "Redefinition of function " <> (functName f))) >>
    (if (functReturn f) == TUndef || any (\(_, t) -> t == TUndef) (functArgs f)
    then modify (\(vs, fs) -> (vs, Map.insert (functName f) f fs))
    else checkFunct (functBody f) (functArgs f) >>= (\(body, t) ->
        unless (t == functReturn f)
            (throwError "") >>
        modify (\(vs, fs) -> (vs, Map.insert (functName f) (f { functBody = body }) fs)))) >> 
    return f
        where
            checkFunct exp proto = 
                mapM (\(a, b) -> tryInsertVar a b) proto >>
                modify (\(vs, fs) -> (vs, Map.insert (functName f) f fs)) >>
                checkerExpr exp >>= (\e ->
                modify (\(vs, fs) -> (vs, Map.delete (functName f) fs)) >> return e)

checkerExpr :: Expr -> Checker (Expr, Type)
checkerExpr (Nb n) = return (Nb n, TInt)
checkerExpr (NbF n) = return (NbF n, TDouble)

checkerExpr (Var s) = gets fst >>= (\vs -> case Map.lookup s vs of
    Nothing -> throwError $ "Undefined variable " <> s
    Just t -> return (Var s, t))

checkerExpr (Exprs exprs) = mapM (\(expr, _) -> checkerExpr expr) exprs >>= (
    \exprs' -> return (Exprs exprs', snd $ last exprs'))

checkerExpr unop@(UnOp {}) = checkerExpr (fst $ unArg unop) >>= (\(e,t) ->
    when (t == TVoid)
        (throwError "Cannot execute operation on void") >>
    return (unop { unArg = (e,t) }, t))

checkerExpr BinOp { binLft = (Var s, _), binName = "=", binRgt = (e, _) } =
    checkerExpr e >>= (\(e', t) ->
    tryInsertVar s t >>
    return (BinOp { binLft = (Var s, t), binName = "=", binRgt = (e', t) }, t))
checkerExpr BinOp { binName = "=" } = throwError "Cannot assign to a non-variable"

checkerExpr BinOp { binLft = (e1,_), binName = ope, binRgt = (e2,_) } =
    checkerExpr e1 >>= (\(e1', t1) ->
    checkerExpr e2 >>= (\(e2', t2) -> 
    when (t1 == TVoid)
        (throwError "Cannot execute operation on void") >>
    unless (t1 == t2)
        (throwError "Operands don't have the same type") >>
    return (BinOp {
        binLft = (e1', t1),
        binName = ope,
        binRgt = (e2', t2)
    }, if ope `elem` ["==","!=","<",">"] then TInt else t1)))

checkerExpr IfExpr { ifCond = (ec,_), ifThen = (et,_), ifElse = ifelse } =
    checkerExpr ec >>= (\(eCond, tCond) ->
    unless (tCond == TInt)
        (throwError "Wrong condition type") >>
    checkerExpr et >>= (\(eThen, tThen) ->
    case ifelse of
        Nothing -> return (IfExpr {
                ifCond = (eCond, tCond),
                ifThen = (eThen, tThen),
                ifElse = Nothing
            }, tThen)
        Just (ee, _) -> checkerExpr ee >>= (\(eElse, tElse) ->
            unless (tElse == tThen)
                (throwError "Branches return types differ") >>
            return (IfExpr {
                ifCond = (eCond, tCond),
                ifThen = (eThen, tThen),
                ifElse = Just (eElse, tElse)
            }, tThen))))

checkerExpr WhileExpr { whileCond = (ec,_), whileBody = (eb,_) } =
    checkerExpr ec >>= (\(eCond, tCond) ->
    unless (tCond == TInt)
        (throwError "Wrong condition type") >>
    checkerExpr eb >>= (\(e, t) ->
    return (WhileExpr {
        whileCond = (eCond, tCond),
        whileBody = (e, t)
    }, t)))

checkerExpr ForExpr { forVar = (v, (ev,_)), forCond = (ec,_), forStep = (es,_), forBody = (eb,_) } =
    checkerExpr ev >>= (\(eInit, tInit) ->
    locally (do
        tryInsertVar v tInit
        (eCond, tCond) <- checkerExpr ec
        unless (tCond == TInt)
            (throwError "Wrong condition type")
        (eStep, tStep) <- checkerExpr es
        unless (tInit == tStep)
            (throwError "Invalid incremental type")
        (eBody, tBody) <- checkerExpr eb
        return (ForExpr {
            forVar = (v, (eInit, tInit)),
            forCond = (eCond, tCond),
            forStep = (eStep, tStep),
            forBody = (eBody, tBody)
        }, tBody)))

checkerExpr Call { callName = name, callArgs = args } =
    gets snd >>= (\fs ->
    case Map.lookup name fs of
        Nothing -> throwError $ "Undefined function: " <> name
        Just f@(Function { functArgs = fargs, functReturn = fret, functBody = body }) -> do
            unless (length args == length fargs)
                (throwError $ "Invalid number of arguments for " <> name <> ": expected " <> show (length fargs) <> ", got " <> show (length args))
            args <- mapM checkerExpr (fst $ unzip args)
            proto' <- zipWithM convertToProto fargs args
            if fret == TUndef || any (\(_, t) -> t == TUndef) fargs
            then
                checkFunct f proto' >>= (\(e, t) ->
                unless (fret == TUndef || fret == t)
                    (throwError "Return type differ") >>
                modify (\(vs, fs) -> (vs, Map.adjust (\fun -> fun { functArgs = proto', functReturn = t, functBody = e }) name fs)) >>
                return (Call { callName = name, callArgs = args }, t))
            else
                return (Call { callName = name, callArgs = args }, fret))
    where
        checkFunct f proto =
            mapM (\(a, b) -> tryInsertVar a b) proto >>
            modify (\(vs, fs) -> (vs, Map.delete (functName f) fs)) >>
            checkerExpr (functBody f) >>= (\e ->
            modify (\(vs, fs) -> (vs, Map.insert (functName f) f fs)) >> return e)
        convertToProto (s, t) (_, t') = unless (t == TUndef || t == t')
                (throwError $ "Invalid argument type") >>
            return (s, t')


checkerUndef :: AST -> Checker AST
checkerUndef [] = return []
checkerUndef (f@(Function {}):rest) =
    gets snd >>= (\fs ->
    let f' = fs Map.! (functName f) 
    in
        when ((functReturn f') == TUndef || any (\(_, t) -> t == TUndef) (functArgs f'))
            (throwError $ "Function " <> functName f <> " has unknow type") >>
        checkerUndef rest >>= (\ast -> return (f':ast)))
checkerUndef (Expression e TUndef:rest) = throwError $ "An expression remain undetermined"
checkerUndef (e:rest) = checkerUndef rest >>= (\ast -> return (e:ast))

checkerAST :: AST -> Bool -> Checker AST
checkerAST [] True = pure [] 
checkerAST [] False = throwError "Cannot compile a file with only functions definitions"
checkerAST (Function {}:_) True = throwError $ "Functions cannot be defined after an expression"
checkerAST (f@(Function {}):r) False = tryInsertFunction f >>= (\kdef ->
    checkerAST r False >>= \kdefs ->
    return (kdef:kdefs))
checkerAST ((Expression e _):[]) _ = checkerExpr e >>= \(e', t') -> return [Expression (Exprs [(e', t')]) t']
checkerAST ((Expression e _):r) _ = checkerExpr e >>= \(e', t') ->
    checkerAST r True >>= \[Expression (Exprs es) _] ->
    return [Expression (Exprs ((e', t'):es)) t']

koakCheckAST :: AST -> Either String AST
koakCheckAST [] = Left "Empty file"
koakCheckAST ast = evalState (runExceptT $ checkerAST ast False >>= checkerUndef) (Map.empty, Map.empty)