#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：for_04.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月17日
#   描    述：
#
#================================================================

for(( a=1;a<10;a++ ))
do
	echo "The number is $a"
done > test23.txt
