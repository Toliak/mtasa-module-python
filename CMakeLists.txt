cmake_minimum_required(VERSION 3.4)
project(ModulePython)
option(BUILD_TESTS Off "Build tests")

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/ModuleSdk)

find_package(PythonLibs 3.6 REQUIRED)

set(
        ${PROJECT_NAME}_INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set(
        ${PROJECT_NAME}_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PythonModule.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PythonVm.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/pythonCallback.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/pythonCheck.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/pythonInit.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/pythonTriggerEvent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/globalLuaVm.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/Modules.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/MtasaCore.cpp
)

include_directories(
        ${${PROJECT_NAME}_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
)

add_library(
        ${PROJECT_NAME}
        SHARED
        ${${PROJECT_NAME}_SOURCE}
)

target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE
        "$<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIR}>")

target_link_libraries(
        ${PROJECT_NAME}
        ModuleSdk
        ${PYTHON_LIBRARY}
)

if (BUILD_TESTS)
    set(
            ${PROJECT_NAME}_SOURCE_TEST
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
    )

    add_executable(
            ${PROJECT_NAME}Tests
            ${${PROJECT_NAME}_SOURCE_TEST}
    )

    target_link_libraries(
            ${PROJECT_NAME}Tests
            ${PROJECT_NAME}
            ${CMAKE_DL_LIBS}
    )
endif ()