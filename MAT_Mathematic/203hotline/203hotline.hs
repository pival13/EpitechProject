module Hotline
    ( factorielle, coefBino, binoLaw, poissonLaw, getPoissonLaw, getBinoLaw
    ) where

factorielle :: Integer -> Integer
factorielle 0 = 1
factorielle x = x * factorielle (x-1)

coefBino :: Integer -> Integer -> Integer
coefBino n k
    | k > n = (-1)
    | otherwise = (factorielle n) `div` ((factorielle k) * (factorielle (n-k)))

binoLaw :: Integer -> Integer -> Double -> Double--IO ()
binoLaw n k p
    | k > n = (-1)
    | otherwise = do
        --print $ ((1-p)^(n-k))
        {-print $-} (fromInteger (coefBino n k)) * (p^k) * ((1-p)^(n-k))

poissonLaw :: Integer -> Double -> Double
poissonLaw k lambda = ((lambda^k) / (fromInteger $ factorielle k)) * (exp (-lambda))

getPoissonLaw :: Integer -> Integer -> [Double]
getPoissonLaw _ 51 = []
getPoissonLaw x k = (poissonLaw k ((fromInteger $ x * 3500) / (fromInteger $ (28800))):getPoissonLaw x (k+1))

getBinoLaw :: Integer -> Integer -> [Double]
getBinoLaw _ 51 = []
getBinoLaw x k = (binoLaw 3500 k (fromInteger x / fromInteger 28800):getBinoLaw x (k+1))
