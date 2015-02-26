#!/bin/bash

mismatches=4

rm result.txt
touch result.txt

for str in $(cat patterns.txt); do
    ./a.exe test.txt $str $mismatches >> result.txt &
done
