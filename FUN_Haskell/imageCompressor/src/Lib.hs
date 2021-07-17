module Lib where

import Data.Char
import System.Exit

failure :: String -> IO ()
failure str = do
    putStrLn str
    exitWith $ ExitFailure 84

isNatural :: [Char] -> Bool
isNatural [] = False
isNatural (x:[]) = isDigit x
isNatural (x:xs) = isDigit x && isNatural xs

isInt :: [Char] -> Bool
isInt [] = False
isInt ('-':xs) = isNatural xs
isInt x = isNatural x

isShort :: [Char] -> Bool
isShort x = any (\n -> x == show n) [0..255]

isUFloat :: [Char] -> Bool
isUFloat [] = False
isUFloat ('.':xs) = isNatural xs
isUFloat (x:[]) = isDigit x
isUFloat (x:xs) = isDigit x && isUFloat xs

isFloat :: [Char] -> Bool
isFloat [] = False
isFloat ('-':xs) = isUFloat xs
isFloat x = isUFloat x

map2 :: ((a, b) -> c) -> ([a], [b]) -> [c]
map2 _ ([], _) = []
map2 _ (_, []) = []
map2 f ((x:xs), (y:ys)) = ((f (x,y)):map2 f (xs,ys))