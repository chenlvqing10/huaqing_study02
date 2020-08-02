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
	/*COPY the fin FILE into fout FILE */
	int fin,fout;
	const char *fin_path="./fin.txt";//read noly method
	const char *fout_path="./fout.txt";//write noly method
	int  size_file=0;

	//open the fin.txt
	if((fin=open(fin_path,O_RDONLY,S_IRWXU | S_IRWXG | S_IRWXO))<0)
	{   
		perror("open fin.txt");
		exit(1);
	}   
	else
	{
		perror("open fin.txt");
		size_file=lseek(fin,0,SEEK_END);
		printf("the size of fin.txt is %d\n",size_file);
	}
	lseek(fin,0,SEEK_SET);//重新定位到文件开头

	//read the fin.txt
	char buf_read[300];
	if((read(fin,buf_read,size_file))<0)
	{   
		perror("read fin.txt");
		exit(1);
	}   
	else
	{   
		perror("read fin.txt");
		fputs(buf_read,stdout); 
	}   

	//open the fout.txt
	if((fout=open(fout_path,O_WRONLY | O_TRUNC,S_IRWXU | S_IRWXG | S_IRWXO))<0)
	{   
		perror("open fout.txt");
		exit(1);
	}   
	else
		perror("open fout.txt");

	//write the fout.txt
	if((write(fout,buf_read,size_file))<0)
	{
		perror("write fout.txt");
		exit(1);
	}
	else
		perror("write fout.txt");

	close(fin);
	close(fout);


	return 0;
}
