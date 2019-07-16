cmake_minimum_required(VERSION 3.14)
project(mtasa_module_python)

set(CMAKE_CXX_STANDARD 14)

add_library(mtasa_module_python SHARED library.cpp library.h)