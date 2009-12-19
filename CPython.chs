-- Copyright (C) 2009 John Millikin <jmillikin@gmail.com>
-- 
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- any later version.
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
-- 
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.
-- 
{-# LANGUAGE ForeignFunctionInterface #-}
module CPython
	( initialize
	, isInitialized
	, finalize
	, newInterpreter
	, endInterpreter
	, getProgramName
	, getPrefix
	, getExecPrefix
	, getProgramFullPath
	, getPath
	, getVersion
	, getPlatform
	, getCopyright
	, getCompiler
	, getBuildInfo
	, getPythonHome
	) where
import CPython.Internal

#include <Python.h>

{# pointer *wchar_t as CWString nocode #}

{# fun Py_Initialize as initialize
	{} -> `()' id #}

{# fun Py_IsInitialized as isInitialized
	{} -> `Bool' #}

{# fun Py_Finalize as finalize
	{} -> `()' id #}

newtype ThreadState = ThreadState (Ptr ThreadState)

newInterpreter :: IO (Maybe ThreadState)
newInterpreter = do
	ptr <- {# call Py_NewInterpreter as ^ #}
	return $ if ptr == nullPtr
		then Nothing
		else Just $ ThreadState $ castPtr ptr

endInterpreter :: ThreadState -> IO ()
endInterpreter (ThreadState ptr) =
	{# call Py_EndInterpreter as ^ #} $ castPtr ptr

{# fun Py_GetProgramName as getProgramName
	{} -> `String' peekCWString* #}

-- setProgramName :: String -> IO ()

{# fun Py_GetPrefix as getPrefix
	{} -> `String' peekCWString* #}

{# fun Py_GetExecPrefix as getExecPrefix
	{} -> `String' peekCWString* #}

{# fun Py_GetProgramFullPath as getProgramFullPath
	{} -> `String' peekCWString* #}

{# fun Py_GetPath as getPath
	{} -> `String' peekCWString* #}

{# fun Py_GetVersion as getVersion
	{} -> `String' #}

{# fun Py_GetPlatform as getPlatform
	{} -> `String' #}

{# fun Py_GetCopyright as getCopyright
	{} -> `String' #}

{# fun Py_GetCompiler as getCompiler
	{} -> `String' #}

{# fun Py_GetBuildInfo as getBuildInfo
	{} -> `String' #}

-- setPythonHome :: String -> IO ()

{# fun Py_GetPythonHome as getPythonHome
	{} -> `String' peekCWString* #}
