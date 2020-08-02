/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：cal.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月19日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>

typedef enum cal{
	add=0,
	sub,
	mul,
	div,
	mod,
	other
}calculator;

double val_fun(int a,int b,calculator op)
{
	switch(op)
	{
		case 0:
			return (a+b);
			break;
		case 1:
			return (a-b);
			break;
		case 2:
			return (a*b);
			break;
		case 3:
			return (a/b);
			break;
		case 4:
			return (a%b);
			break;
		default:
			printf("op is error\n");
			return -1;
	}
}

int main(int argc,const char *argv[])
{

	int a,b;
	printf("Please input two number:");
	scanf("%d %d",&a,&b);

	printf("a + b =%.2f\n",val_fun(a,b,add));
	printf("a - b =%.2f\n",val_fun(a,b,sub));
	printf("a * b =%.2f\n",val_fun(a,b,mul));
	printf("a / b =%.2f\n",val_fun(a,b,div));
	printf("a mod b =%.2f\n",val_fun(a,b,mod));
	printf("the error status:%.2f",val_fun(a,b,other));

	return 0;
}
