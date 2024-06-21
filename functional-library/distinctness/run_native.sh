dir="../../Data/result/distinctness/se/total/do/"
mkdir -p "$dir" && echo "Directory created: $dir"

for file in ../../Data/input/distinctness/do_se/*
do
  bn="$(basename $file)"   
  fn=$dir$bn
  echo $fn
  ./main "$fn" "$file"
done