#!/bin/sh
# Compile C++ OpenMP Files (macOS Exclusive)

echo "Enter you OpenMP program filename (without extension): "
read filename

echo "Threads to rise: "
read threads 

clang++ -Xclang\
    -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include\
    -lomp "$filename.cpp" -o "$filename"

./"$filename" $threads 