#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define  BUF_SIZE 100
#define  QUIT     "quit"
#define  PORT	  1235

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

	//获取套接字属性
	//int getsockopt(int sockfd, int level, int optname,void *optval, socklen_t *optlen);
	//设置套接字属性
	//int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t optlen);
	/*int optval=-1;
	socklen_t optlen=sizeof(optval);
	getsockopt(serv_sock,SOL_SOCKET,SO_SNDBUF,(void*)&optval,&optlen);
	printf("发送缓冲区大小:%d\n",optval);
	getsockopt(serv_sock,SOL_SOCKET,SO_RCVBUF,(void*)&optval,&optlen);
	printf("接收缓冲区大小:%d\n",optval);
	*/
	//快速复用
	int b_reuse = -1;
	socklen_t b_len=sizeof(int);
	if(getsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&b_reuse,&b_len)<0)
	{
		perror("get sockopt");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("快速复用属性的数值:%d\n",b_reuse);
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
#if 0   //IP地址优化----任意IP地址
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
#else
	serv_addr.sin_addr.s_addr=inet_addr("192.168.199.255");//广播地址
	//serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//本机地址
	//const char straddr[20]="192.168.0.58";
	//serv_addr.sin_addr.sin_addr=inet_pton(AF_INET, straddr, &serv_addr.sin_addr.s_addr);
#endif
	serv_addr.sin_port=htons(PORT);//端口号

#if 1	
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
		printf("广播标识:%d\n",broadflag);
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
	printf("广播发送端绪\n");
	char buffer_broad[BUF_SIZE]={0};
	while(1)
	{
		fprintf(stdout,"输入广播内容:");
		if(fgets(buffer_broad,BUF_SIZE-1,stdin)==NULL)
		{
			perror("fgets");
			continue;
		}
        //发送广播
        if(sendto(serv_sock,buffer_broad,strlen(buffer_broad),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
        {
            perror("broad send:");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("broad send");
			printf("广播发送的内容:%s\n",buffer_broad);
        }
         if(!strncasecmp(buffer_broad,QUIT,4))
         {
             printf("退出成功\n");
             close(serv_sock);
             shutdown(serv_sock,2);//不允许收发数据
             exit(EXIT_SUCCESS);
         }
	}
	close(serv_sock);


#else//服务端通信
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
	//	listen(serv_sock,20);

	//接收客户端请求
	struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
	socklen_t clnt_addr_size=sizeof(clnt_addr);//客户端地址的长度
	bzero(&clnt_addr,clnt_addr_size);//置0
	char buffer[BUF_SIZE]={};//定义缓冲区

	char ip[20]={0};
	while(1)
	{
		//使用recvfrom函数从客户端接收数据
		if(recvfrom(serv_sock,buffer,BUF_SIZE-1,0,(struct sockaddr*)&clnt_addr,&clnt_addr_size)<0)
		{
			perror("recieve from client error");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("recieve from client success");
			if((inet_ntop(AF_INET, (void *)&clnt_addr.sin_addr.s_addr,ip,sizeof(clnt_addr)))==NULL)
			{
				perror("ip error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("ip=%s  port=%d   从客户端接收到的数据:%s\n",ip,ntohs(serv_addr.sin_port),buffer);
			}
		}

		if(!strncasecmp(buffer,QUIT,4))
		{
			printf("ip=%s  port=%d  退出成功\n",ip,ntohs(serv_addr.sin_port));
			//接收到数据后将数据原样发送回去
			if(sendto(serv_sock,buffer,strlen(buffer),0,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr))<0)
			{
				perror("send to client:");
				exit(EXIT_FAILURE);
			}
			else
			{
				perror("send to client:");
			}
			close(serv_sock);
			shutdown(serv_sock,2);//不允许收发数据
			exit(EXIT_SUCCESS);
		}

		//接收到数据后将数据原样发送回去
		if(sendto(serv_sock,buffer,strlen(buffer),0,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr))<0)
		{
			perror("send to client:");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("send to client:");
		}


		memset(buffer,0,BUF_SIZE);//重置缓冲区
	}
	close(serv_sock);
#endif
	return 0;
}
