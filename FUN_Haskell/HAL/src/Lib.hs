module Lib where

dotNumber :: String -> Int -> Int
dotNumber [] nbr = nbr
dotNumber ('.':xs) nbr = dotNumber xs (nbr + 1)
dotNumber (_:xs) nbr = dotNumber xs nbr

isNumberFloat :: String -> Int -> Bool -> Int -> Bool
isNumberFloat [] 1 True _ = False
isNumberFloat [] _ _ _ = True
isNumberFloat ('.':xs) 0 _ nbr = isNumberFloat xs 1 False nbr
isNumberFloat ('-':xs) 0 _ nbr = isNumberFloat xs 1 True nbr
isNumberFloat (x:xs) _ isneg nbr
    | nbr > 1 = False
    | x `notElem` ['0'..'9'] && x /= '.' = False
    | otherwise = isNumberFloat xs 2 isneg 0
