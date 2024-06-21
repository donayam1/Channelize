#! /bin/bash
dir="Data/result/add/sgx/total/do/"
mkdir -p "$dir" && echo "Directory created : $dir" 

for i in {0..300}
do 
  echo $i
  for file in Data/input/add/do/*
  do  
    #echo $file
    bn="$(basename $file)"     
    fn=$dir$i$bn
    x=$bn
    a=($(echo $x | tr '_' "\n"))
    echo $fn
    ./app "$fn" "$file" "${a[1]}" "${a[2]}"
  done
done 
