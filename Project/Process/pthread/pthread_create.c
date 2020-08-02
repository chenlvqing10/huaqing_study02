/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//定义线程创建时候的指针函数
void* child(void *arg)
{
	pthread_t tid=pthread_self();
	printf("thread %lu enter\n",tid);
}
int main()
{

	pthread_t a_thread;//线程ID
	pthread_t tid=pthread_self();

	printf("main thread %lu enter\n",tid);

	int res=pthread_create(&a_thread,NULL,child,NULL);
	
	if(res!=0)
	{
		printf("thread create failed!!!\n");
		exit(-1);
	}

	sleep(10);
	printf("main byebye!!!\n");
return 0;
}


