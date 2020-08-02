#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：stderr01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月20日
#   描    述：
#

exec 2>testerror
echo "This output should go to the script"
echo "now redirecting all output to anither location"

exec 1>testout
echo "This output should go to the testout file"
echo "but this should go to the testerror file" >&2
