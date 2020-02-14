/**
 * Copyright (C) 2009 John Millikin <jmillikin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <hscpython-shim.h>
#include <execinfo.h>

int notified = 0;

// DEPRECATION WARNINGS: TODO fix
/////////////////////////////////
/*  cbits/hscpython-shim.c: In function ‘hscpython_PyUnicode_GetSize’: */
/*   */
/*  ./haskell-cpython/cbits/hscpython-shim.c:282:3: error: */
/*       warning: ‘PyUnicode_GetSize’ is deprecated [-Wdeprecated-declarations] */
/*         return PyUnicode_GetSize(o); */
/*         ^~~~~~ */
/*      | */
/*  282 |   return PyUnicode_GetSize(o); */
/*      |   ^ */
/*  In file included from /usr/include/python3.8/Python.h:97, */
/*                   from cbits/hscpython-shim.h:4, */
/*   */
/*  ./haskell-cpython/                 from cbits/hscpython-shim.c:18:0: error:  */
/*   */
/*  ./haskell-cpython//usr/include/python3.8/unicodeobject.h:177:43: error: */
/*       note: declared here */
/*       Py_DEPRECATED(3.3) PyAPI_FUNC(Py_ssize_t) PyUnicode_GetSize( */
/*                                                 ^~~~~~~~~~~~~~~~~ */
/*      | */
/*  177 | Py_DEPRECATED(3.3) PyAPI_FUNC(Py_ssize_t) PyUnicode_GetSize( */
/*      |                                           ^ */
/*  cbits/hscpython-shim.c: In function ‘hscpython_PyUnicode_GetSize’: */
/*   */
/*  ./haskell-cpython/cbits/hscpython-shim.c:282:3: error: */
/*       warning: ‘PyUnicode_GetSize’ is deprecated [-Wdeprecated-declarations] */
/*         return PyUnicode_GetSize(o); */
/*         ^~~~~~ */
/*      | */
/*  282 |   return PyUnicode_GetSize(o); */
/*      |   ^ */
/*  In file included from /usr/include/python3.8/Python.h:97, */
/*                   from cbits/hscpython-shim.h:4, */
/*   */
/*  ./haskell-cpython/                 from cbits/hscpython-shim.c:18:0: error:  */
/*   */
/*  ./haskell-cpython//usr/include/python3.8/unicodeobject.h:177:43: error: */
/*       note: declared here */
/*       Py_DEPRECATED(3.3) PyAPI_FUNC(Py_ssize_t) PyUnicode_GetSize( */
/*                                                 ^~~~~~~~~~~~~~~~~ */
/*      | */
/*  177 | Py_DEPRECATED(3.3) PyAPI_FUNC(Py_ssize_t) PyUnicode_GetSize( */
/*      |                                           ^ */


/* Initialization helpers */
static wchar_t *program_name = NULL;
static wchar_t *python_home = NULL;

static wchar_t *hscpython_wcsdup(wchar_t *s)
{
  // printf("hscpython_wcsdup in\n");
	size_t len = 0;
	wchar_t *orig = s, *new, *new0;

	if (!s) {
		return s;
	}

	while (*(s++)) {
		len++;
	}

	new = new0 = malloc(sizeof(wchar_t) * len);
	s = orig;
	while (*(new++) = *(s++)) {
	}
  // printf("hscpython_wcsdup out\n");
	return new0;
}

void hscpython_SetProgramName(wchar_t *s)
{
  // printf("hscpython_SetProgramName\n");
	free(program_name);
	program_name = hscpython_wcsdup(s);
	Py_SetProgramName(program_name);
  // printf("hscpython_SetProgramName out\n");
}

void hscpython_SetPythonHome(wchar_t *s)
{
  // printf("hscpython_SetPythonHome\n");
	free(python_home);
	python_home = hscpython_wcsdup(s);
	Py_SetPythonHome(python_home);
  // printf("hscpython_SetPythonHome out\n");
}

/* Object */
void hscpython_Py_INCREF(PyObject *o)
{
  // printf("hscpython_Py_INCREF\n");
  Py_INCREF(o);
  // printf("hscpython_Py_INCREF out\n");
}

void hscpython_Py_DECREF(PyObject *o)
{
  // printf("hscpython_Py_DECREF, %p\n", o);
  /* void *array[10]; */
  /* size_t size; */
  /* char **strings; */
  /* size_t i; */

  /* size = backtrace(array, 10); */
  /* strings = backtrace_symbols (array, size); */
  /* // printf ("Obtained %zd stack frames.\n", size); */
  /* for (i = 0; i < size; i++) */
  /*    // printf ("%s\n", strings[i]); */
  /* free (strings); */
  
  if (notified == 0) {
    printf("\n\nIMPORTANT WARNING: Due to a SIGSEGV error decreasing the reference counter is disabled. Thus using this library will likely cause a memory leak!\n\n");
    notified = 1;
  }
  /* Py_DECREF(o); */
  // printf("hscpython_Py_DECREF out\n");
}

int hscpython_PyObject_DelAttr(PyObject *o, PyObject *name)
{
  // printf("hscpython_PyObject_DelAttr\n");
  return PyObject_DelAttr(o, name);
  // printf("hscpython_PyObject_DelAttr out\n");
}

int hscpython_PyObject_TypeCheck(PyObject *o, PyTypeObject *type)
{
  // printf("hscpython_PyObject_TypeCheck\n");
  return PyObject_TypeCheck(o, type);
  // printf("hscpython_PyObject_TypeCheck out\n");
}

int hscpython_PyIter_Check(PyObject *o)
{
  // printf("hscpython_PyIter_Check\n");
  return PyIter_Check(o);
  // printf("hscpython_PyIter_Check out\n");
}

/* Types */
PyTypeObject *hscpython_PyType_Type()
{
  // printf("*hscpython_PyType_Type\n");
  return &PyType_Type;
  // printf("*hscpython_PyType_Type out\n");
}

PyTypeObject *hscpython_PyTuple_Type()
{
  // printf("*hscpython_PyTuple_Type\n");
  // printf("hscpython_PyTuple_Type\n");
  return &PyTuple_Type;
  // printf("*hscpython_PyTuple_Type out\n");
}

PyTypeObject *hscpython_PyList_Type()
{
  // printf("*hscpython_PyList_Type\n");
  return &PyList_Type;
  // printf("*hscpython_PyList_Type out\n");
}

PyTypeObject *hscpython_PyDict_Type()
{
  // printf("*hscpython_PyDict_Type\n");
  return &PyDict_Type;
  // printf("*hscpython_PyDict_Type out\n");
}

PyTypeObject *hscpython_PyLong_Type()
{
  // printf("*hscpython_PyLong_Type\n");
  return &PyLong_Type;
  // printf("*hscpython_PyLong_Type out\n");
}

PyTypeObject *hscpython_PyFloat_Type()
{
  // printf("*hscpython_PyFloat_Type\n");
  return &PyFloat_Type;
  // printf("*hscpython_PyFloat_Type out\n");
}

PyTypeObject *hscpython_PyComplex_Type()
{
  // printf("*hscpython_PyComplex_Type\n");
  return &PyComplex_Type;
  // printf("*hscpython_PyComplex_Type out\n");
}

PyTypeObject *hscpython_PyUnicode_Type()
{
  // printf("*hscpython_PyUnicode_Type\n");
  return &PyUnicode_Type;
  // printf("*hscpython_PyUnicode_Type out\n");
}

PyTypeObject *hscpython_PyBytes_Type()
{
  // printf("*hscpython_PyBytes_Type\n");
  return &PyBytes_Type;
  // printf("*hscpython_PyBytes_Type out\n");
}

PyTypeObject *hscpython_PyByteArray_Type()
{
  // printf("*hscpython_PyByteArray_Type\n");
  return &PyByteArray_Type;
  // printf("*hscpython_PyByteArray_Type out\n");
}

PyTypeObject *hscpython_PyCell_Type()
{
  // printf("*hscpython_PyCell_Type\n");
  return &PyCell_Type;
  // printf("*hscpython_PyCell_Type out\n");
}

PyTypeObject *hscpython_PyCode_Type()
{
  // printf("*hscpython_PyCode_Type\n");
  return &PyCode_Type;
  // printf("*hscpython_PyCode_Type out\n");
}

PyTypeObject *hscpython_PyFunction_Type()
{
  // printf("*hscpython_PyFunction_Type\n");
  return &PyFunction_Type;
  // printf("*hscpython_PyFunction_Type out\n");
}

PyTypeObject *hscpython_PyInstanceMethod_Type()
{
  // printf("*hscpython_PyInstanceMethod_Type\n");
  return &PyInstanceMethod_Type;
  // printf("*hscpython_PyInstanceMethod_Type out\n");
}

PyTypeObject *hscpython_PyMethod_Type()
{
  // printf("*hscpython_PyMethod_Type\n");
  return &PyMethod_Type;
  // printf("*hscpython_PyMethod_Type out\n");
}

PyTypeObject *hscpython_PySet_Type()
{
  // printf("*hscpython_PySet_Type\n");
  return &PySet_Type;
  // printf("*hscpython_PySet_Type out\n");
}

PyTypeObject *hscpython_PyFrozenSet_Type()
{
  // printf("*hscpython_PyFrozenSet_Type\n");
  return &PyFrozenSet_Type;
  // printf("*hscpython_PyFrozenSet_Type out\n");
}

PyTypeObject *hscpython_PySeqIter_Type()
{
  // printf("*hscpython_PySeqIter_Type\n");
  return &PySeqIter_Type;
  // printf("*hscpython_PySeqIter_Type out\n");
}

PyTypeObject *hscpython_PyCallIter_Type()
{
  // printf("*hscpython_PyCallIter_Type\n");
  return &PyCallIter_Type;
  // printf("*hscpython_PyCallIter_Type out\n");
}

PyTypeObject *hscpython_PySlice_Type()
{
  // printf("*hscpython_PySlice_Type\n");
  return &PySlice_Type;
  // printf("*hscpython_PySlice_Type out\n");
}

PyTypeObject *hscpython_PyModule_Type()
{
  // printf("*hscpython_PyModule_Type\n");
  return &PyModule_Type;
  // printf("*hscpython_PyModule_Type out\n");
}

PyTypeObject *hscpython_PyCapsule_Type()
{
  // printf("*hscpython_PyCapsule_Type\n");
  return &PyCapsule_Type;
  // printf("*hscpython_PyCapsule_Type out\n");
}

/* Constants */
PyObject *hscpython_Py_None()
{
  // printf("*hscpython_Py_None\n");
  return Py_None;
  // printf("*hscpython_Py_None out\n");
}

PyObject *hscpython_Py_True()
{
  // printf("*hscpython_Py_True\n");
  return Py_True;
  // printf("*hscpython_Py_True out\n");
}

PyObject *hscpython_Py_False()
{
  // printf("*hscpython_Py_False\n");
  return Py_False;
  // printf("*hscpython_Py_False out\n");
}

/* Unicode */
Py_ssize_t hscpython_PyUnicode_GetSize(PyObject *o)
{
  // printf("hscpython_PyUnicode_GetSize\n");
  return PyUnicode_GetSize(o);
  // printf("hscpython_PyUnicode_GetSize out\n");
}

Py_UNICODE *hscpython_PyUnicode_AsUnicode(PyObject *o)
{
  // printf("UNICODE *hscpython_PyUnicode_AsUnicode\n");
  return PyUnicode_AsUnicode(o);
  // printf("UNICODE *hscpython_PyUnicode_AsUnicode out\n");
}

PyObject *hscpython_PyUnicode_FromUnicode(Py_UNICODE *u, Py_ssize_t size)
{
  // printf("*hscpython_PyUnicode_FromUnicode\n");
  return PyUnicode_FromUnicode(u, size);
  // printf("*hscpython_PyUnicode_FromUnicode out\n");
}

PyObject *hscpython_PyUnicode_FromEncodedObject(PyObject *o, const char *enc, const char *err)
{
  // printf("*hscpython_PyUnicode_FromEncodedObject\n");
  return PyUnicode_FromEncodedObject(o, enc, err);
  // printf("*hscpython_PyUnicode_FromEncodedObject out\n");
}

PyObject *hscpython_PyUnicode_AsEncodedString(PyObject *o, const char *enc, const char *err)
{
  // printf("*hscpython_PyUnicode_AsEncodedString\n");
  return PyUnicode_AsEncodedString(o, enc, err);
  // printf("*hscpython_PyUnicode_AsEncodedString out\n");
}

PyObject *hscpython_PyUnicode_FromObject(PyObject *o)
{
  // printf("*hscpython_PyUnicode_FromObject\n");
  return PyUnicode_FromObject(o);
  // printf("*hscpython_PyUnicode_FromObject out\n");
}

PyObject *hscpython_PyUnicode_Decode(const char *s, Py_ssize_t len, const char *enc, const char *err)
{
  // printf("*hscpython_PyUnicode_Decode\n");
  return PyUnicode_Decode(s, len, enc, err);
  // printf("*hscpython_PyUnicode_Decode out\n");
}

PyObject *hscpython_PyUnicode_Concat(PyObject *l, PyObject *r)
{
  // printf("*hscpython_PyUnicode_Concat\n");
  return PyUnicode_Concat(l, r);
  // printf("*hscpython_PyUnicode_Concat out\n");
}

PyObject *hscpython_PyUnicode_Split(PyObject *s, PyObject *sep, Py_ssize_t max)
{
  // printf("*hscpython_PyUnicode_Split\n");
  return PyUnicode_Split(s, sep, max);
  // printf("*hscpython_PyUnicode_Split out\n");
}

PyObject *hscpython_PyUnicode_Splitlines(PyObject *s, int keep)
{
  // printf("*hscpython_PyUnicode_Splitlines\n");
  return PyUnicode_Splitlines(s, keep);
  // printf("*hscpython_PyUnicode_Splitlines out\n");
}

PyObject *hscpython_PyUnicode_Translate(PyObject *str, PyObject *table, const char *err)
{
  // printf("*hscpython_PyUnicode_Translate\n");
  return PyUnicode_Translate(str, table, err);
  // printf("*hscpython_PyUnicode_Translate out\n");
}

PyObject *hscpython_PyUnicode_Join(PyObject *sep, PyObject *seq)
{
  // printf("*hscpython_PyUnicode_Join\n");
  return PyUnicode_Join(sep, seq);
  // printf("*hscpython_PyUnicode_Join out\n");
}

int hscpython_PyUnicode_Tailmatch(PyObject *str, PyObject *substr, Py_ssize_t start, Py_ssize_t end, int dir)
{
  // printf("hscpython_PyUnicode_Tailmatch\n");
  return PyUnicode_Tailmatch(str, substr, start, end, dir);
  // printf("hscpython_PyUnicode_Tailmatch out\n");
}

Py_ssize_t hscpython_PyUnicode_Find(PyObject *str, PyObject *substr, Py_ssize_t start, Py_ssize_t end, int dir)
{
  // printf("hscpython_PyUnicode_Find\n");
  return PyUnicode_Find(str, substr, start, end, dir);
  // printf("hscpython_PyUnicode_Find out\n");
}

Py_ssize_t hscpython_PyUnicode_Count(PyObject *str, PyObject *substr, Py_ssize_t start, Py_ssize_t end)
{
  // printf("hscpython_PyUnicode_Count\n");
  return PyUnicode_Count(str, substr, start, end);
  // printf("hscpython_PyUnicode_Count out\n");
}

PyObject *hscpython_PyUnicode_Replace(PyObject *str, PyObject *substr, PyObject *replstr, Py_ssize_t max)
{
  // printf("*hscpython_PyUnicode_Replace\n");
  return PyUnicode_Replace(str, substr, replstr, max);
  // printf("*hscpython_PyUnicode_Replace out\n");
}

PyObject *hscpython_PyUnicode_Format(PyObject *format, PyObject *args)
{
  // printf("*hscpython_PyUnicode_Format\n");
  return PyUnicode_Format(format, args);
  // printf("*hscpython_PyUnicode_Format out\n");
}

int hscpython_PyUnicode_Contains(PyObject *a, PyObject *b)
{

  // printf("hscpython_PyUnicode_Contains\n");
  return PyUnicode_Contains(a, b);
  // printf("hscpython_PyUnicode_Contains out\n");
}

/* Lists */
void hscpython_peek_list(PyObject *list, Py_ssize_t size, PyObject **objs)
{
  // printf("hscpython_peek_list in\n");
	Py_ssize_t ii;

	for (ii = 0; ii < size; ii++) {
		objs[ii] = PyList_GET_ITEM(list, ii);
	}
  // printf("hscpython_peek_list out\n");
}

PyObject *hscpython_poke_list(size_t count, PyObject **objs)
{
  // printf("hscpython_poke_list in\n");
	PyObject *list;
	size_t ii;

	if (!(list = PyList_New(count))) {
		return NULL;
	}

	for (ii = 0; ii < count; ii++) {
		Py_INCREF(objs[ii]);
		PyList_SET_ITEM(list, ii, objs[ii]);
	}
  // printf("hscpython_poke_list out\n");
	return list;
}

/* Tuples */
void hscpython_peek_tuple(PyObject *tuple, Py_ssize_t size, PyObject **objs)
{
  // printf("peek_tuple in: %d\n", size);
	Py_ssize_t ii;

	for (ii = 0; ii < size; ii++) {
		objs[ii] = PyTuple_GET_ITEM(tuple, ii);
	}
  // printf("peek_tuple out\n");
}

PyObject *hscpython_poke_tuple(size_t count, PyObject **objs)
{
  // printf("tuple in\n");
	PyObject *tuple;
	size_t ii;

	if (!(tuple = PyTuple_New(count))) {
		return NULL;
	}

	for (ii = 0; ii < count; ii++) {
		Py_INCREF(objs[ii]);
		PyTuple_SET_ITEM(tuple, ii, objs[ii]);
	}
  // printf("tuple out\n");
	return tuple;
}
