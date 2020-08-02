#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_[[]].sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#===============================================================0=
read -p "Enter a telephone>>" tel
if [[ $tel =~ ^1[0-9]{10}$ ]]
then
	echo "This is a telephone number"
else
	echo "This is not a telephone number"
fi
