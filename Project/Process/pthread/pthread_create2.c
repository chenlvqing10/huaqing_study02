/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static long data=100;//静态全局变量

int add(int a,int b)
{
	return (a+b);
}
//定义线程创建时候的指针函数
void* my_thread(void *arg)
{
	long *data=(long *)arg;//因为arg是(void*)类型的指针 所以需要将定义一个中间变量来接受arg的数值 才可以进行计算

	printf("my_thread里arg的地址:%p\n",arg);

	while(1)
	{
		printf("my_thread:%s %d  %ld\n",__func__,__LINE__,*data);//预定义宏表__LINE__  当前程序行的行号，表示为十进制整型常量__func__指示当前函数名
		sleep(10);
		*data=*data+1;
		sleep(5);
		printf("thread:a+b=%d",add(11,44));
	}

	return NULL;
}

void func(void)
{
	pthread_t tid;
	printf("func里data的地址:%p\n",&data);//data取地址

	int res=pthread_create(&tid,NULL,my_thread,(void *)&data);//data---传递的参数  创建线程  （void*)的指针 所以要取地址

	if(res!=0)
	{
		perror("pthread create");
	}
}
int main()
{
	func();
	while(1)//死循环 让进程不要死掉   以调用线程
	{
		printf("main:%s %d  %ld\n",__func__,__LINE__,data);////预定义宏表__LINE__  当前程序行的行号，表示为十进制整型常量__func__指示当前函数名
		sleep(2);
		printf("process:a+b=%d",add(1111,44));
	}
	return 0;
}


