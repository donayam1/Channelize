#! /bin/bash
dir="../../Data/result/add/native/total/normal/"
mkdir -p "$dir" && echo "Directory created: $dir"

for i in {0..500}
do 
  echo $i
  for file in ../../Data/input/add/normal/*
  do  
    
    bn="$(basename $file)"     
    fn=$dir$i$bn
    x=$bn
    a=($(echo $x | tr '_' "\n"))
    echo $fn
    ./main "$fn" "$file" "${a[1]}" "${a[2]}"
  done
done 