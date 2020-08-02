#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<string.h>
/*计算文件的行数   计算文件中含有多少换行符*/
/*参数：*path:文件的路径 */
/*返回值：文件的函数*/
int get_file_number(const char *path)
{
	FILE *fp=NULL;
	int count=0;
	char ret;
	if((fp=fopen(path,"r"))==NULL)
	{
		perror("fopen");
		exit(0);
	}
	else
		perror("fopen");

	/*1.使用fgets()函数 统计行数*/
	char string[100];
	while(fgets(string,100,fp)!=NULL)//从文件中读取n个字符  按行读取
	{
		fputs(string,stdout);//将读取到的文件输出到屏幕或者终端
		if(string[strlen(string)-1]=='\n')//遇到换行符结束本行的读取 并加‘\0’
			count++;
	}



	/*2.使用fgetc()函数*/
	/*
	if((ret=fgetc(fp))==EOF)
		perror("fgetc no date");

	//for循环实现
	for(ret=fgetc(fp);ret!=EOF;ret=fgetc(fp))
	{
		if(ret=='\n')
			count++;
	}
	*/
	//while循环实现
	/*
	while((ret=fgetc(fp))!=EOF)//从文件一个一个字符读入数据
	{
		if(ret=='\n')
			count++;
	}
   */
	fclose(fp);

	return count;
}


int main(int argc, const char *argv[])
{
	const char *file_path="./file1.txt";//文件路径
	
	int num_line=get_file_number(file_path);

	printf("the file line number is:%d",num_line);
	
	return 0;
}
