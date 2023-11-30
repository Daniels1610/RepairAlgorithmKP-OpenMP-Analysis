#!/bin/sh
# Compile C++ Files (macOS Exclusive)

echo "Enter you C++ program filename (without extension): "
read filename

g++ -o "$filename" "$filename.cpp"
./"$filename"