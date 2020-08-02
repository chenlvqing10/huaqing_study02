#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
int main(int argc, const char *argv[])
{
	/*Write the date message into the fdate.txt */
	FILE *fdate;
	time_t timep;
	struct tm *ptr_tm;//struct ptr
	char const *fdate_path="./fdate.txt";//read noly method
	char writebuf[3000];
	char ch;
	int line=1;

	if((fdate=fopen(fdate_path,"a+"))==NULL)
	{
		perror("fopen fdate.txt");
		exit(0);
	}
	else
		perror("fopen fdate.txt");

	//count the line numbee

	if((ch=fgetc(fdate))==EOF)
		printf("there is no scope int the txt file");

	//the next time line
	while((ch=fgetc(fdate))!=EOF)
	{
		if(ch=='\n')
			line++;
	}

	//get current system time each 1 second
	while(1)
	{
		time(&timep);
		ptr_tm=localtime(&timep);
		printf("line=%d\n",line);
		printf("year:%d\n",ptr_tm->tm_year+1900);
		sprintf(writebuf,"line:%d year:%d month:%d day:%d week:%d hour:%d minute:%d second:%d\n",
				line,ptr_tm->tm_year+1900,ptr_tm->tm_mon+1,ptr_tm->tm_mday,ptr_tm->tm_wday,ptr_tm->tm_hour,ptr_tm->tm_min,ptr_tm->tm_sec);

		line++;
		//fputs(writebuf,fdate);
		printf("sizeof(char)=%d strlen(sritebuf)=%d\n",sizeof(char),strlen(writebuf));
		fwrite(writebuf,sizeof(char),strlen(writebuf),fdate);
		//fwrite(writebuf,strlen(writebuf),1,fdate);
		fflush(fdate);
		sleep(1);
	}
//	fclose(fdate);

	return 0;
}
