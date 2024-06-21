#! /bin/bash
dir="../../Data/result/setintersection9/native/total/normal/"
adir="../../Data/input/si2/a/"
for file in ../../Data/input/si2/b/*
do  
  echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr 'rand' "\n"))
  c=($(echo ${a[1]} | tr '.' "\n"))
  # echo ${c[0]}
  aname="f_rand"${c[0]}".txt"
  apath=$adir$aname
  # echo $apath
  perf stat -o "$fn"  -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores ./main "$file" "$apath"
  # --interval-print 100
  # perf stat -o "$fn" --interval-print 100 -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults ./main "$file" "${a[1]}" "${a[2]}"
done