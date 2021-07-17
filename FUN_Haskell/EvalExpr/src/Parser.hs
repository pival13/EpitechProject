module Parser (
    parserEvalExpr
) where

import Lib
import DataType

import Control.Exception
import Data.List
import Data.Char
import Data.String

trimExpr :: [Char] -> [Char]
trimExpr [] = []
trimExpr s@(c:[])
    | isSpace c = []
    | otherwise = s
trimExpr s@(c:subs@(c2:rest))
    | isDigit c && isSpace c2 = case trimExpr rest of
        [] -> [c]
        s2@(c3:_) -> if isDigit c3
            then (c:c2:s2)
            else (c:s2)
    | isSpace c = trimExpr subs
    | otherwise = (c:trimExpr subs)
--trimExpr s = concat $ words s

combineAndEnclose :: [EvalExprNode] -> [EvalExprNode] -> EvalExprAST
combineAndEnclose ast1 ast2 = [Right ParI] ++ ast1 ++ ast2 ++ [Right ParO]

readNumber :: [Char] -> Maybe ([EvalExprNode], [Char])
readNumber expr@('(':_) = parseParenthEvalExpr expr
readNumber ('-':expr@('(':_)) = case parseParenthEvalExpr expr of
    Nothing -> Nothing
    Just (ast, rest) -> Just ((Right Minus):ast, rest)
readNumber s = case readFloat s of
    Nothing -> Nothing
    Just (nb, rest) -> Just ((Left nb):[], rest)

readOperator :: [Char] -> Maybe (Operator, [Char])
readOperator [] = Nothing
readOperator ('(':xs) = Just (ParI, xs)
readOperator (')':xs) = Just (ParO, xs)
readOperator (x:xs)
    | isOperator x = Just (toOperator x, xs)
    | otherwise = Nothing

readOpeNbs :: [Char] -> Maybe ([EvalExprNode], [Char])
readOpeNbs [] = Nothing
readOpeNbs s@(')':_) = Just ([], s)
readOpeNbs s@('(':_) = readOpeNbs ('*':s)
readOpeNbs (x:xs)
    | not $ isOperator x = Nothing
    | otherwise = case readNumber xs of
        Nothing -> Nothing
        Just (ast, rest) -> case readOpeNbs rest of
            Nothing -> Nothing
            Just (ast2, rest2) -> Just ([Right $ toOperator x] ++ ast ++ ast2, rest2)

parseParenthEvalExpr :: [Char] -> Maybe (EvalExprAST, [Char])
parseParenthEvalExpr ('(':expr) = case readNumber expr of
    Nothing -> Nothing
    Just (astNb, rest) -> case readOpeNbs rest of
        Nothing -> Nothing 
        Just (ast, ')':rest2) -> Just (combineAndEnclose astNb ast, rest2)
        Just _ -> Nothing
parseParenthEvalExpr _ = Nothing

parserEvalExpr :: [String] -> Maybe EvalExprAST
parserEvalExpr (expr:[]) = case parseParenthEvalExpr $ "(" ++ trimExpr expr ++ ")" of
    Nothing -> Nothing
    Just (ast, []) -> Just ast
    Just _ -> Nothing 
parserEvalExpr _ = Nothing
