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
//双工通信   双向管道----四个文件描述符

int main() 
{
	int pipe_fd[2];//pipe_fd[0]--读端   pipe_fd[1]--写端
	int pipe_fd1[2];//pipe_fd1[0]--write  pipe_fd1[1]---read

	pid_t pid;//进程ID
	char buf_r[100];//缓冲区数组
	char* p_wbuf;//写指针
	int r_num;//读的计数
	memset(buf_r,0,sizeof(buf_r));//初始化缓冲区
    

	//在创建子进程之前先创建管道 子进程会继承该管道
	if(pipe(pipe_fd)<0)//如果创建管道失败
	{
		printf("pipe one create error\n");
		return -1;
	}

	if(pipe(pipe_fd1)<0)//如果创建管道失败
	{
		printf("pipe two create error\n");
		return -1;
	}

	printf("fd[0]=%d    fd[1]=%d   fd1[0]=%d   fd1[1]=%d\n",pipe_fd[0],pipe_fd[1],pipe_fd1[0],pipe_fd1[1]);//打印文件描述符

	if((pid=fork())==0)//创建子进程
	{
		printf("-------------------------------\n");

		//读取管道一数据  写入管道二数据
		close(pipe_fd[1]);//关闭写端
		if((r_num=read(pipe_fd[0],buf_r,100))>0)//从管道write端读取数据
		{
			printf( "管道一:%d numbers read from the pipe is::\n%s\n",r_num,buf_r);
		}	
		close(pipe_fd[0]);//关闭read端
		//sleep(10);

		//管道二写入数据
		close(pipe_fd1[0]);//关闭管道二的read端
		p_wbuf="管道二:write the pipe two\nhello nihao";//定义写的内容
		if(write(pipe_fd1[1],p_wbuf,strlen(p_wbuf))!=-1)//向管道二write端里面写入数据
			printf("写入管道二:parent write1 success!\n");
		close(pipe_fd1[1]);//关闭管道二写端
		//sleep(20);//等待三秒
		printf("子进程结束\n");
		exit(0);
  	}
	else if(pid>0)//继续执行父进程代码
	{
		printf("+++++++++++++++\n");
		//将内容写入管道一   从管道二中读取数据
		close(pipe_fd[0]);//关闭管道一的read端
		p_wbuf="管道一:write the pipe one\nhello";//定义写的内容
		if(write(pipe_fd[1],p_wbuf,strlen(p_wbuf))!=-1)//向管道一write端里面写入数据
			printf("写入管道一:parent write1 success!\n");
		close(pipe_fd[1]);//关闭管道一写端
		sleep(10);

		close(pipe_fd1[1]);//关闭管道二write端
		if((r_num=read(pipe_fd1[0],buf_r,100))>0)//从管道二中读取数据
		{
			printf("管道二:%d numbers read from the pipe is::\n%s\n",r_num,buf_r);
		}
		close(pipe_fd1[0]);//关闭管道二写端
		//sleep(3);//等待三秒
		
		waitpid(pid,NULL,0);//等待子进程结束
		printf("父进程结束\n");
		exit(0);
	}

	return 0;
}


