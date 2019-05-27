-- version.hs
module Main where

import qualified Data.Text.IO as T
import qualified CPython as Py

main :: IO ()
main = do
  Py.initialize
  Py.getVersion >>= T.putStrLn
        
