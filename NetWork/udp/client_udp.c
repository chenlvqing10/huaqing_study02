#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define  BUF_SIZE 100
#define  QUIT     "quit"
#define  PORT	  1235
int main()
{
	//结构体设置
	//创建套接字
	int sock=socket(AF_INET,SOCK_DGRAM,0);//UDP
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
	struct sockaddr_in serv_addr;//服务器端地址
	memset(&serv_addr,0,sizeof(serv_addr));//结构体清0
	socklen_t serv_addr_size=sizeof(serv_addr);//结构体大小
	serv_addr.sin_family=AF_INET;//IP地址类型:ipv4
#if 1   //IP地址优化----任意IP地址
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
#else
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//本机地址
	//const char straddr[20]="192.168.0.58";
	//serv_addr.sin_addr.sin_addr=inet_pton(AF_INET, straddr, &serv_addr.sin_addr.s_addr);
#endif
	serv_addr.sin_port=htons(PORT);//端口号
	char buffersend[BUF_SIZE]={0};//客户端发送缓冲区
	char bufferrecv[BUF_SIZE]={0};//客户端接收缓冲区
	char ip[20]={0};

#if 1
	/*------------多点通讯-------------------*/
	int broadflag=-1;
	socklen_t broadflaglen=sizeof(broadflag);
	if(getsockopt(sock,SOL_SOCKET,SO_BROADCAST,(void*)&broadflag,&broadflaglen)<0)
	{
		perror("get broadcast");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("get broadcast");
		printf("广播标识:%d\n",broadflag);
		if(broadflag==0)
		{
			broadflag=1;
			if(setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(void*)&broadflag,broadflaglen)<0)
			{
				perror("set broadflag");
				exit(EXIT_FAILURE);
			}
			else
			{
				perror("set broadflag");
				printf("广播标志设置成功:%d\n",broadflag);
			}
		}
	}
    if(bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)//将套接字与特定的IP地址和端口号绑定起来  
    {
        perror("bind server");
        exit(EXIT_FAILURE);
    }
    else
    {
        perror("bind server");
    }

	printf("广播接收端就绪\n");
	while(1)
	{
		printf("123456789");
		//读取服务器返回的数据并打印
		if(recvfrom(sock,bufferrecv,BUF_SIZE-1,0,(struct sockaddr*)&serv_addr,&serv_addr_size)<0)
		{
			perror("recieve from server error");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("recieve from server success");
			if((inet_ntop(AF_INET, (void *)&serv_addr.sin_addr.s_addr,ip,sizeof(serv_addr)))==NULL)
			{
				perror("ip error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("ip=%s  port=%d   从服务器接收到的数据:%s\n",ip,ntohs(serv_addr.sin_port),bufferrecv);
			}
		}

		if(!strncasecmp(bufferrecv,QUIT,4))
		{
			printf("ip=%s  port=%d  退出成功\n",ip,ntohs(serv_addr.sin_port));
			shutdown(sock,2);//不允许收发数据
			close(sock);
			exit(EXIT_SUCCESS);
		}
		close(sock);
	}

#else
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)//客户端与服务器端进行连接
	{
		perror("connect server");//连接失败
		exit(EXIT_FAILURE);
	}
	else
		perror("connect server");//连接成功
	while(1)
	{
		//向服务器发送数据
		printf("输入发送信息：");
		fgets(buffersend,100,stdin);

		//向套接字写入/发送数据
		if(sendto(sock,buffersend,strlen(buffersend),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		{
			perror("send to server:");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("send to server:");
		}
		printf("客户端发送的信息:%s\n",buffersend);


		//读取服务器返回的数据并打印
		if(recvfrom(sock,bufferrecv,BUF_SIZE-1,0,(struct sockaddr*)&serv_addr,&serv_addr_size)<0)
		{
			perror("recieve from server error");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("recieve from server success");
			if((inet_ntop(AF_INET, (void *)&serv_addr.sin_addr.s_addr,ip,sizeof(serv_addr)))==NULL)
			{
				perror("ip error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("ip=%s  port=%d   从服务器接收到的数据:%s\n",ip,ntohs(serv_addr.sin_port),bufferrecv);
			}
		}

		if(!strncasecmp(bufferrecv,QUIT,4))
		{
			printf("ip=%s  port=%d  退出成功\n",ip,ntohs(serv_addr.sin_port));
			shutdown(sock,2);//不允许收发数据
			close(sock);
			exit(EXIT_SUCCESS);
		}

		memset(buffersend,0,BUF_SIZE);
		memset(bufferrecv,0,BUF_SIZE);
		//关闭套接字
		close(sock);
	}
#endif
	return 0;
}
