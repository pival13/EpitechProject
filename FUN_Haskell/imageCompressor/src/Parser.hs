module Parser (
    extractDataFile
) where

import Lib
import DataType

import Data.List

lineToPoint :: String -> Maybe PointColor
lineToPoint l
    | length (words l) /= 2 || length position /= 2 || length color /= 3
        || not (all isInt position) || not (all isShort color) = Nothing
    | otherwise = Just PointColor { x = read (position!!0)::Integer
                                  , y = read (position!!1)::Integer
                                  , color = Color { r = read (color!!0)::Integer
                                                  , g = read (color!!1)::Integer
                                                  , b = read (color!!2)::Integer
                                                  }
                                  }
        where position = words $ map (\c -> if c == ',' then ' ' else c) $ ((words l) !! 0) \\ "()"
              color = words $ map (\c -> if c == ',' then ' ' else c) $ ((words l) !! 1) \\ "()"

extractDataFile :: [String] -> Maybe [PointColor]
extractDataFile [] = Just []
extractDataFile (x:xs) = case (lineToPoint x) of
    Nothing -> Nothing
    Just pt -> case (extractDataFile xs) of
        Nothing -> Nothing
        Just pts -> Just (pt:pts)
