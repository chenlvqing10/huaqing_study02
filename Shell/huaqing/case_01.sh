#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：case_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================
echo "Input a char:"
read -n 1 char
printf "\n"
case $char in
	[a-zA-Z])
		echo "Letter";;
	[0-9])
		echo "Digit";;
	[,.?!])
		echo "Punctuation";;
	*)
		echo "Error"
esac
