#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

#define  QUIT       "quit"
#define  BUF_SIZE	100
#define  PORT		1256
#define  SERVER_IP	"192.168.75.151"
//接收到SIFCHLD信号后，回收子进程

void client_info(struct sockaddr_in clnt_addr)
{
	char ip[20]={0};
	if((inet_ntop(AF_INET, (void *)&clnt_addr.sin_addr.s_addr,ip,sizeof(clnt_addr)))==NULL)//将IP转化为点分十进制形式
	{
		perror("ip error");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("++++++客户端++++++  ip=%s   port=%d\n",ip,ntohs(clnt_addr.sin_port));
	}

}

void* client_fun(void *arg)
{
	char buffer[BUF_SIZE]={0};//定义缓冲区
	int newfd=*((int*)arg);
	while(1)
	{
		int recv_ret=recv(newfd,buffer,sizeof(buffer),0);
		//从客户端接收信息
		if(recv_ret<0)
		{
			perror("recieve from client");
			exit(EXIT_FAILURE);
		}
		else if(recv_ret>0)
		{
			perror("recieve from client");
			printf("从客户端接收到的信息:%s",buffer);
		}
		else//1.接收的字符数为0  2.对方关闭了连接
		{
			perror("recieve from client =0 ");
			printf(" stream socket peer has performed an orderly shutdown\n");
		}
		if(0 == strncasecmp(buffer,QUIT,strlen(QUIT))){
			puts("++++++你已经退出+++++++");
			shutdown(newfd,SHUT_RDWR);
			break;
		}
	}
	close(newfd);
	pthread_exit(0);
}
int main()
{
	//服务器端::::::::::::::::::::::::::创建套接字
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

	//将套接字和IP,端口号绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));//每个字节都用0填充
	serv_addr.sin_family=AF_INET;//使用ipv4地址
	serv_addr.sin_addr.s_addr=htons(INADDR_ANY);//设置服务器端IP   为什么这样设置???
	serv_addr.sin_port=htons(PORT);//端口号

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

	//服务端 进入监听状态，等待客户端用户发起请求   TCP
	if(listen(serv_sock,10)<0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("listen");
	}

	//与客户端进行连接
	struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
	socklen_t clnt_addr_size=sizeof(clnt_addr);//客户端地址的长度
	//多线程并发服务器
	while(1)
	{
		int newsock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);//产生一个新生成的套接字 接受客户端的请求时候激活accept函数 
		if(newsock==-1)//接收失败
		{
			perror("accept client");
			exit(EXIT_FAILURE);
		}
		else//接收成功
		{
			perror("accept client");
			printf("clnt_sock=%d\n",newsock);
		}

		//显示客户端信息
		client_info(clnt_addr);
		//创建线程
		pthread_t tid;
		pthread_create(&tid,NULL,client_fun,(void*)&newsock);
		pthread_detach(pthread_self());//这将该子线程的状态设置为detached,则该线程运行结束后会自动释放所有资源  非阻塞
	}
	close(serv_sock);

	return 0;
}
