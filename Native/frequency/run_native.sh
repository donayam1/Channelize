#! /bin/bash
dir="../../Data/result/frequency/native/total/normal/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/frequency/do/*
do  
  echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))
  ./main "$fn" "$file" "${a[1]}" "${a[2]}"
  # --interval-print 100
  # perf stat -o "$fn" --interval-print 100 -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults ./main "$file" "${a[1]}" "${a[2]}"
done