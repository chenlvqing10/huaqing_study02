/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：print_ascii.c
*   创 建 者：Chenlvqing
*   创建日期：2020年02月25日
*   描    述：
*
================================================================*/
#include<stdio.h>

int main()
{

	for(int i=0;i<=127;i++)
	{
		printf("16进制%x\t10进制%o\t10进制%d\tASCII码:%c\n",i,i,i,i);

	}

return 0;
}
