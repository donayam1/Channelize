#! /bin/bash
dir="Data/result/contains/sgx/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir" 

for file in Data/input/contains/do/*
do  
  #echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))
  echo $fn
  ./app "$fn" "$file" "${a[1]}"
done
