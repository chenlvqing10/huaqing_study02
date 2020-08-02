#include "multicast.h"

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

	//创建多播组
	struct ip_mreqn mreqn;
	struct sockaddr_in saddr;//服务器端地址
	memset(&saddr,0,sizeof(saddr));//结构体清0
	memset(&mreqn,0,sizeof(mreqn));//结构体清0

	//填入多播组的地址
	inet_pton(AF_INET,MGROUP,&mreqn.imr_multiaddr);
	//填入你本机的地址
	inet_pton(AF_INET,"0.0.0.0",&mreqn.imr_address);
	//加入网络设备索引号
	mreqn.imr_ifindex=2;

	//设置sock属性
	if(setsockopt(sock,IPPROTO_IP,IP_MULTICAST_IF,(void*)&mreqn,sizeof(mreqn))<0)
	{
		perror("set multicast");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("set multicast");
		printf("多播组设置成功\n");
	}
	struct msg_st sbuf;
	memset(&sbuf,'\0',sizeof(sbuf));
	strcpy(sbuf.name,"xiaoming");
	sbuf.math    = 99;
	sbuf.chinese = 100;

	saddr.sin_family    = AF_INET;
	saddr.sin_port      = htons(atoi(RCVPORT));
	//发送地址要改成多播组地址,向多播组群发消息
	inet_pton(AF_INET,MGROUP,&saddr.sin_addr);
	char ip[20]={0};
	while(1)
	{
		if(sendto(sock,&sbuf,sizeof(sbuf),0,
					(struct sockaddr *)&saddr,sizeof(saddr)) <0){
			perror("sent multicase");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("sent multicase");

		}
		if((inet_ntop(AF_INET, (void *)&saddr.sin_addr.s_addr,ip,sizeof(saddr)))==NULL)//将IP转化为点分十进制形式
		{
			perror("ip error");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("ip=%s   port=%d\n",ip,ntohs(saddr.sin_port));
		}

		sleep(5);
	}
	close(sock);
	return 0;
}
