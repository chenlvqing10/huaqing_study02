#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>

#define  QUIT	  "quit"
#define  BUF_SIZE 100
#define  PORT     1256
#define  SERVER_IP  "192.168.75.151"
#define  CLIENT_IP	"192.168.1.111"
#define  CLIENT_PORT  6661
int main()
{
	//创建套接字
	int serv_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock<0)
	{
		perror("socket create");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("socket create");
		printf("serv_sock=%d\n",serv_sock);
	}
	//地址快速重用
	int b_reuse = 1;
	if(setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int)) <0){
		perror("setsockopt");
		exit(1);
	}
	puts("----设置地址快速重用成功----");

	//设置服务器端 IP，端口号
	struct sockaddr_in serv_addr;//服务器端地址
	memset(&serv_addr,0,sizeof(serv_addr));//地址大小
	serv_addr.sin_family=AF_INET;//IP地址类型:ipv4
	serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);//服务器地址
	serv_addr.sin_port=htons(PORT);//端口号//服务器端口号
	//设置客户端IP地址和端口号
	struct sockaddr_in clnt_addr;//客户端地址
	memset(&clnt_addr,0,sizeof(clnt_addr));//地址大小
	clnt_addr.sin_family=AF_INET;//IP地址类型:ipv4
	clnt_addr.sin_addr.s_addr=inet_addr(SERVER_IP);//客户端地址
	clnt_addr.sin_port=htons(CLIENT_PORT);//客户端端口号

	if(bind(serv_sock,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr))<0)//将套接字与特定的IP地址和端口号绑定起来
	{
		perror("bind server");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("bind server");
		printf("服务器就绪\n");
	}


	char buffersend[BUF_SIZE]={0};//客户端发送缓冲区

	if(connect(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)//客户端与服务器端进行连接  TCP三次握手连接
	{
		perror("connect server");//连接失败
		exit(EXIT_FAILURE);
	}
	else
		perror("connect server");//连接成功



	//循环发送信息
	while(1)
	{
		memset(buffersend,0,BUF_SIZE);
		//向服务器发送数据
		printf("输入发送信息：");
		fgets(buffersend,100,stdin);

		//向套接字写入数据 
		int send_ret=send(serv_sock,buffersend,strlen(buffersend),0);
		if(send_ret<0)//可用write代替
		{
			perror("send to server");
			exit(EXIT_FAILURE);
		}
		else if(send_ret>0) 
		{
			perror("send to server");
			char ip[20]={0};
			if((inet_ntop(AF_INET, (void *)&serv_addr.sin_addr.s_addr,ip,sizeof(serv_addr)))==NULL)//将IP转化为点分十进制形式
			{
				perror("ip error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("+++++++服务器端++++++++ip=%s   port=%d\n",ip,ntohs(serv_addr.sin_port));
			}

			printf("客户端发送的信息:%s",buffersend);

			if(0 == strncasecmp(buffersend,QUIT,strlen(QUIT))){                         
				puts("++++++你已经退出+++++++");
				shutdown(serv_sock,SHUT_RDWR);
				break;
			}
		}
	}
	close(serv_sock);
	return 0;
}
