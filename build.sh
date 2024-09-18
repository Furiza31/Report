#!/bin/bash

# Build for Linux
mkdir -p build_linux
cd build_linux
cmake ..
make
cd ..

# Build for Windows
mkdir -p build_windows
cd build_windows
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
make
cd ..

echo "Build complete: Linux in build_linux/, Windows in build_windows/"
