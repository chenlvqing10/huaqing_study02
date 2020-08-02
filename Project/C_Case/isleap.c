/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：1.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年02月28日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>
int  main()
{
	int year;
	printf("Please input a year:");
	scanf("%d",&year);
	if(((year%4==0)&&(year%100!=0))||((year%400==0)))
	{
		printf("今年是闰年\n");
	}
	else
	{
		printf("今年不是闰年");
	}

	return 0;
}
