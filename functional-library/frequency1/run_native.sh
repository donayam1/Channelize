#! /bin/bash
dir="../../Data/result/frequency1/se/total/do/"
for file in ../../Data/input/frequency/do_se/*
do  
  echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))
  perf stat -o "$fn"  -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores ./main "$file" "${a[1]}" "${a[2]}"
  # --interval-print 100
  # perf stat -o "$fn" --interval-print 100 -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults ./main "$file" "${a[1]}" "${a[2]}"
done