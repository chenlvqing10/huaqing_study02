#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	/*求文件的长度*/
	FILE *fp;
	char *file_path="./file_size.txt";
	long length;

	if((fp=fopen(file_path,"rb"))==NULL)
	{
		perror("open file_size.txt");
		exit(0);
	}
	else
	{
		perror("open file_size.txt");
		fseek(fp,0L,SEEK_END);//定位到文件末尾
		length=ftell(fp);
		printf("the length of file is %ld bytes\n",length);
	}



	fclose(fp);

	return 0;
}
