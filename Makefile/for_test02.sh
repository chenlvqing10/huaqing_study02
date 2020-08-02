#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：for_test02.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月17日
#   描    述：
#
#================================================================
input="users.csv"
while IFS=','  read -r userid name
do
	echo "Adding $userid "
	useradd -c "$name" -m $userid
done < "$input"
