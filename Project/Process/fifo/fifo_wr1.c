#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FIFO "./myfifo"  //命名管道文件

int main(int argc,char** argv)
{
	char buf_r[100];
	int  fd;
	int  nread;
	
	if((mkfifo(FIFO,0777)<0)&&(errno!=EEXIST))//创建fifo文件
		printf("cannot create fifoserver\n");


	printf("Preparing for reading bytes...\n");//读取数据
	memset(buf_r,0,sizeof(buf_r));//写缓冲区初始化

	//fd=open(FIFO,O_RDONLY|O_NONBLOCK,0);//以只读和非阻塞方式打开fifo文件
	fd=open(FIFO,O_RDONLY,0);//以只读和非阻塞方式打开fifo文件
	if(fd==-1)
	{
		perror("open");
		exit(1);	
	}

	while(1)
	{
		memset(buf_r,0,sizeof(buf_r));//初始化

		if((nread=read(fd,buf_r,100))==-1)//从fifo管道文件中读取数据
		{
			perror("read");
			if(errno==EAGAIN)
				printf("no data yet\n");
		}

		printf("read %s from FIFO\n",buf_r);
		
		sleep(1);
	}	

	pause();
	unlink(FIFO);
	return 0;
}


