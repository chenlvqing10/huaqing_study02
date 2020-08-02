#include <stdio.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int ret = 0;

	fp = fopen("/home/sky/DC20021/test.c", "r+");
	if(fp == NULL) {
		printf("fopen func error %d \n", errno);
		perror("fopen");
		return 0;
	} else {
		printf("fopen func error %d \n", errno);
		perror("fopen");
		printf("fopen func success\n");
	}

//	printf("hello word %d ", 12);
	int num = fprintf(fp, "hello world %d ", 12);
	printf("num %d \n", num);


	ret = fclose(fp);
	if(ret == 0) {
		perror("fclose");
	} else {
		perror("fclose");
	}


	return 0;
}
