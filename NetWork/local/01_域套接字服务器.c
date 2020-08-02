/*================================================================
 *   Copyright (C) 2020 hqyj Ltd. All rights reserved.
 *   
 *   文件名称：01_域套接字服务器.c
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
	int sockfd = -1;
	sockfd = socket(AF_LOCAL,SOCK_STREAM,0);

	int b_reuse = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int));

	struct sockaddr_un sun;
	bzero(&sun,sizeof(sun));
	sun.sun_family    = AF_LOCAL;
	strncpy(sun.sun_path,PATH,strlen(PATH));

	if(!access(PATH,F_OK))unlink(PATH);

	if(bind(sockfd,(struct sockaddr*)&sun,sizeof(sun))<0){
		perror("bind");
		exit(1);
	}

	if(listen(sockfd,BACKLOG)<0){
		perror("listen");
		exit(1);
	}


	char buf[BUFSIZ]={};

	//创建集合
	fd_set readfds,temp;
	//初始化集合（清空集合）
	FD_ZERO(&readfds);
	FD_ZERO(&temp);
	//把关心的文件描述符加入集合
	FD_SET(0,&readfds);
	FD_SET(sockfd,&readfds);

	puts("IO多路复用服务器就绪");
	int maxfd = sockfd;
	int val = -1;
	int i = -1;
	ssize_t recv_t = -1;

	int setfd = -1;
	int input_t = -1;
	int ret = -1;
	int acceptfd = -1;
	puts("输入方式：“客户端对应的文件描述符 内容");
	while(1){
		temp = readfds;
		val = select(maxfd+1,&temp,NULL,NULL,NULL);
		if(val<0){
			perror("select");
			exit(1);
		}
		//轮训判断那个文件描述符产生事件
		for(i=0;i<maxfd+1;i++){
			if(FD_ISSET(i,&temp)){
				if(0==i){//是键盘输入产生事件
					bzero(buf,sizeof(buf));
					input_t = scanf("%d %s",&setfd,buf);
					while(getchar()!='\n');
					if(input_t !=2){
						puts("输入错误！请按格式输入：fd+空格+消息内容");
						continue;
					}
					if(!FD_ISSET(setfd,&readfds)){
						puts("输入fd号错误，没有这个链接！");
						continue;
					}
					//发出信息
					do{
						ret = send(setfd,buf,strlen(buf),0);
					}while(ret<0 && EINTR==errno);
				}
				//如果是socket产生的套接字文件描述符
				//那就说明是要建立连接
				else if(sockfd == i){
					acceptfd = accept(sockfd,NULL,NULL);
					if(acceptfd < 0){
						perror("accept");
						exit(1);
					}
					//newfd加入集合
					FD_SET(acceptfd,&readfds);
					//更新maxfd（判断那个最大的文件描述符是那个）
					maxfd = (maxfd > acceptfd) ? maxfd : acceptfd;
				}
				else//剩下的情况就是所有的客户端对应的newfd了
				{
					bzero(buf,sizeof(buf));
					//i就是产生事件的客户端对应的fd
					//接收消息
					do{
						recv_t = recv(i,buf,sizeof(buf),0);
					}while(recv_t < 0 && EINTR==errno);
					if(recv_t <= 0){
						perror("客户端错误或关闭");
						FD_CLR(i,&readfds);
						close(i);
						maxfd = (( i == maxfd) ? (--maxfd) : maxfd);
					}
					else{
						printf("收到%d 消息：%s\n",i,buf);
					}
				}
			}
		}
	}

	close(sockfd);

	return 0;
}

