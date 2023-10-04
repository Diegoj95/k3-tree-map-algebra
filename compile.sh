#!/bin/sh

echo "Clean project"
sh ./clean.sh

echo "Create folder build"
mkdir -p build
cd build

echo "Run CMake"
cmake ..

echo "Run make"
make

echo "DONE!!!"