[![Build Status](https://travis-ci.com/Toliak/mtasa-module-python.svg?branch=master)](https://travis-ci.com/Toliak/mtasa-module-python)
[![pipeline status](https://gitlab.toliak.ru/mtasa/module-python/badges/master/pipeline.svg)](https://gitlab.toliak.ru/mtasa/module-python/commits/some-trash)
![Code size](https://img.shields.io/github/languages/code-size/Toliak/mtasa-module-python.svg)
![GitHub Repo size](https://img.shields.io/github/repo-size/Toliak/mtasa-module-python.svg)

# MTASA Module Python

Full Python 3.7.6 support for server-side scripts 

## Tutorial

TODO

## API

### pythonInit

``int[, string] pythonInit(table moduleNames)``

Initializes Python VM and loads modules

#### Arguments

``table moduleNames`` - list of module names (strings)

#### Return

Amount of loaded modules, if success. 
Exit code and error message, otherwise.

### isPythonInited

``bool isPythonInited()``

Checks is Python VM already created

#### Return

True, if Python VM is created. False otherwise.

### pythonCall

``[return_args ...] pythonCall(string moduleName, string functionName [, arguments ...])``

TODO

## References

Origin: [https://gitlab.toliak.ru/mtasa/module-python](https://gitlab.toliak.ru/mtasa/module-python)

Mirror: [https://github.com/Toliak/mtasa-module-python](https://github.com/Toliak/mtasa-module-python)