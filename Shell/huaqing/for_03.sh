#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：for_03.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月17日
#   描    述：
#
#================================================================
IFS.OLD=$IFS
IFS=$'\n'
for entry in $(cat /etc/passwd)
do
	echo "Values in $entry -"
	IFS=:
	for value in $entry
	do
		echo "   $value"
	done
done
