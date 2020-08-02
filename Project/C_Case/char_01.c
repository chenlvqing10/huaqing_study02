/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：char_01.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月03日
 *   描    述：
 *
 ================================================================*/


#include<stdio.h>
#include<string.h>

void mystrcmp(char *a,char *b)
{

	int ret=0;
	while((*a!='\0')||(*b!='\0'))
	{
		ret += (*a-*b);
		printf("a=%d   b=%d   ret=%d\n",*a,*b,ret);
		a++;
		b++;
	}

	if(ret>0)
	{
		printf("string a>string b");
	}
	else if(ret<0)
	{
		printf("string a<string b");
	}
	else
		printf("string a=string b");
}
int main()
{
	char a[100]={0};
	char b[100]={0};

	printf("Please input a string:");
	scanf("%s",a);
	printf("Please input b string:");
	scanf("%s",b);

	mystrcmp(a,b);

	return 0;
}
