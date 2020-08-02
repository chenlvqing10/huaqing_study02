#!/bin/bash
#copy the shell script to Shared Document
source_dir=/home/chenlvqing/myprogram/Shell
Shared_dir=/mnt/hgfs/Share/shell

for shfile in $source_dir/*.*
do
  #echo $shfile
  #echo "${shfile#*.}"
  case "${shfile#*.}" in
  sh)
   #echo "the file is sh program";;
   chmod 777 $shfile
   cp -i $shfile $Shared_dir/;;
  *)
    echo "The file is not shell program";;
  esac
done
