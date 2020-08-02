#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

//服务器端向客户端发送广播  故服务器端作为广播的发送端
#define  BUF_SIZE 100
#define  QUIT     "quit"
#define  PORT	  1240

int main()
{
	//创建套接字
	int serv_sock=socket(AF_INET,SOCK_DGRAM,0);//UDP
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

	//设置快速复用
	int b_reuse = -1;
	socklen_t b_len=sizeof(int);
	if(getsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&b_reuse,&b_len)<0)
	{
		perror("get sockopt");
		exit(EXIT_FAILURE);
	}
	else
	{
		//printf("快速复用属性的数值:%d\n",b_reuse);
		if(b_reuse==0)//设置快速复用属性为1
		{
			b_reuse=1;
			if(setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&b_reuse,b_len)<0)
			{
				perror("set sockopt");
				exit(EXIT_FAILURE);
			}
			else
			{
				perror("set sockopt");
				printf("设置快速复用成功\n");
			}
		}
	}
	printf("快速复用属性的数值:%d\n",b_reuse);


	//将套接字和ip、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));//每个字节都用0填充
	serv_addr.sin_family=AF_INET;//使用ipv4地	
#if 1   //IP地址优化----任意IP地址
	serv_addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);//采用广播的IP段
#else
	serv_addr.sin_addr.s_addr=inet_addr("192.168.199.255");//广播地址
	//serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//本机地址
	//const char straddr[20]="192.168.0.58";
	//serv_addr.sin_addr.sin_addr=inet_pton(AF_INET, straddr, &serv_addr.sin_addr.s_addr);
#endif
	serv_addr.sin_port=htons(PORT);//端口号

	/*------------多点通讯-------------------*/
	int broadflag=-1;
	socklen_t broadflaglen=sizeof(broadflag);
	if(getsockopt(serv_sock,SOL_SOCKET,SO_BROADCAST,(void*)&broadflag,&broadflaglen)<0)
	{
		perror("get broadcast");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("get broadcast");
		//printf("广播标识:%d\n",broadflag);
		if(broadflag==0)
		{
			broadflag=1;
			if(setsockopt(serv_sock,SOL_SOCKET,SO_BROADCAST,(void*)&broadflag,broadflaglen)<0)
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

	char buffer_sendbroad[BUF_SIZE]={0};//发送端缓冲区

	while(1)//从客户端得到广播
	{
		fprintf(stdout,"输入广播内容:");
		if(fgets(buffer_sendbroad,BUF_SIZE-1,stdin)==NULL)
		{
			perror("fgets");
			continue;
		}
		//发送广播
		if(sendto(serv_sock,buffer_sendbroad,strlen(buffer_sendbroad),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		{
			perror("broad send:");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("broad send");
			printf("广播发送的内容:%s\n",buffer_sendbroad);
		}
		if(!strncasecmp(buffer_sendbroad,QUIT,4))
		{
			printf("退出成功\n");
			close(serv_sock);
			shutdown(serv_sock,2);//不允许收发数据
			exit(EXIT_SUCCESS);
		}
		memset(buffer_sendbroad,0,BUF_SIZE);
	}
	close(serv_sock);
	return 0;
}
