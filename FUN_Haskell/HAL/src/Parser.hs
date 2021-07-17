module Parser where

import Data.Char
import Control.Applicative

newtype Parser a = Parser { parse :: String -> Maybe (a, String) }

instance Functor Parser where
    --fmap -> (a -> b) -> Parser a -> Parser b
    fmap f (Parser p) = Parser $ \s -> case p s of
        Just (b, s') -> Just (f b, s')
        Nothing -> Nothing

instance Applicative Parser where
    --pure -> a -> Parser a
    pure a = Parser (\s -> Just (a, s))
    --(<*>) -> Parser (a -> b) -> Parser a -> Parser b
    (Parser p1) <*> (Parser p2) = Parser $ \s -> case p1 s of
        Just (f, s') -> case p2 s' of
            Just (a, s'') -> Just (f a, s'')
            Nothing -> Nothing
        Nothing -> Nothing

instance Alternative Parser where
    --empty -> Parser a
    empty = Parser (\s -> Nothing)
    --(<|>) -> Parser a -> Parser a -> Parser a
    (Parser p1) <|> (Parser p2) = Parser $ \s ->
        case p1 s of
            Nothing -> p2 s
            result  -> result

instance Monad Parser where
    --(>>=) -> Parser a -> (a -> Parser b) -> Parser b
    (Parser p) >>= f = Parser $ \s ->
        case p s of
            Just (a, s') -> parse (f a) s'
            Nothing -> Nothing
    --(Parser p1) >> (Parser p2) = p1 >>= (\a -> p2)
    --a <- (Parser p) = p >>= (\a -> ...)

--"*"
getAll :: Parser a -> Parser [a]
getAll = many

--"+"
getSeveral :: Parser a -> Parser [a]
getSeveral = some

getFirst :: Parser Char
getFirst = Parser $ \s -> 
    case s of
        (c:cs) -> Just (c, cs)
        [] -> Nothing

--"(?=())."
getIf :: (Char -> Bool) -> Parser Char
getIf pred = getFirst >>= \c ->
    if pred c
        then pure c
        else empty

--"a"
getChara :: Char -> Parser Char
getChara c = getIf (c ==)

--"[azer]"
getOneOf :: [Char] -> Parser Char
getOneOf s = getIf $ (flip elem s)

--"[^azrt]"
getOneNotOf :: [Char] -> Parser Char
getOneNotOf s = getIf $ (flip notElem s)

--"\s*"
getAllSpaces :: Parser String
getAllSpaces = getAll $ getIf isSpace

--"-?\d+(\.\d+)?"
getNumber :: Parser Double
getNumber = 
    (getOneOf "+-" <|> pure '+') >>= (\sign ->
    getAll (getIf isDigit) >>= (\nb1 ->
    ((getString "." >> getAll (getIf isDigit)) <|> pure []) >>= (\nb2 ->
    if nb1 /= "" || nb2 /= ""
        then case sign of
            '-' -> pure $ read ("-0"++nb1++"."++nb2++"0")
            _   -> pure $ read ("0"++nb1++"."++nb2++"0")
        else empty)))

--"azeyu"
getString :: String -> Parser String
getString [] = pure []
getString s@(c:cs) = getChara c >> getString cs >> pure s

--"\(()\)"
getParenths :: Parser a -> Parser a
getParenths p =
    getString "(" >>
    p >>= (\a ->
    getString ")" >>
    pure a)

--"\s*\(\s*()\s*\)\s*"
getParenthsTrimm :: Parser a -> Parser a
getParenthsTrimm p =
    getAllSpaces >>
    getParenths (
        getAllSpaces >>
        p >>= (\b ->
        getAllSpaces >>
        pure b)
    ) >>= (\a ->
    getAllSpaces >>
    pure a)