import Control.Monad
import System.Exit        (ExitCode(..))
import System.Process     (readProcessWithExitCode, readProcess)
import System.Directory   (listDirectory, doesFileExist)
import System.Environment (getExecutablePath)

exePath :: IO String
exePath = readProcess "stack" ["path", "--local-install-root"] [] >>= \path ->
    return $ (init path) ++ "/bin/koakc"

checkSuccess :: String -> IO ()
checkSuccess f = do
    putStrLn $ "Test file " ++ f
    (code, _, err) <- exePath >>= \exe -> readProcessWithExitCode exe ["test/"++f, "-o", "./a.out"] []
    case code of
        ExitSuccess -> do
            putStrLn "  \27[92mCompilation succed\27[0m"
            (code', out, _) <- readProcessWithExitCode "./a.out" [] []
            content <- readFile $ "test/expectedResult/" ++ take ((length f) - 4) f
            if code' == ExitSuccess && init out == content
                then putStrLn $ "  \27[92mExecution succed\27[0m"
                else putStrLn $ "  \27[91mUnexpected result. Got \"" ++ if length out > 0 then init out else out ++ "\", but expected \"" ++ content ++ "\"\27[0m"
        _ -> putStrLn $ "  \27[91mFailed to compile: " ++ err ++ "\27[0m"

checkFailure :: String -> IO ()
checkFailure f = do
    putStrLn $ "Test file " ++ f
    (code, _, err) <- exePath >>= \exe -> readProcessWithExitCode exe ["test/"++f] []
    case code of
        ExitFailure 84 -> putStrLn "  \27[92mCompilation refused\27[0m"
        ExitSuccess -> putStrLn "  \27[91mUnexpected compilation success\27[0m"
        ExitFailure c -> putStrLn $ "  \27[91mUnexpected error code " ++ show c ++ "\27[0m"

main :: IO ()
main = do
    --(reverse (dropWhile (/='/') (reverse path)))
    exePath >>= putStrLn
    dir <- listDirectory "test"
    forM_ dir (\f -> do
        when (drop ((length f) - 4) f == ".kal")
            (doesFileExist ("test/expectedResult/" ++ take ((length f) - 4) f) >>= \b -> 
            if b
                then checkSuccess $ f
                else checkFailure $ f))