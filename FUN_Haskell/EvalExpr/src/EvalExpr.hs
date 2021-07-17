module EvalExpr (
    evalExpr,
    evalExprRPN
) where

import Lib
import DataType

import GHC.Exts
import Data.List
import Data.Either

evalNeg :: [EvalExprNode] -> EvalExprAST
evalNeg (Left nb:rest) = (Left (-nb):rest)
evalNeg nb@(Right ParI:_) = evalNeg $ evalParenth nb

evalAdd :: Double -> [EvalExprNode] -> EvalExprAST
evalAdd nb1 (Left nb2:rest@(Right ope:rest2))
    | ope > Plus = evalAdd nb1 $ evalOpe ope nb2 rest2
    | otherwise = (Left (nb1 + nb2):rest)

evalMult :: Double -> [EvalExprNode] -> EvalExprAST
evalMult nb1 (Left nb2:rest@(Right ope:rest2))
    | ope > Mult = evalMult nb1 $ evalOpe ope nb2 rest2
    | otherwise = (Left (nb1 * nb2):rest)

evalDiv :: Double -> [EvalExprNode] -> EvalExprAST
evalDiv nb1 (Left nb2:rest@(Right ope:rest2))
    | ope > Div = evalDiv nb1 $ evalOpe ope nb2 rest2
    | otherwise = (Left (nb1 / nb2):rest)

evalPow :: Double -> [EvalExprNode] -> EvalExprAST
evalPow nb1 (Left nb2:rest@(Right ope:rest2))
    | ope >= Pow = evalPow nb1 $ evalOpe ope nb2 rest2
    | otherwise = (Left (nb1 ** nb2):rest)

evalOpe :: Operator -> Double -> [EvalExprNode] -> EvalExprAST
evalOpe ope nb exp@(Right ParI:_) = evalOpe ope nb $ evalParenth exp
evalOpe ope nb exp@(Right Minus:_) = evalOpe ope nb $ evalNeg exp
evalOpe Plus nb exp = evalAdd nb exp
evalOpe Minus nb exp = evalAdd nb $ evalNeg exp
evalOpe Mult nb exp = evalMult nb exp
evalOpe Div nb exp = evalDiv nb exp
evalOpe Pow nb exp = evalPow nb exp

evalParenth :: [EvalExprNode] -> EvalExprAST
-- ( nb ) .*
evalParenth (Right ParI:nb@(Left _):Right ParO:rest) = (nb:rest)
-- ( ( .*
evalParenth (Right ParI:newExp@(Right ParI:_)) = evalParenth (Right ParI:evalParenth newExp)
-- ( - .*
evalParenth (Right ParI:Right Minus:rest) = evalParenth (Right ParI:evalNeg rest)
-- ( nb ope .*
evalParenth (Right ParI:Left nb:Right ope:rest) = evalParenth (Right ParI:evalOpe ope nb rest)

evalExpr :: EvalExprAST -> Maybe Double
evalExpr [] = Just 0.0
evalExpr expr@((Right ParI):_) = case evalParenth expr of
    (Left nb):[] -> Just nb
    _ -> Nothing

evalRPN :: EvalExprAST -> EvalExprAST
evalRPN ast = if nb2 == 0 && ope == Div
    then (Left nb1:Left nb2:Right ope:[])
    else left ++ (init $ evalOpe ope nb1 (Left nb2:Right ParO:[])) ++ right
        where (Just ite) = findIndex (\elem -> isRight elem) ast
              (left, (Left nb1:Left nb2:Right ope:right)) = (take (ite-2) ast, drop (ite-2) ast)

evalExprRPN :: EvalExprAST -> Maybe Double
evalExprRPN [] = Nothing
evalExprRPN (Left nb:[]) = Just nb
evalExprRPN (Left _:Left 0:Right Div:_) = Nothing
evalExprRPN expr = evalExprRPN $ evalRPN expr