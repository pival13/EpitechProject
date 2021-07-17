module Main where

import Control.Exception  (bracket)
import System.Posix.Temp  (mkdtemp, mkstemps)
import System.Directory   (removePathForcibly, withCurrentDirectory)
import System.Process     (callProcess)

import LLVM.AST           (Module(..))
import LLVM.Context       (withContext)
import LLVM.Target        (withHostTargetMachineDefault)
import LLVM.Module        (withModuleFromAST, writeObjectToFile, File(..))

import KOAKParser         (parseKoak)
import KOAKVerifier       (koakCheckAST)
import KOAKCodeGen        (koakCodeGen)

import System.Environment
import System.Exit

compile :: Module -> FilePath -> IO ()
compile llvmModule outfile =
    -- bracket :: IO a -> (a -> IO b) -> (a -> IO c) -> IO c
    -- Usually used to create ressource, destroy them at the end, and do some things inbetween
    bracket (mkdtemp "build") removePathForcibly (
        \buildDir -> withCurrentDirectory buildDir (withContext (
            \ctx -> withHostTargetMachineDefault (
                \machine -> withModuleFromAST ctx llvmModule (
                    \mod -> writeObjectToFile machine (File "output.o") mod))) >>
            callProcess "clang" ["-Wno-override-module", "-lm", "output.o", "-o", "../" <> outfile]))

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
                    Right ast' -> compile (koakCodeGen ast') out
                Nothing -> putStrLn "Error: Fail to parse" >> (exitWith $ ExitFailure 84)
                Just (_, s) -> putStrLn ("Error: Fail to parse from " <> take 20 s <> "...") >> (exitWith $ ExitFailure 84)))
