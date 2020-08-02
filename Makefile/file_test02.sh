#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_test02.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================
location=~/chenlq/Shell/huaqing
file_name="a.txt"

if [ -e $location ]   #check the file
then
	echo "OK on the location"
	echo "Now Check the file"
	if [ -e $location/$file_name ]    #check the file
	then
		echo "OK on the filename"
		echo "Updating Current Date..."
		date > $location/$file_name     #update the date
	else
		echo "The file is not exist"
		echo "Nothing is to Update"
	fi
else
	echo "The location is not exist"
	echo "Nothing to update"
fi
