/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pc,pc2,pr;

	pc2=fork();//创建子进程PC2     有两个进程:   父进程pc2  子进程pc2

	if(pc2==0)

	{
		printf("调度顺序3: 调用pc2=%d子进程\n",getpid());
		printf("调度顺序3:pc2=%d   现在的进程pid=%d\n",pc2,getpid());
		//	printf("pc2子进程将要退出,所以pc2子进程的pc子进程,不会执行\n");
		//exit(0);
	}
	else//调度顺序1
	{
		printf("调用顺序1:先调用pc2父进程\n");
		//printf("经过第一次fork后,共有两个进程 父进程pc2=%d  子进程pc2=%d\n",getpid(),pc2);
		printf("调用顺序1:pc2=%d  现在的进程pid=%d\n",pc2,getpid());
		//sleep(10);
	}


	pc=fork();//创建子进程pc  有四个进程  父进程pc2   父进程pc2的子进程pc  子进程pc2 子进程pc2的子进程pc

	if(pc<0)
		printf("Error fork.\n");
	else if(pc==0)
	{ 
		if(pc2==0)//调用pc2子进程的pc子进程时会调用到这里的内容
		{
			printf("调度顺序4:由于父进程%d被阻塞,调用子进程pc2的子进程pc%d\n",getppid(),getpid());
			printf("调度顺序4:pc2=%d pc=%d   现在的进程pid=%d\n",pc2,pc,getpid());
			exit(0);//子进程退出

		}
		else if(pc2>0)//当父进程pc2被阻塞的时候,如果调用父进程的pc子进程,那么此处会被调用
		{
			printf("调度顺序2:由于父进程%d被阻塞,调用父进程的pc子进程%d\n",getppid(),getpid());
			printf("调度顺序2:pc2=%d pc=%d   现在的进程pid=%d\n",pc2,pc,getpid());
			exit(0);//子进程退出
		}
	}  
	else
	{
		if(pc2>0)
		{
			printf("调用顺序1:继续调用pc2父进程\n");
			printf("调用顺序1:pc2=%d pc=%d   现在的进程pid=%d\n",pc2,pc,getpid());
		}
		else if(pc2==0)
		{
			printf("调度顺序3:pc2=%d pc=%d   现在的进程pid=%d\n",pc2,pc,getpid());
		}
		//printf("经过第二次fork后,有四个进程  父进程pc2   父进程pc2的子进程pc  子进程pc2 子进程pc2的子进程pc\n");

		do
		{ 
			if(pc2==0)
			{
				printf("调度顺序3:pc2=%d pc=%d   现在的进程pid=%d\n",pc2,pc,getpid());
			}
			//pr=wait(NULL);//使父进程暂停执行 等待子进程结束 如果有多个子进程的情况下，子进程的调度顺序可变
			//pr=waitpid(pc,NULL,WNOHANG);//不阻塞父进程

			pr=waitpid(pc2,NULL,WNOHANG);//不等待pc2 
			pr=waitpid(pc,NULL,WUNTRACED);//阻塞父进程   由于pc会产生2个数值等待父进程pc2的子进程pc结束  或者等待子进程pc2的子进程  
			//pr=waitpid(pc2,NULL,WUNTRACED);//阻塞父进程   等待子进程pc2结束 

			printf("阻塞过后执行pc2=%d pc=%d   现在的进程pid=%d\n",pc2,pc,getpid());

			printf("pr=%d   pc=%d\n",pr,pc); //pr成功的话返回子进程ID

			if(pr==0)
			{ 
				printf("The child process has not exited\n");
				sleep(1);  
			}

		}while(pr==0);

		if(pr==pc)//调用父进程的时候pc=子进程pid   pr==子进程pid
			printf("Get child %d\n",pr);
		else
			printf("some error occured.\n");

		printf("+++++++\n");
	}

}


