#! /bin/bash
dir="Data/result/setintersection/sgx/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

adir="Data/input/setintersection/native/a/"
for file in Data/input/setintersection/native/b/*
do    
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr 'rand' "\n"))
  c=($(echo ${a[1]} | tr '.' "\n"))
  # echo ${c[0]}
  aname="f_rand"${c[0]}".txt"
  apath=$adir$aname
  echo $apath
  echo $file 
  ./app "$fn" "$file" "$apth" 	 
done
