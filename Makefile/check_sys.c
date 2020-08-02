/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：check_sys.c
*   创 建 者：Chenlvqing
*   创建日期：2020年03月19日
*   描    述：
*
================================================================*/
#include<stdio.h>

typedef union litter{
	int a;
	char b;
}litter_t;

int check_sys()
{
	litter_t islitter;
	islitter.a=1;//0X00000001 if b=1 小端  else 大端
	return (islitter.b);
}
int main(int argc,const char *argv[])
{
	int ret=check_sys();
	if(ret==1)
		printf("This System is Litter Endian");
	else
		printf("This System is Big Endian");

return 0;
}
