/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <error.h>
//无名管道 pipe

int main() 
{
	int pipe_fd[2];//pipe_fd[0]--读端   pipe_fd[1]--写端
	pid_t pid;//进程ID
	char buf_r[100];//缓冲区数组
	char* p_wbuf;//写指针
	int r_num;//读的计数
	memset(buf_r,0,sizeof(buf_r));//初始化缓冲区
    

	//在创建子进程之前先创建管道 子进程会继承该管道
	if(pipe(pipe_fd)<0)//如果创建管道失败
	{
		printf("pipe create error\n");
		return -1;
	}
	printf("fd[0]=%d    fd[1]=%d\n",pipe_fd[0],pipe_fd[1]);//打印文件描述符

	if((pid=fork())==0)//创建子进程
	{
		printf("\n");
		close(pipe_fd[1]);//关闭写端
		sleep(2);//

		if((r_num=read(pipe_fd[0],buf_r,100))>0)//从管道write端读取数据
		{
			printf( "%d numbers read from the pipe is::\n%s\n",r_num,buf_r);
		}	

		close(pipe_fd[0]);//关闭read端

		exit(0);
  	}
	else if(pid>0)//继续执行父进程代码
	{
		close(pipe_fd[0]);//关闭read端
		p_wbuf="write the pipe\nwrite the pipe two";

		if(write(pipe_fd[1],p_wbuf,strlen(p_wbuf))!=-1)//向管道write端里面写入数据
			printf("parent write1 success!\n");

		close(pipe_fd[1]);//关闭写端

		sleep(3);//等待三秒
		waitpid(pid,NULL,0);//等待子进程结束
		printf("子进程结束\n");
		exit(0);
	}

	return 0;
}


