import System.Exit
import System.Environment
import Control.Exception


import Dannon
import Lib

parseFile :: String -> Maybe [Double]
parseFile str
    | (not $ length (lines str) == 1) || (not $ all (\wd -> isFloat wd) $ words str) = Nothing
    | otherwise = Just $ map (\wd -> read wd::Double) $ words str

main :: IO ()
main = do
    args <- getArgs
    if not $ length args == 1 then
        failure "USAGE\n\t./301dannon file\nDESCRIPTION\n\tfile\tfile that contains the numbers to be sorted, separated by spaces"
    else do
        result <- try (readFile $ args!!0) :: IO (Either SomeException String)
        case result of
            Left _ -> failure "file must be a readable file"
            Right file -> case (parseFile file) of
                Nothing -> failure "file must only contains numbers, separated by spaces"
                Just numbers -> dannon numbers