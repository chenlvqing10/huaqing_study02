#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：for_test01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月17日
#   描    述：
#
#================================================================
IFS=:
for folder in $PATH
do
	echo "$folder"
	for file in $folder/*
	do
		if [ -x $file ]
		then
			echo "   $file"
		fi
	done
done
