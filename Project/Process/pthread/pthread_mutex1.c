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

//定义一个全局变量，函数声明
int sum=0;
void increase_num(void *arg);

//增加i次，函数的实现
void increase_num(void *arg)
{
  int *a=(int*)arg;//定义一个中间变量来得到参数的数值

  long tmp;
  for(int i =0;i<=10000;++i)
  {
	  // lock
    if(pthread_mutex_lock(&mutex) != 0)
    {
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }

    tmp = sum;
    tmp = tmp + 1;//加i次
    sum = tmp;
	 // unlock
    if(pthread_mutex_unlock(&mutex) != 0)
    {
      perror("pthread_mutex_unlock");
      exit(EXIT_FAILURE);
    }

  }
  printf("pthread:sum=%d\n",sum+*a);
  if(*a==100)
	printf("执行子线程1\n");
  else if(*a==200)
	  printf("执行子线程2\n");
  else if(*a==300)
	  printf("执行子线程3\n");
}

int main() 
{
  int ret;
  static int a1,a2,a3;
  a1=100;
  a2=200;
  a3=300;

  pthread_t thread1,thread2,thread3;//创建3个简称
  
  ret = pthread_create(&thread1,NULL,(void *)&increase_num,(void*)&a1);
  ret = pthread_create(&thread2,NULL,(void *)&increase_num,(void*)&a2);
  ret = pthread_create(&thread3,NULL,(void *)&increase_num,(void*)&a3);
 
  if(ret!=0)
  {
	perror("create pthread");
	exit(-1);
  }

  //线程3  线程2  线程1的执行顺序是随机的
  pthread_join(thread1,NULL);//阻塞main线程,等待线程1
  pthread_join(thread2,NULL);//等待线程2
  pthread_join(thread3,NULL);//等待线程3
 
  while(1)//使main进程不要结束
  {
	printf("sum = %d\n",sum);
	sleep(10);
  }

	return 0;
}


