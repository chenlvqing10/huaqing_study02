#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：getopt_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月18日
#   描    述：
#
#================================================================
set -- $( getopt -q ab:cd "$@" )
echo
while [ -n "$1" ]
do
	case "$1" in
		-a)
			echo "Found the -a option";;
		-b)
			param="$2"
			echo "Found teh -b option,with parameter value $param"
			shift;;
		-c)
			echo "Found the -c option";;
		--)
			shift
			break;;
		*)
			echo "$1 is not an option"
	esac
	shift
done

echo
count=1
for param in "$@"
do
	echo "Parameter #$count : $param"
	(( count += 1))
done



