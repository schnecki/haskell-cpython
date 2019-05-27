-- import.hs

{-# LANGUAGE OverloadedStrings #-}

module Main where

import qualified Data.Text as T
import System.IO (stdout)

import qualified CPython as Py
import qualified CPython.Protocols.Object as Py
import qualified CPython.Types as Py
import qualified CPython.Types.Module as Py

main :: IO ()
main = do
  Py.initialize

  os <- Py.importModule "os"
  uname <- Py.getAttribute os =<< Py.toUnicode "uname"
  res <- Py.callArgs uname []
  Py.print res stdout
