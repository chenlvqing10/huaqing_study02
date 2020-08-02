#include "multicast.h"

#define BUF_SIZE 200

int main(int argc,char *argv[])
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
	//设置快速复用
	int b_reuse = -1;
	socklen_t b_len=sizeof(int);
	if(getsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void*)&b_reuse,&b_len)<0)
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
			if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void*)&b_reuse,b_len)<0)
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

	//加入多播组
	struct ip_mreqn mreqn;
	struct sockaddr_in raddr;//客户端地址
	memset(&raddr,0,sizeof(raddr));//结构体清0
	memset(&mreqn,0,sizeof(mreqn));//结构体清0
	socklen_t raddr_len=sizeof(raddr);
	//填入多播组的地址
	inet_pton(AF_INET,MGROUP,&mreqn.imr_multiaddr);
	//填入你本机的地址
	inet_pton(AF_INET,"0.0.0.0",&mreqn.imr_address);
	//加入网络设备索引号
	mreqn.imr_ifindex=2;

	//设置sock属性
	if(setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&mreqn,sizeof(mreqn))<0)
	{
		perror("add multicast");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("add multicast");
		printf("多播组加入成功\n");
	}

	//bind 绑定本机IP和端口号
	raddr.sin_family    = AF_INET;
	raddr.sin_port      = htons(atoi(RCVPORT));
	//发送地址为本机地址
	inet_pton(AF_INET,"0.0.0.0",&raddr.sin_addr);
	if(bind(sock,(struct sockaddr*)&raddr,sizeof(raddr))<0)//将套接字与特定的IP地址和端口号绑定起来  
	{                                                                                                                     
		perror("bind server");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("bind server");

	}
	//循环接收数据
	struct msg_st rbuf;
	char ip[20]={0};
	while(1)
	{
		if(recvfrom(sock,&rbuf,sizeof(rbuf),0,(struct sockaddr*)&raddr,&raddr_len)<0)
		{
			perror("recieve data from server");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("recieve data from server");
			if((inet_ntop(AF_INET, (void *)&raddr.sin_addr.s_addr,ip,sizeof(raddr)))==NULL)//将IP转化为点分十进制形式
			{
				perror("ip error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("ip=%s   port=%d\n",ip,ntohs(raddr.sin_port));
			}
			printf("name=%s math=%d chinese=%d\n",rbuf.name,rbuf.math,rbuf.chinese);
		}
		sleep(5);
	}
	close(sock);
	return 0;
}
