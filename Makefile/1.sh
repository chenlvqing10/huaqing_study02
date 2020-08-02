#!/bin/sh
#input a score then output A-D
read -p "Enter the Student's Score >>" score

if [ `echo $score | gawk -v bi=90 '{print ($1>bi?"1":"0") }'` -eq "1" ]
then
	echo "A"
else
	echo "input error"
fi

