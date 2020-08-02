#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：read_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================
#read -p "Enter some information >" name url age
#echo "name:$name"
#echo "URL:$url"
#echo "AGE:$age"

#read -n 1 -p "Enter a char >" char
#printf "\n"
#echo $char
if
	read -t 20 -sp "Entter password in 20 seconds(once) >"  pass1 && printf "\n" &&
	read -t 20 -sp "Entter password in 20 seconds(again) >" pass2 && printf "\n" &&
[ $pass1 == $pass2 ]
then
	echo "Valid password"
else
	echo "Invalid password"
fi
