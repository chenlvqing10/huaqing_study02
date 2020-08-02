#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：signal_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月23日
#   描    述：
#
trap "echo 'Sorry!I have trapped Ctrl-C'" SIGINT

echo "This is a test script"

count=1
while [ $count -le 10 ]
do
	echo "Loop #$count"
	count=$[ $count + 1]
	echo $count
	sleep 1
done

echo "This is the end of the test script"

