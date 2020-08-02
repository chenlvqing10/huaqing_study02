#!/bin/sh
read -p "Enter m>>" m
read -p "Enter n>>" n
sum=0
while((m<=n))
do
	((sum += m))
	((m++))
done
echo "The sum is :$sum"
