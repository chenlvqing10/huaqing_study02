#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <error.h>
#include <signal.h>
#include <bits/sigaction.h>
#include <sys/siginfo.h>
//进程间通信  系统信号应用

void new_op(int,siginfo_t*,void*);
void new_op(int signum,siginfo_t *info,void *myact)
{
	printf("receive signal %d", signum);
	sleep(5);
}

int main(int argc,char**argv)
{
	struct sigaction act;//sigaction结构体  指定了对特定信号的处理
	int sig;
	sig=atoi(argv[1]);
	sigemptyset(&act.sa_mask);//初始化由set指定的信号集，信号集里面的所有信号被清空；
	act.sa_flags=SA_SIGINFO;//Invoke signal-catching function with three arguments instead of one.
	act.sa_handler=new_op;//函数指针指定的信号处理函数

	if(sigaction(sig,&act,NULL) < 0)
		printf("install sigal error\n");

	while(1)
	{
		sleep(2);
		printf("wait for the signal\n");
	}
	return 0;
}


