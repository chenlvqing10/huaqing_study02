#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
//共享内存

struct node {
	pid_t pid;
	char buf[100];
};

void my_func_handler(int sig)
{

}
pid_t pid_r = 0;

int main(int argc, const char *argv[])
{
	signal(SIGALRM, my_func_handler);//signal:给当前进程e799bee5baa6e58685e5aeb931333337616634注册SIGALRM信号处理代码，若收到SIGALRM信号，就去执行函数内容  SIGALRM是在定时器终止时发送给进程的信号
	
	//------------创建key值
	key_t key;
	char poj_id = 'l';
	key = ftok("./app", poj_id);//可执行文件
	if(key == -1)//创建key失败
	{
		perror("ftok");
		return -1;
	}
	
	//创建共享内存
	int shmid = 0;
	shmid = shmget(key, 1000, IPC_CREAT|IPC_EXCL|0777);
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

	printf("共享内存id号:%d\n",shmid);//打印共享内存id
	
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
	

	struct node *p = (struct node *)addr;//将结构体指针指向虚拟内存的首地址，以操作该共享内存
	pid_r = p->pid;  // 通过共享内存获取 对方的进程ID
	p->pid = getpid();  // 将自己的进程号(write)放到共享内存中
	kill(pid_r, SIGALRM);  // 唤醒
	printf("对方的进程ID:%d\n",pid_r);

	while(1) {
		bzero(p->buf, 100);//共享内存清零
		printf("plase input:");
		fflush(stdin);//刷新标准输入
		fgets(p->buf, 100, stdin);//从标准输入获取字符到共享内存
		if(strcmp(p->buf , "quit\n") == 0)//如果共享内存输入的是quit命令就杀死本进程
		{
			kill(pid_r, SIGALRM);//唤read进程
			raise(SIGKILL);
			//kill(getpid(), SIGKILL);
		}
		else
		{
			kill(pid_r, SIGALRM);//唤read进程
			pause();//阻塞write进程
		}
		if(strcmp(p->buf , "quit\n") == 0)//如果read进程输入的是quit命令则同时杀死本进程
		{
			raise(SIGKILL);
			//kill(getpid(), SIGKILL);
		}
		printf("从read进程得到的内容:%s\n", p->buf);

	}
	

	//4.撤销共享内存映射
	shmdt(addr);
	//删除共享内存
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}

