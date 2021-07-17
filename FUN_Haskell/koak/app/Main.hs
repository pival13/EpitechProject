{-# LANGUAGE OverloadedStrings #-}

module Main where

import Prelude hiding     (putStr)
import Data.ByteString    (ByteString(..), putStr)
import System.Environment
import System.Exit

import LLVM.AST           (Module(..))
import LLVM.Context       (withContext)
import LLVM.Module        (withModuleFromAST, moduleLLVMAssembly)

import KOAKParser         (parseKoak)
import KOAKVerifier       (koakCheckAST)
import KOAKCodeGen        (koakCodeGen)


toLLVM :: Module -> IO ByteString
toLLVM mod = withContext $ \ctx -> withModuleFromAST ctx mod moduleLLVMAssembly

getFilesOutput :: IO ([String], String)
getFilesOutput = getArgs >>= (\args -> parseArgs args "a.out")
    where
        parseArgs :: [String] -> String -> IO ([String], String)
        parseArgs [] output = return ([], output)
        parseArgs ("-o":f:fs) _ = parseArgs fs f
        parseArgs (f:fs) out = parseArgs fs out >>= \(args,out') -> return (f:args, out')

main :: IO ()
main = getFilesOutput >>= (
    \(args, out) -> case args of
        [] -> putStrLn "Error: No argument provided" >> (exitWith $ ExitFailure 84)
        (f:fs) -> readFile f >>= (
            \content -> case parseKoak content of
                Just (ast, []) -> case koakCheckAST ast of
                    Left err -> putStrLn ("Error: " <> err) >> (exitWith $ ExitFailure 84)
                    Right ast' -> toLLVM (koakCodeGen ast') >>= (\bs -> putStr bs >> putStrLn "")
                Nothing -> putStrLn "Error: Fail to parse" >> (exitWith $ ExitFailure 84)
                Just (_, s) -> putStrLn ("Error: Fail to parse from " <> take 20 s <> "...") >> (exitWith $ ExitFailure 84)))