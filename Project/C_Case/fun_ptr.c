/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：fun_ptr.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月06日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>

int sum(int a,int b)
{
	return a+b;
}

int sub(int a,int b)
{
	return a-b;
}

void fun_show(int (*fun_ptr)(int,int))
{
	printf("show=%d\n",fun_ptr(45,10));
}

int main()
{
	//	int (*fun_ptr)(int,int)=sum;
	//	printf("sum=%d",fun_ptr(5,15));
	//printf("sum=%d",(*fun_ptr)(45,45));
	fun_show(sum);
	fun_show(sub);

	return 0;
}
