module Dannon
    ( dannon
    ) where

selectionSort :: [Double] -> Int
selectionSort [] = 0
selectionSort l = (length l) * ((length l) - 1) `div` 2

insertionSort :: [Double] -> [Double] -> Int
insertionSort [] _ = 0
insertionSort (v:vs) [] = insertionSort vs [v]
insertionSort (v:vs) arr
    | bigger == arr = (length arr) + (insertionSort vs (v:arr))
    | otherwise = (length bigger) + 1 + (insertionSort vs (v:arr))
    where bigger = filter (\n -> n <= v) arr

bubbleSort :: [Double] -> Int
bubbleSort [] = 0
bubbleSort l = (length l) * ((length l) - 1) `div` 2

quickSort :: [Double] -> Int
quickSort [] = 0
quickSort (_:[]) = 0
quickSort (v:vs) = quickSort small + quickSort big + length vs
    where small = filter (\n -> n < v) vs
          big = filter (\n -> n >= v) vs

mergeSort :: [Double] -> Int
mergeSort [] = 0
mergeSort (_:[]) = 0
mergeSort l = mergeSort left + mergeSort right + length l - max idxLeft idxRight
    where left = fst $ splitAt ((length l) `div` 2) l
          right = snd $ splitAt ((length l) `div` 2) l
          idxRight = length $ filter (\n -> n >= (maximum left)) right
          idxLeft = length $ filter (\n -> n >= (maximum right)) left

dannon :: [Double] -> IO()
dannon list = putStrLn $ (show $ length list) ++ (plural " element" $ length list) ++ "\n" ++
    "Selection sort: " ++ (show $ selectionSort list) ++ (plural " comparison" $ selectionSort list) ++ "\n" ++
    "Insertion sort: " ++ (show $ insertionSort list []) ++ (plural " comparison" $ insertionSort list []) ++ "\n" ++
    "Bubble sort: " ++ (show $ bubbleSort list) ++ (plural " comparison" $ bubbleSort list) ++ "\n" ++
    "Quicksort: " ++ (show $ quickSort list) ++ (plural " comparison" $ quickSort list) ++ "\n" ++
    "Merge sort: " ++ (show $ mergeSort list) ++ (plural " comparison" $ mergeSort list)
    where plural str size | size == 1 = str
                          | otherwise = str ++ "s"