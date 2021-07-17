module DataType where

{-
EXPR     = ( NUMBER {OPERATOR NUMBER}* )
NUMBER   = -?[0-9]+(.[0-9+])? | EXPR
OPERATOR = + | - | * | / | ^
-}

data Operator = ParI | ParO | Plus | Minus | Mult | Div | Pow deriving(Eq, Ord, Enum)

type EvalExprNode = Either Double Operator
--data EvalExprNode = EvalExprNode { type :: EENodeType, operator :: Operator, number :: Double }

type EvalExprAST = [EvalExprNode]

showEEAst :: EvalExprAST -> String
showEEAst [] = ""
showEEAst ((Left nb):xs) = show nb ++ " " ++ showEEAst xs
showEEAst ((Right ParI):xs) = "( " ++ showEEAst xs
showEEAst ((Right ParO):xs) = ") " ++ showEEAst xs
showEEAst ((Right Plus):xs) = "+ " ++ showEEAst xs
showEEAst ((Right Minus):xs) = "- " ++ showEEAst xs
showEEAst ((Right Mult):xs) = "* " ++ showEEAst xs
showEEAst ((Right Div):xs) = "/ " ++ showEEAst xs
showEEAst ((Right Pow):xs) = "^ " ++ showEEAst xs

isOperator :: Char -> Bool
isOperator c = elem c "+-*/^"

toOperator :: Char -> Operator
toOperator '(' = ParI
toOperator ')' = ParO
toOperator '+' = Plus
toOperator '-' = Minus
toOperator '*' = Mult
toOperator '/' = Div
toOperator '^' = Pow