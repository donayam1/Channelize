#! /bin/bash
dir="../../Data/result/setintersection/native/total/do_snoopy/"
mkdir -p "$dir" && echo "Directory created: $dir"

adir="../../Data/input/setintersection/native/a/"
for file in ../../Data/input/setintersection/native/b/*
do  
  # echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr 'rand' "\n"))
  c=($(echo ${a[1]} | tr '.' "\n"))
  # echo ${c[0]}
  aname="f_rand"${c[0]}".txt"
  apath=$adir$aname
  echo $fn
  ./main_snoopy "$fn" "$file" "$apath"
  # --interval-print 100
  # perf stat -o "$fn" --interval-print 100 -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults ./main "$file" "${a[1]}" "${a[2]}"
done