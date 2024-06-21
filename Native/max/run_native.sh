#! /bin/bash
dir="../../Data/result/contains/native/total/do/"
for i in {1..500}
do 
  echo $i
  file="../../Data/input/contains/f_rand0.txt"
  
  echo $file
  index=$((i*60000-1))
  number=$index #"40000000"
  # echo $index 
  outname="t_rand"$index".txt" 
  # echo $outname
  # bn="$(basename $file)"     
  fn=$dir$outname
  # echo $fn 
  # x=$bn
  # a=($(echo $x | tr '_' "\n"))
  perf stat -o "$fn"  -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores ./main "$file" "$number" 

done 