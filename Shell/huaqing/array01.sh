#!/bin/sh

#================================================================
#   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
#   文件类型：SHELL脚本
#   文件名称：array01.sh
#   创 建 者：Chenlvqing
#   创建日期：2020年03月13日
#   描    述：
#
#================================================================
declare -A color
color["red"]="#ff0000"
color["green"]="#00ff00"
color["blue"]="#0000ff"
color["white"]="#ffffff"
color["black"]="#000000"
#获取所有元素值
for value in ${color[*]}
do
    echo $value
done
echo "*************************************************************"
#获取所有元素下标（键）
for key in ${!color[*]}
do
    echo $key
done
echo "***********************"
#列出所有键值对
for key in ${!color[@]}
do
    echo "${key} -> ${color[$key]}"
done
