/*================================================================
 *   Copyright (C) 2020 hqyj Ltd. All rights reserved.
 *   
 *   文件名称：02_域套接字客户端.c
 *   创 建 者：Chens
 *   创建日期：2020年04月26日
 *   描    述：
 *
 ================================================================*/


#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>

#define  QUIT         "quit"
#define BACKLOG       10
#define PATH          "./unix_sock"


int main(int argc, char *argv[])
{
	int fd = -1;
	fd = socket(AF_LOCAL,SOCK_STREAM,0);

	struct sockaddr_un sun;
	bzero(&sun,sizeof(sun));
	sun.sun_family    = AF_LOCAL;
	strncpy(sun.sun_path,PATH,strlen(PATH));

	if(access(PATH,F_OK|W_OK) <0){
		puts("路径文件不存在或没有权限");
		exit(1);
	}

	if( connect(fd,(struct sockaddr*)&sun,sizeof(sun))<0){
		perror("connect");
		exit(1);
	}

	puts("域套接字客户端OK！");
	

	int ret =-1;
	int fh =-1;
	fd_set readfds;
	int maxfd =-1;
	struct timeval tv={1,0};
	char buf[BUFSIZ]={};

	puts("准备就绪-----------");
	while(1){
		FD_ZERO(&readfds);
		FD_SET(0,&readfds);
		FD_SET(fd,&readfds);
		tv.tv_sec = 5;
		tv.tv_usec= 0;
		maxfd = fd;
		fh = select(maxfd+1,&readfds,NULL,NULL,&tv);
		if(fh<0){
			perror("select");
			exit(1);
		}
		if(FD_ISSET(0,&readfds)){//键盘输入了
			bzero(buf,BUFSIZ);
			do{
				ret = read(0,buf,BUFSIZ-1);
			}while(ret<0&&EINTR==errno);
			if(ret <0){
				perror("read");
				continue;
			}
			if(!ret)continue;
			if(write(fd,buf,strlen(buf))<0){
				perror("write");
				exit(1);
			}
			if(!strncasecmp(buf,QUIT,strlen(QUIT))){
				printf("***客户端退出***\n");
				break;
			}
		}
		if(FD_ISSET(fd,&readfds)){//接收数据
			bzero(buf,BUFSIZ);
			do{
				ret = read(fd,buf,BUFSIZ-1);
			}while(ret<0 && EINTR==errno);
			if(ret<0){
				perror("接收");
				continue;
			}
			if(!ret)break;
			printf("已收到：%s \n",buf);
		}
	}
	close(fd);

	return 0;
}

