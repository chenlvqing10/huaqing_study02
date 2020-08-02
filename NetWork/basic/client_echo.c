#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define  BUF_SIZE 100
 
int main()
{
 
	//向服务器发起请求
	struct sockaddr_in serv_addr;//服务器端地址
	memset(&serv_addr,0,sizeof(serv_addr));//地址大小
	serv_addr.sin_family=AF_INET;//IP地址类型:ipv4
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//IP地址:本机
	serv_addr.sin_port=htons(1234);//端口号
 
	char buffersend[BUF_SIZE]={0};//客户端发送缓冲区
	char bufferrecv[BUF_SIZE]={0};//客户端接收缓冲区
	while(1)
	{
		//创建套接字
		int sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(sock<0)
		{
			perror("socket create");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("socket create");
			printf("sock=%d\n",sock);
		}
		
		if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)//客户端与服务器端进行连接
		{
			perror("connect server");//连接失败
			exit(EXIT_FAILURE);
		}
		else
			perror("connect server");//连接成功
 
		//向服务器发送数据
		printf("输入发送信息：");
		fgets(buffersend,100,stdin);
		
		//向套接字写入数据
		write(sock,buffersend,sizeof(buffersend));
		printf("客户端发送的信息:%s\n",buffersend);

		//读取服务器返回的数据并打印
		read(sock,bufferrecv,sizeof(bufferrecv)-1);
		printf("接收到的消息：%s\n",bufferrecv);
 
		memset(buffersend,0,BUF_SIZE);
		memset(bufferrecv,0,BUF_SIZE);
		//关闭套接字
		close(sock);
	}
	return 0;
}
