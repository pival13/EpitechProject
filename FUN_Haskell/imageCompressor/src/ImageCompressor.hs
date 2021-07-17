module ImageCompressor (
    compressImage
) where

import DataType
import Lib

import System.Random
import Data.List

compressImage :: Int -> Float -> [PointColor] -> StdGen -> String
compressImage 1 _ pixel _ = exportImage ([createAverage (pixel, Color {r=0,g=0,b=0})], [pixel])
compressImage n d pixel seed = exportImage (compressLoop d (firstRandomColor n (randomRs (0,255) seed)) pixel)

firstRandomColor :: Int -> [Integer] -> [Color]
firstRandomColor 0 _ = []
firstRandomColor n (r:g:b:list) = (Color {r=r,g=g,b=b}:firstRandomColor (n-1) list)

compressLoop :: Float -> [Color] -> [PointColor] -> ([Color], [[PointColor]])
compressLoop d ave pts
    | all (<d) (map (\i -> distColor (ave!!i) (newAve!!i)) [0..length ave-1]) = (newAve, group)
    | otherwise = compressLoop d newAve pts
        where group = groupColor ave pts
              newAve = map2 createAverage (group, ave)

groupColor :: [Color] -> [PointColor] -> [[PointColor]]
groupColor colors [] = map (\c -> []) colors
groupColor colors (pt:pts) = take index arr ++ [(pt:arr!!index)] ++ drop (index+1) arr
    where arr = groupColor colors pts
          index = indexCloser colors pt

indexCloser :: [Color] -> PointColor -> Int
indexCloser (color:colors) pt = head $ elemIndices (foldl (closerColor pt) color colors) (color:colors)

createAverage :: ([PointColor], Color) -> Color
createAverage ([], c) = c
createAverage (v, _) = divColor (foldl addColor (Color {r=0,g=0,b=0}) $ map color v) $ fromInteger $ toInteger $ length v

exportImage :: ([Color], [[PointColor]]) -> String
exportImage ([], _) = ""
exportImage ((c:cs), ([]:pts)) = "--\n(0,0,0)\n-\n" {-++ (show c) ++ "\n-\n"-} ++ exportImage (cs, pts)
exportImage ((c:cs), (pt:pts)) = "--\n" ++ (show c) ++ "\n-\n"
    ++ (foldl (\s s2 -> s ++ "\n" ++ (show s2)) (show $ head pt) (tail pt)) ++ "\n"
    ++ exportImage (cs, pts)