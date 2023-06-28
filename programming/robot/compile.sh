#!/bin/bash
mkdir -p build
cp -r src/* build
pushd build
cmake .
make -j
popd
mvn build
mvn test