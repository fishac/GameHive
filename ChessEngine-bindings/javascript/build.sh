#!/bin/ash

mkdir build
cd build
mkdir lib
cp ../../../ChessCore ./lib -r
cp ../../../ChessEngine ./lib -r
docker run --rm -v $(pwd)/..:/src -u $(id -u):$(id -g) emscripten/emsdk emcmake cmake
docker run --rm -v $(pwd)/..:/src -u $(id -u):$(id -g) emscripten/emsdk make 
