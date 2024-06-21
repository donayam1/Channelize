#! /bin/bash
dir="../../Data/result/bubblesort/native/total/do/"
for file in ../../Data/input/bubblesort/nosec/*
do  
  echo $file
  bn="$(basename $file)"     
  fn=$dir$bn
  perf stat -o "$fn"  -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores ./main "$file"
  # --interval-print 100
  # perf stat -o "$fn" --interval-print 100 -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults ./main "$file" "${a[1]}" "${a[2]}"
done

for i in {0..500}
do 
  echo $i
  file="../../Data/input/bubblesort/sec/f_rand0.txt"
  
    echo $file
    bn="$(basename $file)"     
    fn=$dir$i$bn
    perf stat -o "$fn"  -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores ./main "$file" 
  
done 