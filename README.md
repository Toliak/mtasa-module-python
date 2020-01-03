[![Build Status](https://travis-ci.com/Toliak/mtasa-module-python.svg?branch=master)](https://travis-ci.com/Toliak/mtasa-module-python)
[![pipeline status](https://gitlab.toliak.ru/mtasa/module-python/badges/master/pipeline.svg)](https://gitlab.toliak.ru/mtasa/module-python/commits/some-trash)
![Code size](https://img.shields.io/github/languages/code-size/Toliak/mtasa-module-python.svg)
![GitHub Repo size](https://img.shields.io/github/repo-size/Toliak/mtasa-module-python.svg)

# MTASA Module Python

Full Python 3.7.6 support for server-side scripts

## Tutorial

TODO

## Lua API

### pythonInit

``int[, string] pythonInit(table moduleNames)``

Initializes Python VM and loads modules.

#### Arguments

``table moduleNames`` - list of module names (strings)

#### Return

Amount of loaded modules, if success. 
Exit code and error message, otherwise.

### pythonDestroy

``pythonDestroy()``

Destroys Python VM

#### Return

Nothing

### isPythonInited

``bool isPythonInited()``

Checks is Python VM already created.

#### Return

True, if Python VM is created. False otherwise.

### pythonCall

``[return_args ...] pythonCall(string moduleName, string functionName [, arguments ...])``

Calls function from Python VM

#### Arguments

``string moduleName`` - Python module name

``string functionName`` - Python function name

``[arguments ...]`` - Arguments to pass to Python function

Allowed argument types: string, number, boolean, table, Element

#### Return

Returned values from Python function, or negative int and string on error

#### Throws

Prints error into console

## Python API

### mtasa.core.call

``any call(str function_name, int return_args_amount, *args)``

Calls any global Lua function (from resources, also) 

#### Arguments

``str function_name`` - name of Lua function

``str return_args_amount`` - amount of returned arguments

``*args`` - arguments to pass to Lua function 

Allowed argument types: string, number, boolean, list, dict, Element (or subclasses)

#### Return

Returned values from Lua function

### mtasa.core.call_method

``any call(Element element, str method_name, int return_args_amount, *args)``

Calls any global Lua function (from resources, also) 

#### Arguments

``Element element`` - MTASA Element

``str method_name`` - name of Lua method

``str return_args_amount`` - amount of returned arguments

``*args`` - arguments to pass to Lua method 

#### Return

Returned values from Lua method

## References

Origin: [https://gitlab.toliak.ru/mtasa/module-python](https://gitlab.toliak.ru/mtasa/module-python)

Mirror: [https://github.com/Toliak/mtasa-module-python](https://github.com/Toliak/mtasa-module-python)