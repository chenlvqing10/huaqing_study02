#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：bc_01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月16日
#   描    述：
#
#================================================================

var1=10.46
var2=43.67
var3=33.2
var4=71

var5 = $( bc << FLAGEOF
	scale = 4
	a1 =  (( $var1 * $var2 ))
	b1 = (( $var3 * $var4 ))
	a1 + b1
	FLAGEOF
	)

echo "the fianl answer is :" $var5

