#!/bin/sh

echo "Enter you OpenMP program filename (without extension): "
read filename

clang++ -Xclang\
    -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include\
    -lomp "$filename.cpp" -o "$filename"

./"$filename"



