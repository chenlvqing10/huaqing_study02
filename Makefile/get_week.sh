#!/bin/sh
read -p "Enter a num>>" num
case "$num" in
	1)
		echo "MonDay";;
	2)
		echo "TuesDay";;
	3)
		echo "WednesDay";;
	4)
		echo "ThursDay";;
	5)
		echo "FriDay";;
	6)
		echo "SaturDay";;
	7)
		echo "SunDay";;
	*)
		echo "Other Number"
esac
