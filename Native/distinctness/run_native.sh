dir="../../Data/result/distinctness/native/total/normal/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/distinctness/do/*
do
  bn="$(basename $file)"   
  fn=$dir$bn
  echo $fn
  ./main "$fn" "$file"
done