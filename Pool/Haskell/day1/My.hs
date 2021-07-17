mySucc :: Int -> Int
mySucc x = x + 1

myIsNeg :: Int -> Bool
myIsNeg x
    | x < 0 = True
    | otherwise = False

myAbs :: Int -> Int
myAbs x
    | x < 0 = -x
    | otherwise = x

myMin :: Int -> Int -> Int
myMin x y
    | x < y = x
    | otherwise = y

myMax :: Int -> Int -> Int
myMax x y
    | x > y = x
    | otherwise = y

myTuple :: a -> b -> (a, b)
myTuple arg1 arg2 = (arg1, arg2)

myTruple :: a -> b -> c -> (a, b, c)
myTruple arg1 arg2 arg3 = (arg1, arg2, arg3)

myFst :: (a, b) -> a
myFst (x, _) = x

mySnd :: (a, b) -> b
mySnd (_, x) = x

mySwap :: (a, b) -> (b, a)
mySwap (x, y) = (y, x)

myHead :: [a] -> a
myHead [] = error "The list is empty"
myHead (x:_) = x

myTail :: [a] -> [a]
myTail [] = error "The list is empty"
myTail (_:x) = x

myLength :: [a] -> Int
myLength [] = 0
myLength (_:x) = 1 + (myLength x)

myNth :: [a] -> Int -> a
myNth [] _ = error "There is nothing at this index"
myNth (x:_) 0 = x
myNth (_:x) n = myNth x (n-1)

myTake :: Int -> [a] -> [a]
myTake n (x:y)
    | n >= myLength (x:y) || n < 0 = (x:y)
    | n == 0 = []
    | otherwise = (x:(myTake (n-1) y))

myDrop :: Int -> [a] -> [a]
myDrop n (x:y)
    | n >= myLength (x:y) || n < 0 = []
    | n == 0 = (x:y)
    | otherwise = myDrop (n-1) y

myAppend :: [a] -> [a] -> [a]
myAppend [] x = x
myAppend x y = myAppend (myTake ((myLength x) -1) x) 
                        ((myNth x ((myLength x) -1)):y)

myReverse2 :: [a] -> [a] -> [a]
myReverse2 [] x = x
myReverse2 (x:y) z = myReverse2 y (x:z)

myReverse :: [a] -> [a]
myReverse x = myReverse2 x []

myInit :: [a] -> [a]
myInit [] = error "The list is empty"
myInit x = myTake ((myLength x)-1) x

myLast :: [a] -> a
myLast [] = error "The list is empty"
myLast x = myNth x ((myLength x)-1)

myZip :: [a] -> [b] -> [(a, b)]
myZip [] _ = []
myZip _ [] = []
myZip (x:xs) (y:ys) = ((x,y):(myZip xs ys))

myUnzip :: [(a, b)] -> ([a], [b])
myUnzip [] = ([],[])
myUnzip (x:y) = ((myFst x:myFst (myUnzip y)),
                 (mySnd x:mySnd (myUnzip y)))

myMap :: (a -> b) -> [a] -> [b]
myMap funct [] = []
myMap funct (x:y) = (funct x:myMap funct y)

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter funct [] = []
myFilter funct (x:y) 
    | funct x == True = (x:myFilter funct y)
    | otherwise = (myFilter funct y)

myFoldl :: (b -> a -> b) -> b -> [a] -> b
myFoldl funct x [] = x
myFoldl funct x (y:z) = myFoldl funct (funct x y) z

myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr funct x [] = x
myFoldr funct x y = myFoldr funct (funct (myLast y) x) (myInit y)

mySpan :: (a -> Bool) -> [a] -> ([a], [a])
mySpan funct [] = ([],[])
mySpan funct (x:y)
    | funct x == True = ((x:(myFst (mySpan funct y))),(mySnd (mySpan funct y)))
    | otherwise = ((myFst (mySpan funct y)), (x:(mySnd (mySpan funct y))))

myQuickSort :: (a -> a -> Bool) -> [a] -> [a]
myQuickSort funct [] = []
myQuickSort funct (x:y) = myAppend (myQuickSort funct (myFst (mySpan (\ z -> funct z x) y)))
                                   (myAppend [x] (myQuickSort funct (mySnd (mySpan (\ z -> funct z x) y))))

