import System.Exit
import System.Environment

myElem :: Eq a => a -> [a] -> Bool
myElem n [] = False
myElem n (x:y)
    | n == x = True
    | otherwise = myElem n y

safeDiv :: Int -> Int -> Maybe Int
safeDiv x 0 = Nothing
safeDiv x y = Just (x `div` y)

safeNth :: [a] -> Int -> Maybe a
safeNth (x:y) n
    | n < 0 || n >= length (x:y) = Nothing
    | otherwise = Just ((x:y) !! n)

safeSucc :: Maybe Int -> Maybe Int
safeSucc x = succ <$> x

myLookUp :: Eq a => a -> [(a,b)] -> Maybe b
myLookUp x [] = Nothing
myLookUp x ((a,b):y)
    | x == a = Just b
    | otherwise = myLookUp x y

maybeDo :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
maybeDo funct _ Nothing = Nothing
maybeDo funct Nothing _ = Nothing
maybeDo funct (Just x) (Just y) = Just (funct x y)

isInt :: [Char] -> Bool
isInt [] = False
isInt (x:[])
    | myElem x "0123456789" = True
    | otherwise = False
isInt (x:y)
    | myElem x "-0123456789" = isInt y
    | otherwise = False

readInt :: [Char] -> Maybe Int
readInt x
    | isInt x = Just (read x::Int)
    | otherwise = Nothing

getLineLength :: IO Int
getLineLength = length <$> getLine

printAndGetLength :: String -> IO Int
printAndGetLength str = do
    putStrLn str
    pure $ length str

createBorder :: Int -> String
createBorder 1 = "+"
createBorder x = '-':(createBorder $ x-1)

createBorderMiddle :: Int -> String
createBorderMiddle 0 = "|"
createBorderMiddle x = "  " ++ (createBorderMiddle (x-1))

drawVertLine :: Int -> Int -> IO ()
drawVertLine x y
    | x < 3 = return ()
    | otherwise = do
        putStrLn ('|':(createBorderMiddle (y-1)))
        drawVertLine (x-1) y

printBox :: Int -> IO ()
printBox x
    | x <= 0 = return ()
    | otherwise = do
    putStrLn $ (reverse (createBorder x)) ++ (createBorder x)
    drawVertLine x x
    putStrLn $ (reverse (createBorder x)) ++ (createBorder x)

concatLines :: Int -> IO String
concatLines x 
    | x <= 0 = return ""
    | otherwise = do
    str <- getLine
    str2 <- concatLines (x-1)
    return (str ++ str2)

getInt :: IO (Maybe Int)
getInt = do
    str <- getLine
    pure $ readInt str

main :: IO ()
main = do
    args <- getArgs
    if (length args) /= 3 || isInt (args!!2) == False || isInt (args!!0) == False || myElem (args!!1) ["+","-","*","/","%"] == False then
        exitWith (ExitFailure 84)
    else
        case args!!1 of
            "+" -> print $ (read $ args!!0) + (read $ args!!2)
            "-" -> print $ (read $ args!!0) - (read $ args!!2)
            "/" -> do
                if (read $ args!!2) == 0 then
                    exitWith (ExitFailure 84)
                else
                    print $ (read $ args!!0) `div` (read $ args!!2)
            "*" -> print $ (read $ args!!0) * (read $ args!!2)
            "%" -> do
                if (read $ args!!2) == 0 then
                    exitWith (ExitFailure 84)
                else
                    print $ (read $ args!!0) `mod` (read $ args!!2)