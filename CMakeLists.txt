cmake_minimum_required(VERSION 3.0)
project(ModulePython)

set(CMAKE_CXX_STANDARD 14)

set (
        ${PROJECT_NAME}_SOURCE
        library.cpp
)

add_library(
        mtasa_module_python
        SHARED
        ${${PROJECT_NAME}_SOURCE}
)