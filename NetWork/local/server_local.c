#include <stdio.h>                                                       
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/un.h>

#define  QUIT     "quit"
#define  BUF_SIZE 100
#define  SERVER_PORT     1258
#define  SERVER_IP  "192.168.75.156"
#define  CLIENT_IP  "192.168.75.156"
#define  CLIENT_PORT  6666

int main(int argc,char *argv[])
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	int i,byte;
	char ch_send,recv_buf[128];
	
	unlink("server_socket");	//解除原有server_socket对象链接
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);//创建socket，指定通信协议为AF_UNIX,数据方式SOCK_STREAM
	//配置server_address
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
 
	listen(server_sockfd, 5);
	
	printf("server waiting for  client connect\n");
	client_len = sizeof(client_address);
	//accept函数接收客户端求情，存储客户端地址信息、客户端地址大小
	client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, (socklen_t *)&client_len);
	printf("the server wait form client data\n");
	  
	for(i=0,ch_send='1';i<5;i++,ch_send++)
	{
		//从client_sockfd读取客户端发来的消息
		if((byte=read(client_sockfd, recv_buf, sizeof(recv_buf)))==-1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		printf("the massage receiver from client is: %s\n",recv_buf);
		sleep(1);
		//向客户端发送消息
		if((byte=write(client_sockfd,&ch_send,1))==-1)
		{
		   	perror("write");
			exit(EXIT_FAILURE);
		}
    }
	close(client_sockfd);
	unlink("server socket");
	return 0;
}
