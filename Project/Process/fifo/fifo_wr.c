#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FIFO_SERVER "./myfifo"

int main(int argc,char* argv[])
{
	int fd;
	char w_buf[100];
	int nwrite;

	//if( (mkfifo(FIFO_SERVER,O_CREAT|O_EXCL)<0) && (errno!=EEXIST) )
	//printf("can not create fifo file\n");

	//fd=open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0);//以只读和非阻塞的形式打开fifo文件
	fd=open(FIFO_SERVER,O_WRONLY,0);//以只读和阻塞的形式打开fifo文件

	if(fd==-1)//判断打开是否成功
	{
		perror("open");
		if(errno==ENXIO)//无写的进程
		{
			printf("open error; no reading process\n");
		}
	}

	if(argc==1)//输入参数
		printf("Please send something\n");
	else
	{
		strcpy(w_buf,argv[1]);//将命令行第二个参数copy到写缓冲数组中
		printf("w_buf=%s\n",w_buf);
	}

	while(-1)
	{
		if((nwrite=write(fd,w_buf,100))==-1)//将缓冲区内容写入管道
		{
			perror("write");

			if(errno==EAGAIN)
				printf("The FIFO has not been read yet.Please try later\n");
		}
		else 
			printf("write %s to the FIFO\n",w_buf);
		sleep(1);
	}		
	return 0;
}


