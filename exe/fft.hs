-- fft.hs

{-# LANGUAGE OverloadedStrings #-}

module Main where

import qualified Control.Exception as E
import qualified Data.Text as T

import qualified CPython as Py
import qualified CPython.Protocols.Object as Py
import qualified CPython.Protocols.Iterator as Py
import qualified CPython.Types as Py
import qualified CPython.Types.Module as Py
import qualified CPython.Types.Exception as Py
import qualified CPython.Protocols.Sequence as PySeq

import Control.Arrow (second)
import Control.Monad (forM_, (>=>))
import Control.Monad.Loops (whileJust)
import Data.Complex
import Data.Maybe (fromJust)
import System.FilePath (splitExtension)
import System.IO (stdout)

n   = 8       -- test vector length
eps = 0.0001  -- threshold for floating point equality

tests :: [([Double],[Complex Double])]
tests = [delta n, cnst n, square n]

main :: IO ()
main = do
  Py.initialize

  E.handle onException $ do
    fft <- getPyFunc "numpy.fft.fft"
    forM_ tests $ \(xs,ys) -> do
      print xs
      ys' <- callPyFunc fft xs
      print ys'
      print $ if all2 (~=) ys' ys then "Pass"
                                  else ("Fail: " ++ show ys')
    putStrLn "Test complete."

getPyFunc :: String -> IO Py.SomeObject
getPyFunc fName = do
  mod <- Py.importModule modStr
  Py.getAttribute mod =<< Py.toUnicode funStr
 where
  (modStr, funStr) = toBoth T.pack $ second tail $ splitExtension fName

toBoth :: (a -> b) -> (a,a) -> (b,b)
toBoth f (x,y) = (f x, f y)

-- TODO: Generalize this.
-- (Might need to use Singletons.)
callPyFunc :: Py.SomeObject -> [Double] -> IO [Complex Double]
callPyFunc f xs = do
  xs'  <- pyList xs
  res  <- Py.callArgs f [Py.toObject xs']
  hsList res
  
-- TODO: Generalize the following 2 functions.
-- (~=) :: (Floating a, Floating b) => a -> b -> Bool
(~=) :: Complex Double -> Complex Double -> Bool
(xr :+ xi) ~= (yr :+ yi) =
  abs (xr - yr) < eps
  && abs (xi - yi) < eps

all2 :: (a -> b -> Bool) -> [a] -> [b] -> Bool
all2 f xs ys = all (uncurry f) $ zipWith (,) xs ys

onException :: Py.Exception -> IO ()
onException exc = Py.print (Py.exceptionValue exc) stdout

pyList :: [Double] -> IO Py.List
pyList = mapM (fmap Py.toObject . Py.toFloat) >=> Py.toList

hsList :: Py.SomeObject -> IO [Complex Double]
hsList =
  PySeq.castToSequence
  >=> (PySeq.toList . fromJust)
  >=> Py.fromList
  >=> mapM Py.cast
  >=> mapM (Py.fromComplex . fromJust)

type TestVec = Int -> ([Double],[Complex Double])

delta :: TestVec
delta n =
  ( 1.0 : replicate (n-1) 0.0
  , replicate n 1.0
  )
  
cnst :: TestVec
cnst n =
  ( replicate n 1.0
  , fromIntegral n * 1.0 : replicate (n-1) 0.0
  )
  
square :: TestVec
square n =
  ( replicate (n `div` 2) 1.0 ++ replicate (n `div` 2) 0.0
  , [ 4.0 :+ 0.0, 1.0 :+ (-2.41421356), 0.0 :+ 0.0, 1.0 :+ (-0.41421356)
    , 0.0 :+ 0.0, 1.0 :+ 0.41421356,   0.0 :+ 0.0, 1.0 :+ 2.41421356
    ]
  )
