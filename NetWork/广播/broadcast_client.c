#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//客户端接收服务端的广播

#define  BUF_SIZE 100
#define  QUIT     "quit"
#define  PORT	  1240
int main()
{
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

	//设置服务器端地址
	struct sockaddr_in serv_addr;//服务器端地址
	memset(&serv_addr,0,sizeof(serv_addr));//结构体清0
	socklen_t serv_addr_size=sizeof(serv_addr);//结构体大小
	serv_addr.sin_family=AF_INET;//IP地址类型:ipv4
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);//IP地址优化----任意IP地址 
	serv_addr.sin_port=htons(PORT);//端口号
	char bufferrecv[BUF_SIZE]={0};//客户端接收缓冲区
	char ip[20]={0};

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
		//读取服务器返回的数据并打印
		if(recvfrom(sock,bufferrecv,BUF_SIZE-1,0,(struct sockaddr*)&serv_addr,&serv_addr_size)<0)
		{
			perror("recieve from server error");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("recieve from server success");
			if((inet_ntop(AF_INET, (void *)&serv_addr.sin_addr.s_addr,ip,sizeof(serv_addr)))==NULL)//将IP转化为点分十进制形式
			{
				perror("ip error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("ip=%s  port=%d  从服务器接收到的数据:%s\n",ip,ntohs(serv_addr.sin_port),bufferrecv);
			}
		}

		if(!strncasecmp(bufferrecv,QUIT,4))
		{
			printf("ip=%s  port=%d  退出成功\n",ip,ntohs(serv_addr.sin_port));
			shutdown(sock,2);//不允许收发数据
			close(sock);
			exit(EXIT_SUCCESS);
		}
	}
	close(sock);

	return 0;
}
