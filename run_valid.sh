dir="Data/result/validParenthesis/sgx/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in Data/input/validParenthesis/do/*
do
  bn="$(basename $file)"   
  fn=$dir$bn
  echo $fn
  ./app "$fn" "$file"
done