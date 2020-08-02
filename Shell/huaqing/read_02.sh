#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：read_02.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月19日
#   描    述：
#
count=1
cat test23.txt | while read line
do
	echo "Line $count::$line"
	count=$[ $count + 1]
done
echo "Finished processing the file"

