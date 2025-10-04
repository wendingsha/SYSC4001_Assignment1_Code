#!/usr/bin/env bash
set -euo pipefail

# Ensure Linux line endings: run `dos2unix build.sh` once if needed

mkdir -p bin output_files

# Compile to bin/interrupts (note the name!)
g++ -std=c++17 -O2 -Wall -Wextra interrupts.cpp -o bin/interrupts

echo "Build complete -> bin/interrupts"
echo "Run with:"
echo "  ./bin/interrupts input_files/trace.txt input_files/vector_table.txt input_files/device_table.txt"
