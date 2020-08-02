#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE* fp;
	char ch;
	char const *filename = "out.txt";
/*  打开一个文件或者创建一个文件
	   fp = fopen_s(&fp,"test.txt", "w");
	   if (fp == -1)
	   {
	   printf("Can not open the File\n");
	   exit(0);
	   }
*/
/*从存在的文本文件中读取数据*/
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("can not read a file\n");
		exit(0);
	}
    
	while((ch=fgetc(fp))!=EOF)//From fp read data
	{
		putchar(ch);//output the data tp screen
	}

/*
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Can not open the File\n");
		exit(0);
	}
	printf("Please input string:\n");
	ch = getchar();
	while (ch!='#')
	{
		fputc(ch, fp);
		putchar(ch);
		ch = getchar();
	}
*/
    fclose(fp);
	return 0;
}
