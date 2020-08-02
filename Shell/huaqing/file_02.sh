#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_02.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月23日
#   描    述：
#
tempfile=$(mktemp test19.XXXXXX)    #创建一个临时文件

exec 3>$tempfile   #将临时文件作为文件描述符3重定向

echo "This script writes to temp file $tempfile"    #STDOUT输出

echo "This is the first line"   >&3    #向临时文件中写数据
echo "This is the second line " >&3
echo "This is the third line"   >&3

exec 3>&-   #关闭文件描述符

echo “Done creating temp file. the contents are:”

cat $tempfile
rm -f  $tempfile 2> /dev/null
