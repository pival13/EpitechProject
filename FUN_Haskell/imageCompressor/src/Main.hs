module Main where

import Lib
import ImageCompressor
import Parser

import System.Exit
import System.Environment
import System.Random
import Control.Exception

parser :: [String] -> IO ()
parser args
    | length args /= 3 = failure "3 arguments expected"
    | not (isNatural (args!!0)) || (read (args!!0)::Int) > 256 = failure "First argument must be between 0 and 256"
    | not (isUFloat (args!!1)) = failure "Second argument must be a positive number"
    | otherwise = do
        result <- try (readFile $ args!!2) :: IO (Either SomeException String)
        case result of
            Left _ -> failure "Third argument must be a readable file"
            Right file -> case (extractDataFile $ lines file) of
                Nothing -> failure "File is wrongly written"
                Just datas -> do
                    seed <- newStdGen
                    putStr $ compressImage (read (args!!0)::Int) (read ("0"++(args!!1))::Float) datas seed

main :: IO ()
main = do 
    args <- getArgs
    parser args
