/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：ptr_array_02.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月05日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[4][3]={1,2,3,4,5,6,7,8,9,10,11,12};
	int (*p)[3];
	p=a;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",a[i][j]);
		}
	}
	printf("\n");
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",*(a[i]+j));
		}
	}
	printf("\n");
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",*(*(a+i)+j));
		}
	}
	printf("\n");
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",p[i][j]);
		}
	}
	printf("\n");
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",*(p[i]+j));
		}
	}
	printf("\n");
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",*(*(p+i)+j));
		}
	}
	printf("\n");
	return 0;
}
