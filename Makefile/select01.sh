#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：select01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月17日
#   描    述：
#
#================================================================
echo "What i your favourite OS?"
select name in "Linux" "Windows" "MAC OS" "Unix" "Android"
do
	echo $name
done
echo "You have selected $name"
