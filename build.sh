#!/bin/bash

echo "Building..."

echo "Checking for dependencies..."
if ! [ -x "$(command -v cmake)" ]; then
  echo "Error: cmake is not installed." >&2
  exit 1
fi

if ! [ -x "$(command -v make)" ]; then
  echo "Error: make is not installed." >&2
  exit 1
fi

if ! [ -x "$(command -v g++)" ]; then
  echo "Error: g++ is not installed." >&2
  exit 1
fi

if ! [ -x "$(command -v x86_64-w64-mingw32-g++)" ]; then
  echo "Error: x86_64-w64-mingw32-g++ is not installed." >&2
  exit 1
fi

echo "Dependencies are installed."

echo "Building... on Linux"

mkdir -p build_linux
cd build_linux
cmake ..
make
cd ..

echo "Build complete: Linux in build_linux/"

echo "Building... on Windows"

mkdir -p build_windows
cd build_windows
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
make
cd ..

echo "Build complete: Windows in build_windows/"

echo "Build complete: Linux in build_linux/, Windows in build_windows/"

exit 0