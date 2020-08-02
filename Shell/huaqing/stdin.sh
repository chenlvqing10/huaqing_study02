#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：stdin.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月20日
#   描    述：
#
#================================================================
exec 0< testfile
count=1

while read line
do
	echo "Line  #$count::$line"
	count=$[ $count +1 ]
done


