module Lib (
    isNatural, isInt, isShort, isFloat,
    readNatural, readInt, readFloat,
    roundAcc, failure, map2
) where

import Data.Char
import System.Exit

{---------------------------------
            Type Checker
---------------------------------}

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

{---------------------------------
            Type Parse
---------------------------------}

getNumberPart :: [Char] -> ([Char], [Char])
getNumberPart [] = ([],[])
getNumberPart s@(x:xs)
    | isDigit x = let (nb, str) = getNumberPart xs
                  in (x:nb,str)
    | otherwise = ([],s)

readNatural :: [Char] -> Maybe (Integer, [Char])
readNatural [] = Nothing
readNatural s@(x:_)
    | not $ isDigit x = Nothing
    | otherwise = let (nb, str) = getNumberPart s
                  in Just (read nb::Integer, str)

readInt :: [Char] -> Maybe (Integer, [Char])
readInt [] = Nothing
readInt ('-':s) = case readNatural s of
    Nothing -> Nothing
    Just (nb,str) -> Just (-nb,str)
readInt s = case readNatural s of
    Nothing -> Nothing
    Just (nb,str) -> Just (nb,str)

readFloat :: [Char] -> Maybe (Double, [Char])
readFloat [] = Nothing
readFloat ('+':s) = readFloat s
readFloat ('-':s) = case readFloat s of
    Nothing -> Nothing
    Just (nb, str) -> Just ((-nb), str)
readFloat s = case getNumberPart s of
    ([], _) -> Nothing
    (sNb,'.':str) -> case getNumberPart str of
        ([], _) -> Nothing
        (sNb2, rest) -> Just (read (sNb ++ "." ++ sNb2)::Double, rest)
    (sNb, str) -> Just (read sNb::Double, str)

{---------------------------------
            Other
---------------------------------}

roundAcc :: (RealFrac a) => a -> Int -> a
roundAcc nb 0 = fromIntegral $ round nb
roundAcc nb acc = (fromIntegral (round $ nb * 10 ^ acc + 0.01)) / 10 ^ acc

failure :: String -> IO ()
failure str = putStrLn str >>
    (exitWith $ ExitFailure 84)

map2 :: ((a, b) -> c) -> ([a], [b]) -> [c]
map2 _ ([], _) = []
map2 _ (_, []) = []
map2 f ((x:xs), (y:ys)) = ((f (x,y)):map2 f (xs,ys))