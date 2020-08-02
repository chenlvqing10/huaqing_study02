/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：n_fun.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月06日
 *   描    述：
 *
 ================================================================*/


#include<stdio.h>

//函数递归
int fact(int n)
{
	if(n==1)
		return 1;
	else
		return n*fact(n-1);
}

int main()
{
	int n;
	printf("Please input a bumber:");
	scanf("%d",&n);
	printf("n!+(n+1)!=%d",fact(n)+fact(n+1));
	return 0;
}
