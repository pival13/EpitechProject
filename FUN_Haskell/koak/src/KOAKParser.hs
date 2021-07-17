module KOAKParser where 

import Data.Char
import Control.Applicative

import Parser
import KOAKData

parseFunct :: Parser Kdefs
parseFunct = getAllSpaces >> getString "def" >> getSeveralSpaces >>
    parsePrototype >>= (\(name, args, ret) ->
        getSeveralSpaces >> parseExpression >>= (\body ->
            getAllSpaces >> getString ";" >>
            pure Function { functName = name, functArgs = args, functReturn = ret, functBody = body } ))

parsePrototype :: Parser (String, [(String, Type)], Type)
parsePrototype = parseIdent >>= (\fName -> 
    getParenthsTrimm (getAll (parseIdent >>= (\aName -> 
        (getAllSpaces >> getString ":" >> parseType >>= \aType -> pure (aName, aType))
        <|> pure (aName, TUndef)
    ))) >>= (\fArgs ->
        (getAllSpaces >> getString ":" >> parseType >>= \fType -> pure (fName, fArgs, fType))
        <|> pure (fName, fArgs, TUndef)))

parseExpression :: Parser Expr
parseExpression = parseIfExpr
    <|> parseForExpr
    <|> parseWhileExpr
    <|> (parseExpr >>=
        (\e -> (getSeveral (getAllSpaces >> getString ":" >> parseExpr >>= \e' -> return (e', TUndef)) >>= (\es -> pure $ Exprs ((e, TUndef):es)))
            <|> pure e))

parseIfExpr :: Parser Expr
parseIfExpr = getAllSpaces >> getString "if" >> getSeveralSpaces >> parseExpr >>=
    (\cond -> getSeveralSpaces >> getString "then" >> getSeveralSpaces >> parseExpression >>=
    (\body1 -> 
        (getSeveralSpaces >> getString "else" >> getSeveralSpaces >> parseExpression >>=
            (\body2 -> pure IfExpr { ifCond = (cond, TUndef), ifThen = (body1, TUndef), ifElse = Just (body2, TUndef) }))
        <|> pure IfExpr { ifCond = (cond, TUndef), ifThen = (body1, TUndef), ifElse = Nothing }))

parseForExpr :: Parser Expr
parseForExpr = getAllSpaces >> getString "for" >> getSeveralSpaces >> parseIdent >>=
    (\initVar -> getAllSpaces >> getString "=" >> parseExpr >>=
    (\initVal ->  getAllSpaces >> getString "," >> parseExpr >>=
    (\cond -> getAllSpaces >> getString "," >> parseExpr >>=
    (\step -> getSeveralSpaces >> getString "in" >> getSeveralSpaces >> parseExpression >>=
    (\body -> pure ForExpr { forVar = (initVar, (initVal, TUndef)), forCond = (cond, TUndef), forStep = (step, TUndef), forBody = (body, TUndef) } )))))

parseWhileExpr :: Parser Expr
parseWhileExpr = getAllSpaces >> getString "while" >> getSeveralSpaces >> parseExpr >>=
    (\cond -> getSeveralSpaces >> getString "do" >> getSeveralSpaces >> parseExpression >>=
    (\body -> pure WhileExpr { whileCond = (cond, TUndef), whileBody = (body, TUndef) }))

parseExpr :: Parser Expr
parseExpr = parseUntil ["="] >>= parseExprRecur ["="]
    where parseUntil [] = parseUnary
          parseUntil opes = parseUntil (nextOpe opes) >>= parseExprRecur (nextOpe opes)
          parseExprRecur [] lft = pure lft
          parseExprRecur opes lft = (getAllSpaces >> getIfOneOf (\ope -> getString ope) opes >>=
                (\ope -> parseUntil opes >>=
                (\rgt -> parseExprRecur opes $ BinOp { binLft = (lft, TUndef), binRgt = (rgt, TUndef), binName = ope })))
            <|> pure lft
          nextOpe ["="] = ["==", "!="]
          nextOpe ["==", "!="] = ["<",">"]
          nextOpe ["<", ">"] = ["+","-"]
          nextOpe ["+", "-"] = ["*","/"]
          nextOpe ["*", "/"] = []

parseUnary :: Parser Expr
parseUnary = getAll (getAllSpaces >> getOneOf "!-")
    >>= (\unaOpes -> ((getParenthsTrimm parseExpression)
        <|> parseNumber
        <|> (parseIdent >>= getVarOrCall))
    >>= (\expr -> pure $ foldr (\ope exp -> UnOp { unArg = (exp, TUndef), unName = [ope] }) expr unaOpes))
    where
        getVarOrCall var = getParenthsTrimm (
                (parseExpr >>= (\e -> getAll (getAllSpaces >> getString "," >> parseExpr >>= \e' -> return (e', TUndef)) >>= (\es -> pure ((e, TUndef):es))) >>=
                    (\args -> pure Call { callName = var, callArgs = args }))
                <|> pure Call { callName = var, callArgs = [] })
            <|> (pure $ Var var)

parseType :: Parser Type
parseType = parseIdent >>= (\id -> case id of
    "void" -> pure TVoid
    "int" -> pure TInt
    "double" -> pure TDouble)

parseIdent :: Parser String
parseIdent = getAllSpaces >> getIf isAlpha >>= (\c1 -> getAll (getIf isAlphaNum) >>= (\cs -> pure (c1:cs)))

parseNumber :: Parser Expr
parseNumber = getAllSpaces >> (
    (getString "." >> getSeveral (getIf isDigit) >>= (\n -> pure $ NbF (read $ "0."++n::Double)))
    <|> (getSeveral (getIf isDigit) >>=
        (\n1 -> (getString "." >> getAll (getIf isDigit) >>= (\n2 -> pure $ NbF (read $ n1++"."++n2++"0"::Double)))
            <|> (pure $ Nb (read n1::Integer)))))

parserKoak :: Parser AST
parserKoak = getAll (parseFunct
        <|> (parseExpression >>= (\e -> getAllSpaces >> getString ";" >> pure (Expression e TUndef)))) >>= 
    (\ast -> getAllSpaces >> return ast)

parseKoak :: String -> Maybe (AST, String)
parseKoak = parse parserKoak