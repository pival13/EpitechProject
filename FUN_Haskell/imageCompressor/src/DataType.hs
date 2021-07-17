module DataType where

data Color = Color { r :: Integer, g :: Integer, b :: Integer } deriving (Eq)
data PointColor = PointColor { x :: Integer, y :: Integer, color :: Color }

instance Show Color where
    show (Color r g b) = "(" ++ (show r) ++ "," ++ (show g) ++ "," ++ (show b) ++ ")"

instance Show PointColor where
    show (PointColor x y color) = "(" ++ (show x) ++ "," ++ (show y) ++ ") " ++ (show color)

addColor :: Color -> Color -> Color
addColor c1 c2 = Color { r = (r c1) Prelude.+ (r c2), g = (g c1) Prelude.+ (g c2), b = (b c1) Prelude.+ (b c2) }

divColor :: Color -> Integer -> Color
divColor c 0 = Color { r = 0, g = 0, b = 0 }
divColor c n = Color { r = (r c) `div` n, g = (g c) `div` n, b = (b c) `div` n }

distColor :: Color -> Color -> Float
distColor c1 c2 = sqrt . fromInteger $ (r c1 - r c2)^2 + (g c1 - g c2)^2 + (b c1 - b c2)^2

closerColor :: PointColor -> Color -> Color -> Color
closerColor pt c1 c2
    | distColor c1 (color pt) < distColor c2 (color pt) = c1
    | otherwise = c2