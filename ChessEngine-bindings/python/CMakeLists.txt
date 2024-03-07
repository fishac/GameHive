cmake_minimum_required(VERSION 3.16)
project(ChessEnginePython)

add_subdirectory($ENV{ChessEnginePythonBindDir}/../../ChessCore ChessCore)
add_subdirectory($ENV{ChessEnginePythonBindDir}/../../ChessEngine ChessEngine)

find_package(pybind11 REQUIRED)
pybind11_add_module(ChessEnginePython src/ChessEnginePython.cpp)

target_link_libraries(ChessEnginePython PRIVATE ChessEngine)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(ChessEnginePython PRIVATE VERSION_INFO=${VERSION_INFO})