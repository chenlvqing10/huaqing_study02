#include <stdio.h>


int main(int argc, const char *argv[])
{
	FILE *fp = NULL;

	// test.txt 的绝对路径  
	char *str = "/home/sky/DC20021/test.txt";
	char *m = "r+";

//	fp = fopen(str, m);
	fp = fopen("/home/sky/DC20021/test.c", "r+");
	fp = fopen(str, "r+");
	if(fp == NULL) {
		printf("fopen func error\n");
		return 0;
	} else {
		printf("fopen func success\n");
	}

	


	return 0;
}
