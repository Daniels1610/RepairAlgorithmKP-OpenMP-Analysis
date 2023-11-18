#!/bin/sh
# Executes a C++ OpenMP program and outputs the result into a CSV file

EXECUTION_NUM=5

echo "Enter you OpenMP program filename (without extension): "
read filename

clang++ -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp "$filename.cpp" -o "$filename"
echo "1thExec, 2thExec, 3rdExec, 4thExec, 5thExec" >> results/rpa_serial.csv

for i in {1}; do
    for j in {1..$EXECUTION_NUM}; do
        time=$(./"$filename" $i)
        if [ $j -eq 5 ]; then end=""
        else end=", "; fi
        printf "$time$end" >> results/rpa_serial.csv
    done
    printf "\n" >> results/rpa_serial.csv
done
