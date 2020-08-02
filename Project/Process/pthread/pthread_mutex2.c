/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//多线程变成的互斥和同步机制

// add mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//互斥锁初始化

//定义一个全局变量，函数声明 如果buf太长，时间片到达，字符串没有完全倒置，此时倒置函数的线程互斥锁还没有解锁
char buf[100]="aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbb";

void* reversebuf(void* arg);
void* printbuf(void* arg);

//线程函数1  倒置一个字符串 如果buf太长，时间片到达，字符串没有完全倒置，此时倒置函数的线程互斥锁还没有解锁
void *reversebuf(void* arg)
{
	printf("执行线程reversebuf\n");


	while(1)
	{	
		//lock
		if(pthread_mutex_lock(&mutex) != 0)
		{
			perror("pthread_mutex_lock");
			exit(EXIT_FAILURE);
		}
		printf("互斥锁reverse锁定字符串没有倒置的时候:printbuf pthread:buf is:%s\n",buf);
		sleep(1);
		char *string=(char *)arg;
		char *ptr=string+strlen(string)-1;
		char temp;

		//临界区
		for(int i=0;i<strlen(string)/2;i++)
		{
			temp=*(string+i);
			*(string+i)=*ptr;
			*ptr=temp;
			ptr--;
			//printf("i=%d",i);
		}
		//printf("\n");
		//unlock
		if(pthread_mutex_unlock(&mutex) != 0)
		{
			perror("pthread_mutex_unlock");
			exit(EXIT_FAILURE);
		}
		printf("互斥锁reverse解锁后字符串倒置之后:printbuf pthread:buf is:%s\n",buf);
		sleep(1);
	}
	return NULL;
}

void* printbuf(void* arg)
{
	printf("执行线程printfbuf\n");
	//临界区
	while(1)
	{
		pthread_mutex_lock(&mutex);//lock
		printf("互斥锁print锁定:printbuf pthread:buf is:%s\n",buf);
		sleep(1);
		pthread_mutex_unlock(&mutex);//unlock
		printf("互斥锁print解锁:printbuf pthread:buf is:%s\n",buf);
		sleep(1);
	}


	pthread_exit("printbuf线程的返回状态:return printbuf function");
}

int main() 
{
	int ret;
	void* ret_join;
	pthread_t thread1,thread2;

	ret = pthread_create(&thread1,NULL,reversebuf,(void*)buf);
	ret = pthread_create(&thread2,NULL,printbuf,NULL);


	printf("main线程在执行\n");
	if(ret!=0)
	{
		perror("create pthread");
		exit(-1);
	}

	//线程1 线程2的执行迅速  是随机的  时间片调度机制  如果时间片到了 线程进入睡眠态
	pthread_join(thread1,NULL);//阻塞线程main进程,等待线程1
	pthread_join(thread2,&ret_join);//阻塞main线程,等待线程2

	printf("ret_join=%s\n",(char*)ret_join);
	while(1)//使main进程不要结束
	{
		printf("main pthread:buf is:%s\n",buf);
		sleep(10);
	}

	return 0;
}


