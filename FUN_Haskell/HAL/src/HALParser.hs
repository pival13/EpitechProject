module HALParser where

{-
    expr = function | number | symbol | "#t" | "#f" | quote
    function = "(" symbol { listElem } ")"          #TODO
    symbol  = [^ {[(|`'",;)]} ]+ && not number  #TODO
    quote = "'" ( list | expr )
    list = "()" | "(" listElem { listElem } [ "." listElem ] ")"
    listElem = expr | list
-}

import Control.Applicative

import Parser
import HALData
import Lib

--parseFunction :: Parser Expr
--parseFunction = getParenthsTrimm (
--        parseSymbol >>= (\(Symb s) ->
--        getAll parseExpr >>= (\expr ->
--            pure (Funct s expr)
--    )))

parseNb :: Parser Expr
parseNb = getAllSpaces >> (getNumber >>= (\nb -> pure $ Nb nb))

parseSymb :: String -> Parser Expr
parseSymb "." = empty
parseSymb s
    | isNumberFloat ([head s]) 0 False 0 == True || isNumberFloat s 0 False 0 == True = empty
    | otherwise = pure $ Symb s

parseSymbol :: Parser Expr
parseSymbol = getAllSpaces >> (getSeveral (getOneNotOf "{[(|`'\",;)]} \t\r\n") >>= (\s -> parseSymb s))

parseBool :: Parser Expr
parseBool = (getAllSpaces >> getString "#t" >> Parser (\s -> Just (Bl True, s)))
    <|> (getAllSpaces >> getString "#f" >> Parser (\s -> Just (Bl False, s)))

parseQuote :: Parser Expr
parseQuote = (getAllSpaces >> getOneOf "'`" >> parseExpr >>= (\expr -> pure $ Quote expr))
    <|> (getParenthsTrimm $ getString "quote" >> getAllSpaces >> parseExpr >>= (\expr -> pure $ Quote expr))

parseList :: Parser Expr
parseList = getParenthsTrimm (
    ((getSeveral parseExpr
        >>= (\list -> (getAllSpaces
                >> getString "."
                >> parseExpr
                >>= (\elem -> case elem of
                    List [] -> pure $ list ++ [List []]
                    List elem' -> pure $ list ++ elem'
                    _ -> pure $ list ++ [elem]))
            <|> (pure $ list ++ [List []])))
    <|> (pure $ []))
    >>= (\list -> pure $ List list))

parseExpr :: Parser Expr
parseExpr = parseQuote <|> parseList <|> parseBool <|> parseNb <|> parseSymbol
