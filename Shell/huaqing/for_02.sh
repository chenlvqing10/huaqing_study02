#!/bin/sh
file_path=~/chenlq/Shell/huaqing/*

for file in $file_path
do
	if [ -d "$file" ]
	then
		echo "$file is a directory"
	elif [ -f "$file" ]
	then
		echo "$file is a file"
	else
		echo "$file does not existed"
	fi
done

