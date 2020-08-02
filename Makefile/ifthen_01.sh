#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：ifthen_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================

read -p "Enter a student's score >" score
if(( $score >= 90 && $score <= 100 ))
then
	echo "A"
elif(( $score >=70 && $score <90))
then
	echo "B"
elif(( $score >=60 && $score <70))
then
	echo "C"

elif(( $score >=0 && $score <60))
then
	echo "D"
else
	echo “Eroor Input”
fi
