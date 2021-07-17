import System.Exit
import System.Environment
import Data.List
import Data.Char
import Data.Bits

failure :: String -> IO()
failure str = do
    putStrLn str
    exitWith $ ExitFailure 84

isInt :: [Char] -> Bool
isInt [] = False
isInt (x:[])
    | elem x "0123456789" = True
    | otherwise = False
isInt (x:y)
    | elem x "-0123456789" = isInt y
    | otherwise = False

-- table, (width, offset), color
displayWolfram :: [Char] -> (Int, Int) -> Bool -> IO()
displayWolfram tbl (a, off) b
    | off > 0 = displayWolfram (' ':' ':tbl) (a, (off-1)) b
    | off < 0 = displayWolfram (tbl ++ [' ',' ']) (a, (off+1)) b
displayWolfram tbl (width, 0) a
    | length tbl > width+1 = displayWolfram (tail $ init tbl) (width, 0) a
    | length tbl > width = displayWolfram (init tbl) (width, 0) a
    | length tbl < width = displayWolfram ((' ':tbl) ++ [' ']) (width, 0) a
-- Color: 9X = Text, 10X = Backgroud
-- X0 = Black, X1 = Red, X2 = Green, X3 = Yellow, X4 = Blue, X5 = Magenta, X6 = Cyan, X7 = White, X8 = Grey
displayWolfram str _ True = putStrLn ("\27[92m" ++ str ++ "\27[0m")
displayWolfram str _ False = putStrLn str

ruleWolfram :: (Char,Char,Char) -> Int -> Char
ruleWolfram (' ',' ',' ') x = if testBit x 0 == True then '*' else ' '
ruleWolfram (' ',' ','*') x = if testBit x 1 == True then '*' else ' '
ruleWolfram (' ','*',' ') x = if testBit x 2 == True then '*' else ' '
ruleWolfram (' ','*','*') x = if testBit x 3 == True then '*' else ' '
ruleWolfram ('*',' ',' ') x = if testBit x 4 == True then '*' else ' '
ruleWolfram ('*',' ','*') x = if testBit x 5 == True then '*' else ' '
ruleWolfram ('*','*',' ') x = if testBit x 6 == True then '*' else ' '
ruleWolfram ('*','*','*') x = if testBit x 7 == True then '*' else ' '
--ruleWolfram (a,b,c) x = if testBit x ((shift (fromEnum a) 2) .|. ((shift (fromEnum b) 1) .|. (fromEnum c))) == True then '*' else ' '

updateLine :: [Char] -> Int -> [Char]
updateLine (x:y:z:[]) rule = [ruleWolfram (x,y,z) rule]
updateLine (x:y:z:xs) rule = ((ruleWolfram (x,y,z) rule):(updateLine (y:z:xs) rule))

-- table, pos, (rules, startLine, endLine, width, offset)
wolfram :: [Char] -> Int -> (Int, Int, Int, Int, Int, Bool) -> IO()
wolfram line n (rule, start, height, width, offset, color)
    | n == height+start = exitWith ExitSuccess
    | otherwise = do
        if n >= start then
            displayWolfram line (width, offset) color
        else
            putStr ""
        wolfram (updateLine ((' ':' ':line) ++ [' ',' ']) rule) (n+1) (rule,start,height,width,offset,color)

-- [param], (rules, startLine, endLine, width, offset)
parseWolfram :: [String] -> (Int, Int, Int, Int, Int, Bool) -> IO()
parseWolfram [] (-1,_,_,_,_,_) = failure "Missing --rule option"
parseWolfram [] (rule,start,height,width,offset,color) = wolfram ['*'] 0 (rule, start, height, width, offset, color)
parseWolfram ("--color":rest) (rule,start,height,width,offset,_) = parseWolfram rest (rule,start,height,width,offset,True)
parseWolfram [_] _ = failure "Invalid number of arguments"
parseWolfram ("--rule":value:rest) (_,start,height,width,offset,color) | isInt value && (read value::Int) >= 0 = parseWolfram rest ((read value::Int),start,height,width,offset,color) | otherwise = failure "Int expected"
parseWolfram ("--start":value:rest) (rule,_,height,width,offset,color) | isInt value = parseWolfram rest (rule,(read value::Int),height,width,offset,color) | otherwise = failure "Int expected"
parseWolfram ("--lines":value:rest) (rule,start,_,width,offset,color) | isInt value && (read value::Int) >= 0 = parseWolfram rest (rule,start,(read value::Int),width,offset,color) | otherwise = failure "Int expected"
parseWolfram ("--window":value:rest) (rule,start,height,_,offset,color) | isInt value && (read value::Int) >= 0 = parseWolfram rest (rule,start,height,(read value::Int),offset,color) | otherwise = failure "Int expected"
parseWolfram ("--move":value:rest) (rule,start,height,width,_,color) | isInt value = parseWolfram rest (rule,start,height,width,(read value::Int),color) | otherwise = failure "Int expected"
parseWolfram _ _ = failure "Unknow option"

main :: IO ()
main = do
    args <- getArgs
    parseWolfram args ((-1), 0, (-1), 80, 0, False)