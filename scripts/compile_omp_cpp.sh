#!/bin/sh
# Compile C++ OpenMP Files (ARM64 Exclusive)

echo "Enter you OpenMP program filename (without extension): "
read filename

clang++ -Xclang\
    -fopenmp -L/usr/local/opt/libomp/lib -I/usr/local/opt/libomp/include\
    -lomp $filename.cpp -o $filename

./$filename



