#!/bin/bash
source_dir=/home/chenlvqing/myprogram
cp_dir=/home/c_src
Shared_dir=/mnt/hgfs/Share
if [ ! -d $cp_dir ]
then
    mkdir $cp_dir
    chmod u+x $cp_dir
fi

for cfile in $source_dir/*.*
do
  case "${cfile#*.}" in
  c)
   #echo "the file is c program";;
   cp -i $cfile $cp_dir/;;
  *)
    echo "The file is not c program";;
  esac
done

today=` date +%Y_%m_%d `
cd $cp_dir
tar zcvf src_$today.tgz $cp_dir
if [ -f $cp_dir/src_$today.tgz ]
then
    cp  -i $cp_dir/src_$today.tgz $Shared_dir/
else
    echo "there is no tgz file"
fi
