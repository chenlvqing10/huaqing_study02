#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/msg.h>
#include <wait.h>
#include <signal.h>
//消息队列缓冲区
struct msgbuf
{
	long mtype;
	char mtext[100];
};
//共享内存
struct node {
	pid_t f_pid;//本进程父进程ID
	pid_t c_pid;//本进程子进程IDi
	pid_t f1_pid;//对方程父进程ID
	pid_t c1_pid;//对方进程子进程ID
};

//消息类型
#define MSG_TYPE_A  1
#define MSG_TYPE_B  2
void my_func_handler(int sig)
{

}
int main(int argc, const char *argv[])
{
	signal(SIGALRM,my_func_handler);
	//1.key值
	key_t  key = 0;
	key = ftok("./app", 'm');
	if(key == -1) {
		perror("ftok");
		return -1;
	}
	//创建共享内存
	int shmid = 0;
	shmid = shmget(key, 100, IPC_CREAT|IPC_EXCL|0777);
	if(shmid == -1)//创建共享内存失败
	{
		// 如果共享内存已经存在
		if(errno == EEXIST)
		{   
			shmid = shmget(key, 0, 0777);//打开共享内存
			perror("打开共享内存成功");
		} 
		else
		{   
			perror("创建共享内存失败");
			return -1;
		}
	}
	else
	{
		perror("创建共享内存成功");
	}
	//printf("共享内存id号:%d\n",shmid);//打印共享内存id
	//3.映射共享内存对象到虚拟地址中    
	void *addr = NULL;
	addr = shmat(shmid, NULL, 0);
	if(addr ==  (void *)(-1))//映射失败
	{
		perror("共享内存映射失败");
		return -1;
	}
	else
	{
		perror("共享内存映射成功");
	}
	struct node *p = (struct node *)addr;//将结构体指针指向共享内存

	//2.创建/打开消息队列
	int msgid = msgget(key, IPC_CREAT|IPC_EXCL|0777);
	if(msgid == -1) 
	{
		if(errno == EEXIST) 
		{
			msgid = msgget(key, 0777);
			perror("打开消息队列成功");
		} 
		else 
		{
			perror("消息队列创建失败");
			return -1;
		}
	}
	else
	{
		perror("创建消息队列成功");
	}

	printf("消息队列id:%d\n",msgid);
	struct msgbuf msg;
	pid_t pid=fork();
	while(1)
	{
		//printf("pid=%d 运行的pid=%d\n",pid,getpid());
		if(pid<0)
		{
			perror("create child error");
			exit(-1);
		}
		else if(pid==0)//子进程  从A类性的消息队列中读取信息
		{
			//printf("执行子进程\n");
			p->f_pid=getppid();//将本进程的父进程ID放到共享内存中
			p->c_pid=getpid();//将本进程的子进程ID放到共享内存中
			pause();//等待对方进程发送唤醒信号
			//printf("唤醒了\n");
			
			msg.mtype =  MSG_TYPE_A;
			memset(msg.mtext, 0, sizeof(msg.mtext));
			printf("msgid=%d\n",msgid);
			int ret = msgrcv(msgid, (void *)&msg, 100, MSG_TYPE_A, 0);
			
			if(ret == -1)
			{
				perror("从TYPEA消息队列中读取内容失败");
			}
			else
			{
				//perror("从TYPEA消息队列中读取内容成功");
				printf("从TYPEA消息队列读到的内容:%s\n",msg.mtext);
			}

			//判断是否是退出
			if(strcmp(msg.mtext,"quit\n")==0)
			{
				//唤醒对方子进程进行消息队列的删除
				kill(p->c_pid,SIGALRM);
				//杀死父子进程
				kill(pid,SIGKILL);
				kill(getpid(),SIGKILL);
			}
			else
			{
				//printf("对方的父进程ID:%d   对方的子进程ID:%d\n",p->f_pid,p->c_pid);
				pid_t send_pid=p->c_pid;//唤醒对方进程号
				p->f_pid=getppid();//将本进程的父进程ID放到共享内存中
				p->c_pid=getpid();//将本进程的子进程ID放到共享内存中
				//唤醒对方子进程进行消息队列的删除
				kill(send_pid,SIGALRM);
			}
		}
		else if(pid>0)//父进程 往B类型的消息队列发送消息
		{
			//printf("执行父进程\n");
			printf("please input typeb content:\n");
			fflush(stdin);
			fgets(msg.mtext,100,stdin);
			msg.mtype =  MSG_TYPE_B;
			//strcpy(msg.mtext, "TAPE_B nihaonihao");//消息队列内容
			int ret = msgsnd(msgid, (void *)&msg, 100, 0);
			if(ret == -1)
			{
				perror("TYPEB 消息队列发送失败");
			}
			else
			{
				//perror("TYPEB 消息队列发送成功");
			}

			//打印共享内存中的内容
			//printf("对方的父进程ID:%d   对方的子进程ID:%d\n",p->f1_pid,p->c1_pid);
			if(strcmp(msg.mtext,"quit\n")==0)
			{   //4.删除消息队列

				kill(p->f1_pid,SIGALRM);
				p->f1_pid=getpid();
				p->c1_pid=pid;
				pause();
				int ret=msgctl(msgid, IPC_RMID, NULL);
				if(ret == -1) 
				{   
					perror("删除消息队列失败");
					return 0;
				}   
				else
				{   
					//perror("删除消息队列成功");
				}   
				kill(pid,SIGKILL);
				kill(getpid(),SIGKILL);
			}
			else
			{
				//唤醒对方父进程实现读取
				kill(p->f1_pid,SIGALRM);
				p->f1_pid=getpid();
				p->c1_pid=pid;
				pause();
			}

		}
	}
	return 0;
}

