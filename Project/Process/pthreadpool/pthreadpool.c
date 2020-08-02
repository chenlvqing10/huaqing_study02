#include <sys/types.h>
#include <pthread.h>
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

typedef  void (*task_call_back_t)(void);//回调函数

struct task_s {
	task_call_back_t  process;   // 回调函数 当任务运行时 会调用此函数 
	void *arg;     //  回调函数的参数 
};

//线程池结构体------多个线程
struct pool_s {
	pthread_t *thread_id;			//  存储线程号
	int thread_limit;				//  线程池中,允许 活动的线程 数目
	struct task_s  list[100];		// 任务列表等待线程池处理的任务列表 
	int task_num_in_list;			// 有多少个任务 等待线程池 执行

	pthread_mutex_t  pool_lock;   // 互斥锁 
	pthread_cond_t   pool_cond;   // 条件变量
};

// 线程池的服务函数 
void *pool_thread_server(void *arg)
{
	// 接收线程池对象 
	struct pool_s *pool = NULL;
	pool = (struct pool_s*)arg;

	while(1) {
		pthread_mutex_lock(&pool->pool_lock);//lock 只有一个线程可以进入临界区  其他进程阻塞睡眠
		// 如果 线程池中 没有 任务等待处理 
		if(pool->task_num_in_list == 0) 
		{
			while(pool->task_num_in_list == 0) {
				// 阻塞到 条件变量中 等待 被唤醒 
				// 1. 解锁
				// 2. 将线程 睡眠 到 条件变量中  , 等待被唤醒
				// pthread_cond_broadcast(); 
				printf("thread_id %lu is idle\n",pthread_self());
				pthread_cond_wait(&(pool->pool_cond), &(pool->pool_lock));
			}
		}  
		else //线程池中有任务
		{
			int num=pool->task_num_in_list;//第几个任务
			struct task_s tasks=pool->list[num];//获取任务
			printf("线程%lu正在处理任务\n",pthread_self());
			tasks.process();//调用任务处理函数
			printf("任务处理完毕\n");
			pool->task_num_in_list--;//线程池处理完一个任务
		}
		

		pthread_mutex_unlock(&pool->pool_lock);   
	}

}

// 功能 :创建线程池    
// @pool_p   线程池对象  
// @thread_num   线程池中 线程的个数  
void  pool_init(struct pool_s *pool_p, int thread_num)
{
	pool_p->thread_limit = thread_num;	  // 线程个数 
	pool_p->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);//分配内存空间 线程数*每个线程任务
	memset(pool_p->thread_id, 0, sizeof(pthread_t) * thread_num);  // 将申请的内存空间 清 0 
	pool_p->task_num_in_list = 0;         //   任务列表中 有0 个任务等待处理 
	pthread_mutex_init(&(pool_p->pool_lock), NULL);  // 初始化 互斥锁
	pthread_cond_init(&(pool_p->pool_cond),  NULL);  // 初始化 条件变量 
	
	// 创建线程
	for(int i = 0; i < thread_num; i++) 
	{
		// 创建  thread_num 个线程 
		pthread_create(&(pool_p->thread_id[i]), NULL, pool_thread_server, pool_p);
	}
	
	return ;
}

//给线程池添加任务
//@pool_P 线程池对象
//@process 任务函数
void add_task(struct pool_s *pool_p,task_call_back_t process)
{
	struct task_s tasks;//定义一个任务变量
	tasks.process=process;
	//因为线程池是一个临界资源 因此访问线程池需要加上互斥锁
	pthread_mutex_lock(&pool_p->pool_lock);
	/*临界区*/
	//给线程池添加任务
	pool_p->task_num_in_list++;
	int num=pool_p->task_num_in_list;
	pool_p->list[num]=tasks;
	/*临界区*/
	pthread_mutex_unlock(&pool_p->pool_lock);
	
	//唤醒线程池中的线程
	pthread_cond_broadcast(&pool_p->pool_cond);
}

void my_task(void)
{
	printf("线程正在处理任务\n");
	sleep(2);
}
int main(int argc, const char *argv[])
{
	struct pool_s pool;//定义一个线程池对象
	pool_init(&pool,3);//初始化线程池
	sleep(5);
	for(int i=0;i<50;i++)
	{
		add_task(&pool,my_task);
	}
	while(1)
	{
		sleep(2);
	}
	return 0;
}

