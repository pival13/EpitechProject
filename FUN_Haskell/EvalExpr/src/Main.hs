module Main where

import Lib
import Parser
import RPN
import EvalExpr

import DataType

import System.Environment

usage :: IO ()
usage = failure $ "USAGE:\n\t./funEvalExpr expression\n" ++
                "DESCRIPTION:\n" ++
                "\texpression: A valid mathematical expression.\n" ++
                "\t\tOnly the following operator are supported: + - * / ^ ()."

main :: IO ()
main = do 
    args <- getArgs
    case parserEvalExpr args of
        Nothing -> usage
        Just ast -> case evalExprRPN $ postParserRPN ast of
            Nothing -> usage
            Just nb -> putStrLn $ show $ roundAcc nb 2
