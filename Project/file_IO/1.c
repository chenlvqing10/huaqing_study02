#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, const char *argv[])
{

	//从键盘读入字符并以#键结束并将其写入文件fp中同时输出到终端
	FILE *fp=NULL;
	char ch,*filepath="./file.txt";

	if((fp=fopen(filepath,"w"))==NULL)//以只写方式
	{
		perror("fopen");
		exit(0);
	}
	else
		perror("fopen");
	
	printf("Please input a string and end with '#'\n");
	ch=getchar();//从键盘读入一个字符
	while(ch!='#')
	{
		fputc(ch,fp);//将字符写入fp
		putchar(ch);//将字符输出到屏幕或者终端
		ch=getchar();//读入下一个字符
	}
	fclose(fp);

	//从文件fp中读入字符
	FILE *fp1=NULL;
	int count_line=0;
	char const *filepath1="./file1.txt";
	if((fp1=fopen(filepath1,"r"))==NULL)//以只读方式
	{
		perror("fopen file 1");
		exit(0);
	}
	else
		perror("fopen file 1");
	while((ch=fgetc(fp1))!=EOF)//如果没有读到文件的末尾
	{
		putchar(ch);
		if(ch=='\n')
			count_line++;
	}
	printf("count=%d",count_line);
	fclose(fp1);


	return 0;
}
