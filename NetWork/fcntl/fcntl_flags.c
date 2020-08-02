#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc,char*argv[])
{
	/*
	   int flag;
	   char buf[128]={};
	//1获取文件描述符标记属性
	flag = fcntl(0,F_GETFL);
	//2设置
	flag |= O_NONBLOCK;
	//3写回去
	fcntl(0,F_SETFL,flag);

	while(1){
	bzero(buf,sizeof(buf));
	fgets(buf,sizeof(buf),stdin);
	sleep(1);
	printf("------buf:%s\n",buf);
	}
	*/
	//打开鼠标驱动
	int fd=-1;
	fd=open("/dev/input/mouse0",O_RDONLY);
	printf("fd=%d\n",fd);
	if(fd<0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	else
		perror("open");

	fd_set rfds;
	fd_set temp;
	struct timeval tv;
	int retval;

	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&rfds);//清空fd集合
	FD_SET(0, &rfds);//向fd集合中添加文件描述符(stdin)
	FD_SET(fd,&rfds);
	/* Wait up to five seconds. */
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	while(1){
		temp=rfds;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		retval = select(fd+1, &temp, NULL, NULL, &tv);
		/* Don't rely on the value of tv now! */
		if (retval == -1)
			perror("select()");
		else if (retval>0)
		{
			//printf("Data is available now.\n");
			if(FD_ISSET(0,&temp))
				printf("键盘输入\n");
			sleep(5);
			if(FD_ISSET(fd,&temp))
				printf("鼠标动了\n");
		}
		/* FD_ISSET(0, &rfds) will be true. */
		else if(retval==0)
		{
			printf("No data within five seconds.\n");
		}

	}
	exit(EXIT_SUCCESS);

	return 0;
}
