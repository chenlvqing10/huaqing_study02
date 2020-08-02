/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：2020_2_28_02.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年02月28日
 *   描    述：
 *
 ================================================================*/


#include<stdio.h>
int main()
{
	int i=1,sum=0;
	while(i<=100)
	{
		if(i%2==0)
			sum += i;
		i++;
	}
	printf("the sum is:%d",sum);
	return 0;
}
