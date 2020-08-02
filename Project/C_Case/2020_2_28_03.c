/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：2020_2_28_03.c
*   创 建 者：Chenlvqing
*   创建日期：2020年02月28日
*   描    述：
*
================================================================*/
#include<stdio.h>

int main()
{

for(int i=0;i<5;i++)
{
	for(int j=5;j>i;j--)
	{
		printf("*");
	}
	printf("\n");
}
	
return 0;
}
