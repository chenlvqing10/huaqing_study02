#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	
	//open file with readonly
	int fd_r;//save the file descripter
	const char *pathname="./fin.txt";
	if((fd_r=open(pathname,O_RDONLY,S_IRWXU|S_IRWXG|S_IRWXO))<0)
	{
		perror("open file2.txt");
		exit(1);
	}
	else
		perror("open file2.txt");

   //read file
   char buf_read[300];
	if((read(fd_r,buf_read,150))<0)//将读到的字符保存到buf_read中 需要知道读到的文件的字符大小
	{
		perror("read file2.txt");
		exit(1);
	}
	else
	{
		perror("read file2.txt");
		fputs(buf_read,stdout);
	}
	//close file
	close(fd_r);

   
	//open file with writenonly  if the file does't exist create the file
	int fd_w;//save the file descripter
	const char *pathname1="./file1.txt";
	if((fd_w=open(pathname1,O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU | S_IRWXG | S_IRWXO))<0)
	{
		perror("open file1.txt");
		exit(1);
	}
	else
		perror("open file1.txt");

   //write file
   char buf_write[100]="123456\n456789\n789101\n";
	if((write(fd_w,buf_write,strlen(buf_write)))<0)//将读到的字符保存到buf_read中
	{
		perror("write file1.txt");
		exit(1);
	}
	else
	{
		perror("write file1.txt");
		fputs(buf_write,stdout);
	}
	//close file
	close(fd_w);


	//open file with readwrit  if the file does't exist create the file
	int fd_rw;//save the file descripter
	const char *pathname_rw="./file3.txt";
	if((fd_rw=open(pathname_rw,O_RDWR | O_CREAT | O_APPEND,S_IRWXU | S_IRWXG | S_IRWXO))<0)
	{
		perror("open file3.txt");
		exit(1);
	}
	else
		perror("open file3.txt");

	//read file
    char buf_read1[300];
	if((read(fd_rw,buf_read1,150))<0)//将读到的字符保存到buf_read中 需要知道读到的文件的字符大小
	{
		perror("read file3.txt");
		exit(1);
	}
	else
	{
		perror("read file3.txt");
		fputs(buf_read1,stdout);
	}
	
	
   //write file
   char buf_write1[100]="123456\n456789\n789101\n";
	if((write(fd_rw,buf_write1,strlen(buf_write)))<0)//将读到的字符保存到buf_read中
	{
		perror("write file3.txt");
		exit(1);
	}
	else
	{
		perror("write file3.txt");
		fputs(buf_write1,stdout);
	}
	
	//close file
	close(fd_rw);


	return 0;
}
