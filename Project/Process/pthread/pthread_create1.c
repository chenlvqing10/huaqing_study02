/*waitpid.c*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void*ThreadEntry(void*arg)
{
    (void)arg;
    while(1)
    {
        printf("I am thread,%lu\n",pthread_self());
        sleep(1);
    }
}
int main()
{
    int ret=0;
    pthread_t tid;
    ret=pthread_create(&tid,NULL,ThreadEntry,NULL);
    if(ret!=0)
    { 
        perror("pthread_create");
        exit(1);
    }
    while(1)
    {
        printf("I am main,%lu\n",pthread_self());
        sleep(1);
    }
    return 0;
}
