import System.Exit
import System.Environment
import Data.List
import Data.Char

isInt :: [Char] -> Bool
isInt [] = False
isInt (x:[])
    | elem x "0123456789" = True
    | otherwise = False
isInt (x:y)
    | elem x "-0123456789" = isInt y
    | otherwise = False

splitOn :: (a -> Bool) -> [a] -> [[a]]
splitOn _ [] = []
splitOn f l@(x:xs)
  | f x = splitOn f xs
  | otherwise = let (h,t) = break f l in h:(splitOn f t)

parse_error :: [String] -> [String] -> Bool
parse_error [] [] = True
parse_error [] x = parse_error ["0"] x
parse_error x [] = parse_error x ["sa"]
parse_error (x:xs) (y:ys) 
    | isInt x && elem y ["sa", "sb", "sc", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr", " "] = parse_error xs ys
    | otherwise = False

check_list :: [Int] -> Bool
check_list [] = True
check_list (x:[]) = True
check_list (x:y:z)
    | x <= y = check_list (y:z)
    | otherwise = False

create_list :: [String] -> ([Int], [Int])
create_list [] = ([], [])
create_list (x:xs) = (((read x):(fst $ create_list xs)),[])

sa :: ([Int], [Int]) -> ([Int], [Int])
sa ([], y) = ([], y)
sa ((x:[]), y) = ((x:[]), y)
sa ((x:x2:xs), y) = ((x2:x:xs), y)

sb :: ([Int], [Int]) -> ([Int], [Int])
sb (x, []) = (x, [])
sb (x, (y:[])) = (x, (y:[]))
sb (x, (y:y2:ys)) = (x, (y2:y:ys))

sc :: ([Int], [Int]) -> ([Int], [Int])
sc x = sa $ sb x

pa :: ([Int], [Int]) -> ([Int], [Int])
pa (x, []) = (x, [])
pa (x, (y:ys)) = ((y:x), ys)

pb :: ([Int], [Int]) -> ([Int], [Int])
pb ([], y) = ([], y)
pb ((x:xs), y) = (xs, (x:y))

ra :: ([Int], [Int]) -> ([Int], [Int])
ra ([], y) = ([], y)
ra ((x:xs), y) = (xs ++ [x], y)

rb :: ([Int], [Int]) -> ([Int], [Int])
rb (x, []) = (x, [])
rb (x, (y:ys)) = (x, ys ++ [y])

rr :: ([Int], [Int]) -> ([Int], [Int])
rr x = ra $ rb x

rra :: ([Int], [Int]) -> ([Int], [Int])
rra ([], y) = ([], y)
rra (x, y) = ((last x:init x), y)

rrb :: ([Int], [Int]) -> ([Int], [Int])
rrb (x, []) = (x, [])
rrb (x, y) = (x, (last y:init y))

rrr :: ([Int], [Int]) -> ([Int], [Int])
rrr x = rra $ rrb x

execute :: [String] -> ([Int], [Int]) -> IO ()
execute [] (x, y)
    | y /= [] || check_list x == False = do
        putStr "KO: "
        print $ (x, y)
    | otherwise = putStrLn "OK"
execute (x:xs) y
    | x == "sa" = execute xs $ sa y
    | x == "sb" = execute xs $ sb y
    | x == "sc" = execute xs $ sc y
    | x == "pa" = execute xs $ pa y
    | x == "pb" = execute xs $ pb y
    | x == "ra" = execute xs $ ra y
    | x == "rb" = execute xs $ rb y
    | x == "rr" = execute xs $ rr y
    | x == "rra" = execute xs $ rra y
    | x == "rrb" = execute xs $ rrb y
    | x == "rrr" = execute xs $ rrr y
    | otherwise = execute xs y

main :: IO ()
main = do
    nb <- getArgs
    ope <- getLine
    ope <- pure $ splitOn isSpace ope
    if parse_error nb ope == False then
        exitWith $ ExitFailure 84
    else
        execute ope $ create_list nb