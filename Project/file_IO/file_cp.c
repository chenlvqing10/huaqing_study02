#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, const char *argv[])
{
	/*COPY the fin FILE into fout FILE */
	FILE *fin,*fout;
	char ch;
	char const *fin_path="./fin.txt";//read noly method
	char const *fout_path="./fout.txt";//write noly method

	if(((fin=fopen(fin_path,"r"))==NULL)||((fout=fopen(fout_path,"w"))==NULL))
	{
		perror("fopen");
		exit(0);
	}
	else
		perror("fopen");


	while((ch=fgetc(fin))!=EOF)
	{
		putchar(ch);
		fputc(ch,fout);
	}


	fclose(fin);
	fclose(fout);

	return 0;
}
