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
	pid_t new_pid;
	int count=0;
	printf("hello linux,count=%X\n",&count);
	
	new_pid=fork();//创建一个子进程
	
	printf("现在fork返回的数值是:%d\n",new_pid);//调用父进程的时候new_pid=子进程PID 调用子进程的时候new_pid=0  失败new_pid=-1


	if(new_pid>0)
	{//	sleep(5);
		printf("new_pid=%d\n",new_pid);
		printf("pid=%d\n",getpid());
		printf("ppid=%d\n",getppid());
		printf("uid=%d\n",getuid());
		printf("euid=%d\n",geteuid());
		printf("gid=%d\n",getgid());
		printf("egid=%d\n",getegid());
		count++;
		printf("count=%d,count address=%X",count,&count);
	}
	else if(!new_pid)//pid==0
	{
		printf("new_pid=%d\n",new_pid);
		printf("pid=%d\n",getpid());
		printf("ppid=%d\n",getppid());
		printf("uid=%d\n",getuid());
		printf("euid=%d\n",geteuid());
		printf("gid=%d\n",getgid());
		printf("egid=%d\n",getegid());
		printf("count=%d,count address=%X",count,&count);
	}
	else
	{
		printf("fork failed\n");
	}
	
	count++;
	printf("new_pid=%d   pid=%d   count=%d\n",new_pid,getpid(),count);

	return 0;
}
