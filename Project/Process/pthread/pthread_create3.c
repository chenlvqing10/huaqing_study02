/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void thread1(void)
{
	int tid = pthread_self();

	printf("线程1:This is a pthread.Tid[%d]\n", tid);
/*
	if(execv(exe_file, NULL)<0)
	{
		perror("Err on execl");
	}
*/
}


void thread2(void)
{
	int tid = pthread_self();


	printf("线程2:This is a pthread.Tid[%d]\n", tid);
/*
	if(execv(exe_file, NULL)<0)
	{
		perror("Err on execl");
	}
*/
}


int main(void)
{
	pthread_t id1,id2;
	int ret;


	ret = pthread_create(&id1,NULL,(void *) thread1,NULL);

	ret = pthread_create(&id2,NULL,(void *) thread2,NULL);

	if(ret!=0)
	{
		printf ("Create pthread error!\n");
		exit (1);
	}

	pthread_join(id1,NULL);//main线程等待idl线程执行结束
	pthread_join(id2,NULL);//等待id2线程执行结束
	printf("This is the main process.\n");//main线程最后执行

	return (0);
}



