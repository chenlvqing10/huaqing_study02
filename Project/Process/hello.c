#include <stdio.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
	int a=1,b=8;
	printf("Hello World!!!\n");
	printf("a+b=%d\n",a+b);
	for(int i = 0; i < argc; i++) {
		printf("%s \n", argv[i]);
	}

	execl("/usr/bin/printenv","printenv",NULL);
	return 0;
}
