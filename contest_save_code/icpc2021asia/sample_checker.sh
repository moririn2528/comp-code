#!/bin/bash
g++ $1 -std=c++17 -O2 -o $1.exe
for file in `find $2 -type f -name *.in`;
do
  echo $file
  ./$1.exe < $file > tmp
  diff tmp ${file/in/out}
  rm tmp
done
rm $1.exe