#include<stdio.h>
#include<errno.h>
int main(int argc,char *argv[])
{
	FILE *fp = NULL;
	char *file_dir="./test.txt";//文件路径
	char *open_method="r+";//打开文件的方式

	if((fp=fopen(file_dir,open_method))==NULL)//打开文件失败
	{
		printf("Open test.txt error!!\n");
		perror("fopen");
		printf("the error no:%d\n",errno);
	}
	else
	{
		printf("Open test.txt Success!!\n");
		perror("fopen");
	}




	errno=0;//将errno重新初始化为0
	char *file_dir1="./test.c";//改变文件的路径
	if((fp=fopen(file_dir1,open_method))==NULL)
	{
		printf("Open test.c error!!\n");
		perror("fopen");
		printf("the error no:%d\n",errno);
	}
	else
	{
		printf("Open test.c Success!! errno:%d\n",errno);
		perror("fopen");
	}

	int ret=fclose(fp);
	if(ret==0)
		perror("fclose");
	else
		perror("fclose");

	//按格式对文件进行I/O操作
	char s[80],c[80];
	int a,b;
	FILE *fp1=NULL;
	if((fp1=fopen("./mytest.txt","w"))==NULL)//以只写的方式打开文件   如果没有该文件创建该文件
	{
		puts("Can't open the file");
		return -1;
	}
	printf("Please input data to the file:\n");
	fscanf(stdin,"%s %d",s,&a);//从键盘输入
	fprintf(fp1,"%s %d",s,a);//写入文件

	fclose(fp1);//关闭文件

	if((fp1=fopen("./mytest.txt","r"))==NULL)//以只读的方式打开文件
	{
		puts("can't open the file");
		return -1;
	}
	fscanf(fp1,"%s %d",c,&b);//从文件读出数据  将其放入c,b
	fprintf(stdout,"%s %d",c,b);//将从文件读出的数据输出到屏幕
	fclose(fp1);




	return 0;
}
