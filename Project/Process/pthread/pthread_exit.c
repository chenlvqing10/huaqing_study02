/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *thread_function(void *arg);

char message[] = "Hello World";//全局变量

void *thread_function(void *arg) {
    printf("thread_function is running. Argument was -->%s\n", message);
    sleep(3);
    strcpy(message, "Bye!");//将全局变量变为bye 因为线程执行将要结束
    pthread_exit("Thank you for the CPU time");
}

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
 
	res = pthread_create(&a_thread, NULL, thread_function, (void *)message);//创建线程
    
	if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for thread to finish...\n");
    
	res = pthread_join(a_thread, &thread_result);//等待thread_function线程执行结束 thread_result得到函数pthread_exit()的退出状态信息
    
	if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined, it returned -->%s\n", (char *)thread_result);
    
	printf("Message is now -->%s\n", message);
    exit(EXIT_SUCCESS);
}


