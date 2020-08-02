/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//多线程变成的互斥和同步机制------------------生产者和消费者问题 
struct prodcons buffer;
//设置
#define BUFFER_SIZE 20
#define OVER -1
/*设置一个环形的整数缓冲区*/
struct prodcons{
	int buffer[BUFFER_SIZE];//缓冲区数组
	pthread_mutex_t mutex_lock;//互斥锁
	pthread_cond_t notempty;//缓冲区非空信号 条件变量
	pthread_cond_t notfull;//缓冲区非满信号 条件变量
	int readpos,writepos;//读写的位置
};

/*初始化缓冲区*/
void init(struct prodcons *b)
{
	pthread_mutex_init(&b->mutex_lock,NULL);//初始化互斥锁
	pthread_cond_init(&b->notempty,NULL);//初始化非满条件变量
	pthread_cond_init(&b->notfull,NULL);//初始化非空条件变量
	b->readpos=0;
	b->writepos=0;
}

/*向缓冲区中写入一个整数*/
void put(struct prodcons *b,int data)
{
	sleep(2);
	//Lock
	pthread_mutex_lock(&b->mutex_lock);
	//printf("生产者进程锁定\n");
	//等待缓冲区非满条件成立
	//printf("put  readpos=%d  writepos=%d\n",b->readpos,b->writepos);

	while((b->writepos+1)%BUFFER_SIZE==b->readpos)//缓冲区满
	{
		//printf("等待非满条件满足\n");
		pthread_cond_wait(&b->notfull,&b->mutex_lock);//生产了16件产品之后，缓冲区满 非满条件不满足  生产者线程解锁  被阻塞在这里
	}
	//写数据并且指针前移
	b->buffer[b->writepos]=data;
	b->writepos++;
	if(b->writepos>=BUFFER_SIZE)
		b->writepos=0;
	//设置缓冲区非空信号
	pthread_cond_signal(&b->notempty);//唤醒非空线程
	//pthread_cond_broadcast(&b->notempty);
	//printf("已经向缓冲区写了数据,消费者线程将被唤醒\n");
	pthread_mutex_unlock(&b->mutex_lock);
	//printf("生产者线程被解锁\n");
	sleep(2);
}

//从缓冲区读出一个整数
int get(struct prodcons *b)
{
	int data;
	pthread_mutex_lock(&b->mutex_lock);
	//printf("消费者线程锁定\n");
	//printf("get  readpos=%d  writepos=%d\n",b->readpos,b->writepos);
	//等待缓冲区非空
	while(b->writepos==b->readpos)//缓冲区空
	{
		//printf("等待非空条件满足\n");
		pthread_cond_wait(&b->notempty,&b->mutex_lock);//条件不满足，解锁 条件在这里阻塞  条件满足，继续向下执行
	}
	//Lock
	//读取数据并且指针前移
	data=b->buffer[b->readpos];
	b->readpos++;
	if(b->readpos>=BUFFER_SIZE)
		b->readpos=0;
	//设置缓冲区非满信号
	pthread_cond_signal(&b->notfull);
	//printf("已经从缓冲区读出了数据,生产者线程将被唤醒\n");
	pthread_mutex_unlock(&b->mutex_lock);
	//printf("消费者线程被解锁\n");

	sleep(2);
	return data;
}

//定义生产者和消费者的函数
void* producer(void* arg) //生产者线程
{
	//printf("执行生产者线程\n");
	int n;
	for(n=0;n<BUFFER_SIZE;n++)//生产n件产品
	{
		printf("生产第%d件产品\n",n+1);
		put(&buffer,n);//将生产产品的个数写进Buffer数组
	}

	//生产完了
	put(&buffer,OVER);
	printf("生产停止\n");
	return NULL;

}

void* consumer(void* arg) //消费者线程
{
	//printf("执行消费者线程\n");
	int d = 0;
	while (1)
	{
		d=get(&buffer);
	//	printf("d=%d\n",d);
		if(d==OVER)
			break;
		printf("消费第%d个产品\n",d+1);
	}
	buffer.buffer[0]=0;
	//消费完了
	printf("消费停止\n");
	return NULL;
}


int main() 
{
	//初始化系统变量
	pthread_t th_a,th_b;//创建的线程名
	void* retval;//线程退出的返回状态
	init(&buffer);//初始化函数

	//创建线程
	pthread_create(&th_a,NULL,producer,NULL);
	pthread_create(&th_b,NULL,consumer,NULL);

	//等待生产者和消费者结束
	pthread_join(th_a,&retval);//阻塞main  等待th_a线程
	pthread_join(th_b,&retval);//等待th_b线程

	//打印Buffer数组
	for(int i=0;i<BUFFER_SIZE;i++)
		printf("data=%d\n",buffer.buffer[i]);

	//销毁锁
	pthread_mutex_destroy(&buffer.mutex_lock);
	pthread_cond_destroy(&buffer.notempty);
	pthread_cond_destroy(&buffer.notfull);

	return 0;
}


