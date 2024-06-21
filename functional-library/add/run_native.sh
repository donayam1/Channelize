#! /bin/bash
dir="../../Data/result/add/se/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

for i in {0..500}
do 
  echo $i
  for file in ../../Data/input/add/do/*
  do  
    echo $file
    bn="$(basename $file)"     
    fn=$dir$i$bn
    x=$bn
    a=($(echo $x | tr '_' "\n"))
    ./main "$fn" "$file" "${a[1]}" "${a[2]}"
  done
done 