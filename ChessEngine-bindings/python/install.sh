#!/bin/bash

export CMAKE_GENERATOR="MinGW Makefiles"
export ChessEnginePythonBindDir=`pwd`

echo "Running command [ pip install . ] with env vars: CMAKE_GENERATOR=${CMAKE_GENERATOR}, ChessEnginePythonBindDir=${ChessEnginePythonBindDir}"

pip install .