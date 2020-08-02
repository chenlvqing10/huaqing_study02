#include <stdio.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	int ret = 0;

	fp = fopen("./test.c", "r+");
	if(fp == NULL) {
		printf("fopen func error %d \n", errno);
		perror("fopen");
		return 0;
	} else {
		printf("fopen func success %d \n", errno);
		perror("fopen");
		printf("fopen func success\n");
	}

	ret = fclose(fp);
	if(ret == 0) {
		perror("fclose");
	} else {
		perror("fclose");
	}


	return 0;
}
