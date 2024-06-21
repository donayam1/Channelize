#!/bin/bash
dir="../../Data/result/maxrun/se/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/maxrun/do_se/*
do

  bn="$(basename $file)"     
  fn=$dir$bn
  x=$bn
  a=($(echo $x | tr '_' "\n"))

  # bn="$(basename $file)"   
  # fn=$dir$bn
  echo $fn
  ./main "$fn" "$file" "${a[1]}"
done

# for i in {1..176}
# do 
#   echo $i
#   file="../../Data/input/maxrun/normal/false/f_rand0.txt"
#   echo $file  
#   outname="f_rand"$i".txt"  
#   fn=$dir$outname
#   perf stat -o "$fn"  -e context-switches,cpu-migrations,cache-misses,cache-references,cpu-cycles,instructions,branch-misses,branches,page-faults,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores ./main "$file" "$number" 

# done 