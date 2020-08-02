#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_04.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月23日
#   描    述：
#
{
	echo "11111";
	echo "2222";
	echo "30"
}>log.txt

{
	read name;
	read url;
	read age
}<log.txt
echo "the name is $name  the url is $url the age is $age"
