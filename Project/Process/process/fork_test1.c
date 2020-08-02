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

#define N 3
int main(int argc, const char *argv[])
{
	pid_t new_pid;
	
    for(int i=0;i<N;i++)
	{
		new_pid=fork();//创建一个子进程
		if(new_pid==0)
			printf("i=%d  子进程调用  ppid=%d  pid=%d  new_pid=%d\n",i,getppid(),getpid(),new_pid);
		else
			printf("i=%d  父进程调用  ppid=%d  pid=%d  new_pid=%d\n",i,getppid(),getpid(),new_pid);

	}

	return 0;
}
