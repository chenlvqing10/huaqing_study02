/*================================================================
/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：array.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月02日
 *   描    述：
 *
 ================================================================*/


#include<stdio.h>
int main()
{
	int a[10];
	printf("a=%p &a=%p  &a[0]=%p\n",a,&a,&a[0]);
	printf("a+1=%p &a+1=%p  &a[0]+1=%p\n",a+1,&a+1,&a[0]+1);
	return 0;
}
