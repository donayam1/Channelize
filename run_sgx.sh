dir="Data/result/distinctness_leaky/sgx/total/normal/"
mkdir -p "$dir" && echo "Directory created: $dir" 

for file in Data/input/distinctness/do/*
do
  bn="$(basename $file)"   
  fn=$dir$bn
  echo $fn
  ./app "$fn" "$file"
  # --interval-print 1000
done
