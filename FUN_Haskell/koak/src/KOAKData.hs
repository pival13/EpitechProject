module KOAKData where


type AST = [Kdefs]
data Kdefs = Function { functName :: String, functArgs :: [(String, Type)], functReturn :: Type, functBody :: Expr }
           | Expression Expr Type deriving (Show)
data Expr = ForExpr { forVar :: (String, (Expr, Type)), forCond :: (Expr, Type), forStep :: (Expr, Type), forBody :: (Expr, Type) }
          | WhileExpr { whileCond :: (Expr, Type), whileBody :: (Expr, Type) }
          | IfExpr { ifCond :: (Expr, Type), ifThen :: (Expr, Type), ifElse :: Maybe (Expr, Type) }
          | Exprs [(Expr, Type)]
          | BinOp { binLft :: (Expr, Type), binName :: String, binRgt :: (Expr, Type) }
          | UnOp { unName :: String, unArg :: (Expr, Type) }
          | Call { callName :: String, callArgs :: [(Expr, Type)] }
          | Nb Integer
          | NbF Double
          | Var String deriving (Show)
data Type = TUndef | TVoid | TInt | TDouble deriving (Show, Eq)

{-
    < = 10
    + = 20
    * = 40

    maxime1.didier@epitech.eu
-}