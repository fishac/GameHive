mkdir -p build/lib
mkdir build/src
cd build
cp ../../../ChessCore ./lib -r
cp ../../../ChessEngine ./lib -r
cp ../src/*.cpp ./src
cp ../CMakeLists.txt .
docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) emscripten/emsdk emcmake cmake -DBUILD_FOR_WEB=1
docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) emscripten/emsdk make 

