#!/bin/sh
#input a score then output A-D
read -p "Enter the Student's Score >>" score

if [ "$score" -ge 90 ]   && [ "$score" -le 100 ]
then
	echo "A"
elif [ "$score" -ge 70 ] &&  [ "$score" -lt 90 ]
then
	echo "B"
elif [ "$score" -ge 60 ] &&  [ "$score" -lt 70 ]
then
	echo "C"
elif [ "$score" -ge 0 ] &&  [ "$score" -lt 600 ] 
then
	echo "D"
else
	echo "input error"
fi

