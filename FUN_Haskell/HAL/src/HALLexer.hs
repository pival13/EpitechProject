module HALLexer where

import HALData
import Control.Exception
import GHC.Float ( int2Double )
import Data.Fixed ( mod' )

myFloor :: Double -> Double
myFloor x = int2Double (truncate x)

lexerError :: (SymbolTable, Expr)
lexerError = throw (PatternMatchFail "Exception occured")

initialGlobTable :: SymbolTable
initialGlobTable = []

sTableContain :: SymbolTable -> SymbolTable -> String -> Maybe (Expr)
sTableContain [] [] _ = Nothing
sTableContain ((s,expr):rest) [] name
    | s == name = Just expr
    | otherwise = sTableContain rest [] name
sTableContain global ((s,expr):rest) name
    | s == name = Just expr
    | otherwise = sTableContain global rest name

addSymbolToTable :: SymbolTable -> (String, Expr) -> SymbolTable
addSymbolToTable [] s = [s]
addSymbolToTable (old@(s,_):rest) new@(s',e)
    | s == s' = ((s,e):rest)
    | otherwise = (old:(addSymbolToTable rest new))


{-
    Arithmetic built-in //TODO
-}

plusHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
plusHAL global _ [] = (global, Nb 0)
plusHAL global local (expr:rest) = case execHAL expr global local of
    (glob, (Nb a)) -> case plusHAL glob local rest of
        (glob', (Nb b)) -> (glob', Nb (a + b))
        _ -> lexerError
    _ -> lexerError

minusHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
minusHAL _ _ [] = lexerError
minusHAL global local (expr:[]) = case execHAL expr global local of
    (glob, (Nb a)) -> (glob, (Nb (a * (-1))))
    _ -> lexerError
minusHAL global local (expr:rest) = case execHAL expr global local of
    (glob, (Nb a)) -> case plusHAL glob local rest of
        (glob', (Nb b)) -> (glob', Nb (a - b))
        _ -> lexerError
    _ -> lexerError

timesHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
timesHAL global _ [] = (global, Nb 1)
timesHAL global local (expr:rest) = case execHAL expr global local of
    (glob, (Nb a)) -> case timesHAL glob local rest of
        (glob', (Nb b)) -> (glob', Nb (a * b))
        _ -> lexerError
    _ -> lexerError

divideHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
divideHAL _ _ [] = lexerError
divideHAL global local (expr:[]) = case execHAL expr global local of
    (_, Nb 0) -> lexerError
    (glob, Nb a) -> (glob, Nb (1/a))
    _ -> lexerError
divideHAL global local (expr:rest) = case execHAL expr global local of
    (glob, (Nb a)) -> case timesHAL glob local rest of
        (_, (Nb 0)) -> lexerError
        (glob', (Nb b)) -> (glob', Nb (a / b))
        _ -> lexerError
    _ -> lexerError

divHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
divHAL global local (exp1:exp2:[]) = case execHAL exp1 global local of
    (glob, (Nb a)) -> case execHAL exp2 glob local of
        (_, (Nb 0)) -> lexerError
        (glob', (Nb b)) -> (glob', Nb (myFloor (a / b)))
        _ -> lexerError
    _ -> lexerError
divHAL _ _ _ = lexerError

modHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
modHAL global local (exp1:exp2:[]) = case execHAL exp1 global local of
    (glob, (Nb a)) -> case execHAL exp2 glob local of
        (_, (Nb 0)) -> lexerError
        (glob', (Nb b)) -> case b < 0 of
            True -> (glob', Nb (a `mod'` (b * (-1))))
            _ -> (glob', Nb (a `mod'` b))
        _ -> lexerError
    _ -> lexerError
modHAL _ _ _ = lexerError



quoteHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
quoteHAL global _ (x:[]) = (global, x)
quoteHAL _ _ _ = lexerError

{-
    List built-in //TODO
-}

consHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
consHAL global local (exp1:exp2:[]) = case execHAL exp1 global local of
    (glob, a) -> case execHAL exp2 glob local of
        (glob', List []) -> (glob', List (a:(List []):[]))
        (glob', List elem') -> (glob', List (a:elem'))
        (glob', b) -> (glob', List (a:b:[]))
consHAL _ _ _ = lexerError

carHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
carHAL global local (expr:[]) = case execHAL expr global local of
    (glob, List (a:_)) -> (glob, a)
    _ -> lexerError
carHAL _ _ _ = lexerError

cdrHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
cdrHAL global local (expr:[]) = case execHAL expr global local of
    (glob, List (_:b:[])) -> (glob, b)
    (glob, List (_:b)) -> (glob, List b)
    _ -> lexerError
cdrHAL _ _ _ = lexerError




{-
    Bool built-in //TODO
-}

inferiorHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
inferiorHAL global local (exp1:exp2:[]) = case execHAL exp1 global local of
    (glob, (Nb a)) -> case execHAL exp2 glob local of
        (glob', (Nb b)) -> (glob', Bl (a < b))
        _ -> lexerError
    _ -> lexerError
inferiorHAL _ _ _ = lexerError

eqHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
eqHAL global local (expr:rest:[]) = case execHAL expr global local of
    (glob, Bl a)    -> case execHAL rest glob local of
        (glob', Bl b) -> (glob', Bl (a == b))
        (glob', _)    -> (glob', Bl False)
    (glob, Nb a)    -> case execHAL rest glob local of
        (glob', Nb b) -> (glob', Bl (a == b))
        (glob', _)    -> (glob', Bl False)
    (glob, Symb a)  -> case execHAL rest glob local of
        (glob', Symb b) -> (glob', Bl (a == b))
        (glob', _)      -> (glob', Bl False)
    (glob, List []) -> case execHAL rest glob local of
        (glob', List []) -> (glob', Bl True)
        (glob', _)       -> (glob', Bl False)
    (glob, _)       -> (glob, Bl False)
eqHAL _ _ _ = lexerError

atomHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
atomHAL global local (expr:[]) = case execHAL expr global local of
    (glob, Bl _) -> (glob, Bl True)
    (glob, Nb _) -> (glob, Bl True)
    (glob, Symb _) -> (glob, Bl True)
    (glob, List []) -> (glob, Bl True)
    (glob, _) -> (glob, Bl False)
atomHAL _ _ _ = lexerError




{-
    Complex built-in //TODO
-}

letHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
letHAL global local ((List []):body:[]) = execHAL body global local
letHAL global local ((List args):body:[])
    | last args == List [] || all
        (\a -> case a of
            List as -> length as == 3 && last as == List [] && isSymb (head as)
            _ -> False
        ) (init args) = execHAL body global (foldl (\table (List (Symb a:b:_)) ->
            case execHAL b global local of (_, b') -> addSymbolToTable table (a, b')) local (init args))
    | otherwise = throw (PatternMatchFail $ show args)-- //TODO
letHAL _ _ _ = throw (PatternMatchFail "Unexpected content for let built-in.")

lambdaHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
lambdaHAL global _ ((List []):body:[]) = (global, Lambda [] body)
lambdaHAL global _ ((List args):body:[])
    | last args == List [] && all isSymb (init args) = (global, Lambda (map (\(Symb a) -> a) (init args)) body)
    | otherwise = lexerError
lambdaHAL _ _ _ = lexerError

defineHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
defineHAL global local (Symb s:body:[]) = case execHAL body global local of
    (global', expr) -> (addSymbolToTable global' (s,expr), NoReturn)
defineHAL _ _ (List (Symb _:[]):_) = lexerError
defineHAL global local (List (Symb s:List []:[]):body:[]) = (global ++ [(s, snd (lambdaHAL global local [List [],body]))], NoReturn)
defineHAL global local (List (Symb s:args):body:[])
    | last args /= List [] || any (\a -> not $ isSymb a) (init args) = lexerError
    | otherwise = (addSymbolToTable global (s, snd (lambdaHAL global local [List args,body])), NoReturn)
defineHAL _ _ _ = lexerError

condHAL :: SymbolTable -> SymbolTable -> [Expr] -> (SymbolTable, Expr)
condHAL _ _ [] = lexerError
condHAL global local ((List (cond:List []:[])):rest) = case execHAL cond global local of
    (global', Bl False) -> if rest == [] then (global', NoReturn) else condHAL global' local rest
    r -> r 
condHAL global local ((List (cond:expr:List[]:[])):rest) = case execHAL cond global local of
    (global', Bl False) -> if rest == [] then (global', NoReturn) else condHAL global' local rest
    (global', _) -> execHAL expr global' local
--condHAL global local ((List (cond:expr):rest) = //TODO handle more than one expr
condHAL _ _ _ = lexerError




execFunct :: SymbolTable -> SymbolTable -> String -> [Expr] -> (SymbolTable, Expr)
execFunct global local "cons"   args = consHAL global local args
execFunct global local "car"    args = carHAL global local args
execFunct global local "cdr"    args = cdrHAL global local args
execFunct global local "eq?"    args = eqHAL global local args
execFunct global local "atom?"  args = atomHAL global local args
execFunct global local "+"      args = plusHAL global local args
execFunct global local "-"      args = minusHAL global local args
execFunct global local "*"      args = timesHAL global local args
execFunct global local "div"    args = divHAL global local args
execFunct global local "mod"    args = modHAL global local args
execFunct global local "<"      args = inferiorHAL global local args
execFunct global local "quote"  args = quoteHAL global local args
execFunct global local "cond"   args = condHAL global local args
execFunct global local "lambda" args = lambdaHAL global local args
execFunct global local "let"    args = letHAL global local args
execFunct global local "define" args = defineHAL global local args
execFunct global local funct    args = case sTableContain global local funct of
    Just (Lambda [] body) -> if args == []
        then letHAL global local [List [], body]
        else throw (PatternMatchFail ("Invalid number of argument: 0 expected, " ++ (show (length args)) ++ " provided."))
    Just (Lambda vars body) -> if length vars == length args
        then letHAL global local [List
            ((zipWith (\a b -> List [Symb a, b]) vars args) ++ [List []])
            , body]
        else throw (PatternMatchFail ("Invalid number of argument: "++(show (length vars))++" expected, " ++ (show (length args)) ++ " provided."))
    Nothing -> throw (PatternMatchFail ("Unknow variable " ++ funct))
    _ -> throw (PatternMatchFail ("Attempt to apply non-procedure " ++ funct))

--                 globalSylmbol, localSymbol
execHAL :: Expr -> SymbolTable -> SymbolTable -> (SymbolTable, Expr)
execHAL (List (Symb _:[])) _ _ = throw (PatternMatchFail "Unexpected error occured")
execHAL l@(List (Symb sym:args)) global local
    | last args == List [] = execFunct global local sym (init args)
    | otherwise = throw (PatternMatchFail $ "Invalid syntax " ++ (show l))
execHAL l@(List (expr:args)) global local = case execHAL expr global local of
    (global', Lambda params body) -> if last args == List [] && length params == (length args)-1
        then letHAL global' local [List
            ((zipWith (\a b -> List [Symb a, b]) params (init args)) ++ [List []])
            , body]
        else throw (PatternMatchFail $ "Invalid number of argument: "++(show (length params))++" expected, " ++ (show $ (length args) - 1) ++ " provided.")
    _ -> throw (PatternMatchFail $ "Invalid syntax " ++ (show l))
execHAL (Symb s) globTable locTable = case sTableContain globTable locTable s of
    Just expr -> (globTable, expr)
    Nothing -> throw (PatternMatchFail ("Unknow variable " ++ s))
execHAL (Quote e) global _ = (global, e)
execHAL b global _ = (global, b)