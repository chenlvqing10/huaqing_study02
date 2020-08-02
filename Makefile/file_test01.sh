#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_test01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================
jump_directory=~/chenlq/Shell/huaqing/filetest
if [ -d $jump_directory ]
then
	echo "The jump_directory exists"
	cd $jump_directory
	ls -al
else
	echo "The jump_directory does not exists"
	mkdir $jump_directory
	chmod u+x $jump_directory
	cd $jump_directory
	ls -al
fi
