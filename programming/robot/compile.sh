#!/bin/bash
mkdir -p build
cp -r src/*.cpp build
cp -r src/*.h build
cp -r src/CMakeLists.txt build
pushd build
cmake .
make -j
./robot
popd
mvn compile
mvn test