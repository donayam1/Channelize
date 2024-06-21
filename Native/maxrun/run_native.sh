#! /bin/bash
dir="../../Data/result/maxrun/native/total/do_snoopy/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/maxrun/do/*
do

  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))

  echo $fn
  ./main_snoopy "$fn" "$file" "${a[1]}"
done
