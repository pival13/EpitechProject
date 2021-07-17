module RPN (
    postParserRPN
) where

import DataType

parseNumber :: [EvalExprNode] -> (EvalExprAST, [EvalExprNode])
parseNumber (nb@(Left _):rest) = ([nb], rest)
parseNumber (Right ParI:rest) = parseParenth rest

parsePeerUntil :: [EvalExprNode] -> Operator -> (EvalExprAST, [EvalExprNode])
parsePeerUntil expr@(Right Pow:_) Pow = (nb ++ nb2, rest2)
    where (nb, rest) = parsePeerOpeNb expr
          (nb2, rest2) = parsePeerUntil rest Pow
parsePeerUntil expr@(Right ope:_) ref
    | ref >= ope = ([], expr)
    | otherwise = (nb ++ nb2, rest2)
        where (nb, rest) = parsePeerOpeNb expr
              (nb2, rest2) = parsePeerUntil rest ref

parsePeerOpeNb :: [EvalExprNode] -> (EvalExprAST, [EvalExprNode])
parsePeerOpeNb (Right ParO:rest) = ([], rest)
parsePeerOpeNb (Right ope:expr) = (nb ++ nb2 ++ [Right ope], rest2)
    where (nb, rest) = parseNumber expr
          (nb2, rest2) = parsePeerUntil rest ope

parseAllPeerOpeNb :: [EvalExprNode] -> (EvalExprAST, [EvalExprNode])
parseAllPeerOpeNb (Right ParO:rest) = ([], rest)
parseAllPeerOpeNb expr = (nb ++ nb2, rest2)
    where (nb, rest) = parsePeerOpeNb expr
          (nb2, rest2) = parseAllPeerOpeNb rest

parseParenth :: [EvalExprNode] -> (EvalExprAST, [EvalExprNode])
parseParenth (Right Minus:rest) = parseParenth (Left (-1):Right Mult:rest)
parseParenth (Right ParI:expr) = (nb ++ nb2, rest2)
    where (nb, rest) = parseParenth expr
          (nb2, rest2) = parseAllPeerOpeNb rest
parseParenth (nb@(Left _):expr@(Right ope:_)) = ((nb:nb2), rest)
    where (nb2, rest) = parseAllPeerOpeNb expr

postParserRPN :: [EvalExprNode] -> EvalExprAST
postParserRPN (Right ParI:rest) = fst $ parseParenth rest