/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：2020_2_28_01.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年02月28日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>

int main()
{

	int stu_score;
	printf("Please input a student's score:");
	scanf("%d",&stu_score);
	switch(stu_score/10)
	{
		case(9):
			printf("the score is A\n");
			break;
		case(8):
			printf("the score is B\n");
			break;
		case(7):
			printf("the score is C\n");
			break;
		case(6):
			printf("the score is D\n");
			break;
		Default:
			printf("the score is E\n");
	}

	return 0;
}
