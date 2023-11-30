#!/bin/sh
# Executes an C++ OpenMP program from 1 Thread through X Threads (macOS Exclusive)

THREADS_NUM=8
EXECUTION_NUM=5

echo "Enter you OpenMP program filename (without extension): "
read filename

echo "Which rpa are you running?: "
read type

clang++ -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp "$filename.cpp" -o "$filename"
echo "1thExec, 2thExec, 3rdExec, 4thExec, 5thExec" >> results/rpa_$type.csv

for i in {1..$THREADS_NUM}; do
    for j in {1..$EXECUTION_NUM}; do
        time=$(./"$filename" $i)
        if [ $j -eq 5 ]; then end=""
        else end=", "; fi
        printf "$time$end" >> results/rpa_$type.csv
    done
    printf "\n" >> results/rpa_$type.csv
done