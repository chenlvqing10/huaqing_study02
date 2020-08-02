/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：array_01.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月03日
 *   描    述：
 *
 ================================================================*/


#include<stdio.h>
int main()
{
	int a[10][10]={0};

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if((j==0)||(i==j))
				a[i][j]=1;
			else
			{
				a[i][j] = a[i-1][j-1] + a[i-1][j];
			}
		}
	}

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<=i;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}

	return 0;
}
