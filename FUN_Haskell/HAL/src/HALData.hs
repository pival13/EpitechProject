module HALData where

import Control.Exception

data Expr   = Quote Expr
            | Bl Bool
            | Nb Double
            | Symb String
            | List [Expr]
            | Lambda [String] Expr
            | NoReturn deriving(Eq)

isSymb :: Expr -> Bool
isSymb (Symb _) = True
isSymb _ = False

isList :: Expr -> Bool
isList (List _) = True
isList _ = False

instance Show Expr where
    show (NoReturn) = throw (TypeError "Invalid syntax. Cannot use a procedure without return.")
    show (Quote s) = "'" ++ (show s)--s //TODO
    show (Bl True) = "#t"
    show (Bl False) = "#f"
    show (Nb n) = if fromIntegral (floor n) == n then show (floor n) else show n
    show (Symb s) = s
    show (Lambda _ _) = "#<procedure>"--"#<lambda "++(show $ length args)++" args>"
    show (List l) = {-throw (TypeError $ "Invalid syntax " ++ -}"(" ++ (showListElem l) ++ ")"--)
        where showListElem [] = ""
              showListElem (a:[]) = ". " ++ show a
              showListElem (a:List []:[]) = show a
              showListElem (a:as) = show a ++ " " ++ showListElem as

type SymbolTable = [(String, Expr)]