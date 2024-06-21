dir="../../Data/result/validParenthesis/native/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/validParenthesis/do/*
do
  bn="$(basename $file)"   
  fn=$dir$bn
  echo $fn
  ./main "$fn" "$file"
done