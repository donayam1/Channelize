#! /bin/bash
dir="../../Data/result/frequency/se/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/frequency/do_se/*
do  
  echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))
  ./main "$fn" "$file" "${a[1]}" "${a[2]}"  
done