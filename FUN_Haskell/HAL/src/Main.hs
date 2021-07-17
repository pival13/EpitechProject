module Main where

import Parser
import HALData
import HALParser
import HALLexer

import System.Environment
import System.Exit
import Control.Exception
import GHC.IO.Handle
import GHC.IO.Handle.FD
import Data.Char

failure :: String -> IO a
failure s = hPutStr stderr (s ++ "\n") >> exitWith (ExitFailure 84)

execExprHAL :: Expr -> SymbolTable -> IO SymbolTable
execExprHAL expr global = case execHAL expr global [] of
    (global', NoReturn) -> pure global'
    (global', e) -> print e >> pure global'

parseFileHAL :: String -> String -> SymbolTable -> IO SymbolTable
parseFileHAL filename file global = case parse parseExpr file of
    Just (expr, s) -> execExprHAL expr global >>= (\global' ->
        if s == [] || all isSpace s
            then pure global'
            else parseFileHAL filename s global')
    _ -> failure ("Failed to parse file " ++ filename ++ ".")

readStandartInputHAL :: String -> SymbolTable -> IO SymbolTable
readStandartInputHAL s global = putStr (if s == "" then ">>> " else "... ") >> hFlush stdout >> getLine
    >>= (\s' -> case parse parseExpr (s ++ s') of
        Nothing -> readStandartInputHAL (s ++ s' ++ "\n") global
        Just (expr, []) -> execExprHAL expr global
        _ -> hPutStr stderr ("Invalid input\n") >> readStandartInputHAL "" global)

tryParseAllFileHAL :: [String] -> SymbolTable -> IO SymbolTable
tryParseAllFileHAL [] _ = failure "No argument provided"
tryParseAllFileHAL args@("-i":[]) global = (readStandartInputHAL "" global)
    `catch` (\e -> case (fromException e) :: Maybe IOException of
        Just _ -> putStrLn "" >> exitWith ExitSuccess
        _ -> case (fromException e) :: Maybe ExitCode of
            Just c -> exitWith (c)
            _ -> hPutStr stderr ("Exception: " ++ (show (e :: SomeException)) ++ "\n") >>
                tryParseAllFileHAL args global
    ) >>= (\global' -> tryParseAllFileHAL args global')
tryParseAllFileHAL (arg:rest) global = (readFile arg)
    `catch` (\e ->
        failure ("Failed to read file " ++ arg ++ ": " ++ (show (e :: IOException)))
    ) >>= (\file ->
        (parseFileHAL arg file global)
        `catch` (\e ->
            case (fromException e) :: Maybe ExitCode of
                Just c -> exitWith (c)
                _ -> failure ("Exception: " ++ (show (e :: SomeException)))
        ) >>= (\global' -> if rest == []
            then pure global'
            else tryParseAllFileHAL rest global'
        )
    )

main :: IO()
main = getArgs >>= \args -> tryParseAllFileHAL args initialGlobTable >> exitWith ExitSuccess