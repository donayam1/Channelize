#! /bin/bash
dir="Data/result/maxrun/sgx/total/do/"
mkdir -p "$dir" && echo "Directory Created: $dir"

for file in Data/input/maxrun/do/*
do
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))
  echo $fn
  ./app "$fn" "$file" "${a[1]}"
done
