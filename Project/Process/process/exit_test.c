#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>

int main(int argc, const char *argv[])
{
	printf("Using exit\n");
	printf("this is content in buff.......");

	_exit(0);

	//exit(0);

	return 0;
}
