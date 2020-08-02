#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_test03.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================
#item_name=~/chenlq/Shell/huaqing
item_name=~/chenlq/Shell/huaqing/a.txt


if [ -e $item_name ]  #check does  exit a dir or file
then
	echo "the $item_name does exit"
	echo "is it a file?"
	if [ -f $item_name ]    #check is a file
	then
		echo "Yes $item_name is a file."
	else
		echo "No,$item_name is no a file"
	fi
else
	echo "the $item_name does not exit"
	echo "Nothing is Update"
fi
