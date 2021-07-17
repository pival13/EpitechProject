import System.Exit
import System.Environment
import Data.Time.Clock
import Data.Fixed
import Text.Printf

import Hotline

failure :: String -> IO()
failure str = do
    putStrLn str
    exitWith $ ExitFailure 84
{-
isInt :: [Char] -> Bool
isInt [] = False
isInt (x:xs) = elem x "0123456789-" && isNatural xs
where isNatural :: [Char] -> Bool
    isNatural [] = False
    isNatural (x:[]) = 
    isNatural (x:xs)
-}
isInt :: [Char] -> Bool
isInt [] = False
isInt (x:[])
    | elem x "0123456789" = True
    | otherwise = False
isInt (x:y)
    | elem x "0123456789" = isInt y
    | otherwise = False

getOverload :: [Double] -> Double
getOverload [] = 0
getOverload (x:xs)
    | length xs >= 25 = (x * 100) + getOverload xs
    | otherwise = 0

displayLaw :: [Double] -> IO()
displayLaw [] = putStrLn ""
displayLaw (x:xs)
    | (length xs) `mod` 5 == 0 = printf "\n%d -> %0.3f" (50-(length xs)) x >> displayLaw xs
    | otherwise = printf "\t%d -> %0.3f" (50-(length xs)) x >> displayLaw xs

display :: Integer -> (Integer->Integer->[Double]) -> IO ()
display x f = do
    time <- getCurrentTime
    let value = f x 0
    time2 <- getCurrentTime
    displayLaw value
    printf "Overload: %2.1f%%\n" $ 100 - getOverload value
    print (diffUTCTime time2 time)

hotline :: Integer -> IO ()
hotline x = do
        putStr "Binomial distribution:"
        display x getBinoLaw
        putStr "\nPoisson distribution:"
        display x getPoissonLaw

main :: IO ()
main = do
    args <- getArgs
    if length args == 1 && isInt (args!!0) then
        hotline (read $ (args!!0)::Integer)
    else if length args == 2 && isInt (args!!0) && isInt (args!!1) && (read $ (args!!0)::Integer) >= (read $ (args!!1)::Integer) then
        printf "%s-combinations of a set of size %s:\n%d\n" (args!!1) (args!!0) $ coefBino (read $ (args!!0)::Integer) (read $ (args!!1)::Integer)
    else
        failure "Expected one or two natural integer"