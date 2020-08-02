include <stdio.h>
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
	char *env[] = {"PATH=/usr/local/games","TEAM=console", "123456789","打印参数列表_参数m",NULL};
	char *argvs[] = {"打印参数列表_参数一","TEAM=console", "123456789","打印参数列表_参数二",NULL};
	if((new_pid=fork())==0)
	{
		//用exec函数产生新的进程
		//execl("./hello","打印参数列表_参数一","打印参数列表_参数二",NULL);
		execlp("hello","打印参数列表_参数一","打印参数列表_参数二",NULL);
		//execle("./hello","打印参数列表_参数一","打印参数列表_参数二",NULL,env);
		//execv("./hello",argvs);
		//execve("./hello",argvs,env);
		//execvp("hello",argvs);
		printf("调用子进程 pid=%d new_pid=%d\n",getpid(),new_pid);//子进程被exec函数替换，本语句不执行
	}
	else
	{
		printf("调用父进程 pid=%d new_pid=%d\n",getpid(),new_pid);
	}
	return 0;
}
