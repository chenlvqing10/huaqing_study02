#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, const char *argv[])
{
/*
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

*/
  /*
	//以人r+方式打开  打开可读写的文件 该文件必须存在
	FILE *fp2=NULL;
	char const *filepath2="./file2.txt";
	if((fp2=fopen(filepath2,"r+"))==NULL)//以读写方式打开
	{
		perror("fopen file 2");
		exit(0);
	}
	else
		perror("fopen file 2");
   
	char ch;
	//读取文件内容时显示乱码  读取文件内容后文件指针在文件末尾
	while((ch=fgetc(fp2)!=EOF))//read data from file
	{
		printf("ch=%c\n",ch);
		putchar(ch);
	}
   
	perror("W+ fgetc");	
   //写入内容到文件
   printf("Please input data and end with '#'\n");
   ch=getchar();
   while(ch!='#')
   {
	fputc(ch,fp2);//将ch写入fp2
	putchar(ch);//输出到终端
	ch=getchar();//读取下一个字符
   }

    fclose(fp2);

*/
	/*
    //以人w+方式打开  打开可读写的文件 该文件必须存在
	FILE *fp3=NULL;
	char const *filepath3="./file3.txt";
	if((fp3=fopen(filepath3,"w+"))==NULL)//以读写方式打开
	{
		perror("fopen file 3");
		exit(0);
	}
	else
		perror("fopen file 3");
   
	char ch;
	//无法读取文件内容？？？ 文件指针指向文件开头 会覆盖原文件
	while((ch=fgetc(fp3)!=EOF))//read data from file
	{
		//printf("ch=%c\n",ch);
		putchar(ch);
	}
   
	if((ch=fgetc(fp3)==EOF))//read data from file
	{
		printf("can not read from file with w+???\n");
		perror("w+ fgetc");
	}
	
   //写入内容到文件
   printf("Please input data and end with '#'\n");
   ch=getchar();
   while(ch!='#')
   {
	fputc(ch,fp3);//将ch写入fp2
	putchar(ch);//输出到终端
	ch=getchar();//读取下一个字符
   }

    fclose(fp3);
	*/
	/*
    //以人a方式打开  追加数据到文件的末尾
	FILE *fp4=NULL;
	char const *filepath4="./file4.txt";
	if((fp4=fopen(filepath4,"a"))==NULL)//以追加的方式打开
	{
		perror("fopen file 4");
		exit(0);
	}
	else
		perror("fopen file 4");
   
	char ch;

   //写入内容到文件
   printf("Please input data and end with '#'\n");
   ch=getchar();
   while(ch!='#')
   {
	fputc(ch,fp4);//将ch写入fp2
	putchar(ch);//输出到终端
	ch=getchar();//读取下一个字符
   }

    fclose(fp4);
	*/
    //以人a+方式打开  追加数据到文件的末尾
	FILE *fp5=NULL;
	char const *filepath5="./file5.txt";
	if((fp5=fopen(filepath5,"a+"))==NULL)//以追加的方式打开
	{
		perror("fopen file 5");
		exit(0);
	}
	else
		perror("fopen file 5");
   
	char ch;
	//无法读取文件内容？？ 乱码
	if((ch=fgetc(fp5)==EOF))//read data from file
	{
		printf("can not read from file with a+???\n");
		perror("a+ fgetc");
	}
	while((ch=fgetc(fp5)!=EOF))//read data from file
	{
		//printf("ch=%c\n",ch);
		putchar(ch);
	}
   
   //写入内容到文件
   printf("Please input data and end with '#'\n");
   ch=getchar();
   while(ch!='#')
   {
	fputc(ch,fp5);//将ch写入fp5
	putchar(ch);//输出到终端
	ch=getchar();//读取下一个字符
   }

    fclose(fp5);
	return 0;
}
