
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
#define  BUF_SIZE 100
 
int main()
{
	//创建套接字
	int serv_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//与客户端的套接字应该是一样的
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

	 // 在sockfd_one绑定bind之前，设置其端口复用  
    //int opt = 1;  
    //setsockopt( serv_sock, SOL_SOCKET,SO_REUSEADDR,   
	//              (const void *)&opt, sizeof(opt) );
	
	  //将套接字和ip、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));//每个字节都用0填充
	serv_addr.sin_family=AF_INET;//使用ipv4地址
	
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//本机地址
	//const char straddr[20]="192.168.0.58";
	//serv_addr.sin_addr.sin_addr=inet_pton(AF_INET, straddr, &serv_addr.sin_addr.s_addr);

	serv_addr.sin_port=htons(1234);//端口号
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)//将套接字与特定的IP地址和端口号绑定起来
	{
		perror("bind server");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("bind server");
		printf("服务器就绪\n");
	}
 
	//服务端 进入监听状态，等待客户端用户发起请求
	listen(serv_sock,20);
 
	//接收客户端请求
	struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
	socklen_t clnt_addr_size=sizeof(clnt_addr);//客户端地址的长度
	char buffer[BUF_SIZE]={};//定义缓冲区
	while(1)
	{
		printf("11111111111\n");
		int clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);//产生一个新生成的套接字 接受客户端的请求时候激活accept函数  与客户端通信的时候用到的是新的套接字
		printf("222222222222222\n");
		if(clnt_addr_size==-1)//接收失败
		{
			perror("accept client");
			exit(EXIT_FAILURE);
		}
		else//接收成功
		{
			perror("accept client");
			printf("clnt_sock=%d\n",clnt_sock);
		}
			
		read(clnt_sock,buffer,sizeof(buffer));//套接字中读取数据(来自客户端的数据)  放入缓冲区
		printf("服务器端接收到的消息：%s\n",buffer);
		write(clnt_sock,buffer,sizeof(buffer));//将客户端得到的数据(缓冲区)原样不变地写回客户端
		
		close(clnt_sock); //关闭套接字
		memset(buffer,0,BUF_SIZE);//重置缓冲区
	}
	close(serv_sock);
	
	return 0;
}
