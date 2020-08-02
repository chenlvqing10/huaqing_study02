#!/bin/sh

#get List from Command
file="for.txt"
for state in $(cat $file)
do
	echo "Visit Beautiful $state"
done

