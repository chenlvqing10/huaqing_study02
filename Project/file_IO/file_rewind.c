#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	/*COPY the fin FILE into fout FILE */
	FILE *fin,*fout;
	char ch;
	char const *fin_path="./fin.txt";//read noly method
	char const *fout_path="./fout.txt";//write noly method
	
	//open the fin file with r and open the fout file with w
	if(((fin=fopen(fin_path,"r"))==NULL)||((fout=fopen(fout_path,"w"))==NULL))
	{
		perror("fopen");
		exit(0);
	}
	else
		perror("fopen");


	//output the fin to stdout
	while(!feof(fin))
			putchar(getc(fin));
	
	//显示之后文件指针指向文件末尾
	if(feof(fin))
		printf("the file ptr point to file end");
	
	//将文件指针重新指向文件开头
	rewind(fin);
	//copy fin to fout
	while(!feof(fin))
		putc(getc(fin),fout);
		
	fclose(fin);
	fclose(fout);

	return 0;
}
