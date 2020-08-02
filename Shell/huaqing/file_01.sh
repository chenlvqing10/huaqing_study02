#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：file_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月23日
#   描    述：
#
exec 3> test181
exec 6> test182
exec 7< testfile
lsof -a -p $$ -d 0,1,2,3,6,7
