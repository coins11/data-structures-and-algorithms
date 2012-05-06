module Main where

data Stream a = Stream a (Stream a) deriving Show

stail :: Stream a -> Stream a
stail (Stream _ t) = t

sZipWith :: (a -> b -> c) -> Stream a -> Stream b -> Stream c
sZipWith f (Stream a at) (Stream b bt) = Stream (f a b) (sZipWith f at bt)

stake :: Integral num => num -> Stream a -> [a]
stake 0 _ = []
stake n (Stream a at) = a : stake (pred n) at

fibs :: Stream Integer
fibs = Stream 0 (Stream 1 (sZipWith (+) fibs (stail fibs)))

gcdc :: Integer -> Integer -> Int
gcdc a b | a < b = gcdc b a
gcdc a b | b == 0 = 1
gcdc a b = succ $ gcdc b $ mod a b

test :: [(Integer, Integer, Bool)]
test = do
    (a, b) <- stake 50 $ sZipWith (,) fibs $ stail fibs
    return (a, b, maximum (0 : map (flip gcdc b) [a..pred b]) <= gcdc a b)
