#!/bin/bash

# Stop on errors.
set -e

# Format.
clang-format-11 src/**/*.h src/**/*.cc -i

# Configure the build.
cmake -B build -G Ninja

# Build the project
cmake --build build

cd build && ninja test
