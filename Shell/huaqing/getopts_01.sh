#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：getopts_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月19日
#   描    述：
#
#================================================================
echo
while getopts :ab:c opt
do
	case "$opt" in
		a)
			echo "Found the -a option";;
		b)
			echo "Found the -b option,with calue $OPTARG";;
		c)
			echo "Found the -c option";;
		*)
			echo "Unkown option::$opt";;
	esac
done
