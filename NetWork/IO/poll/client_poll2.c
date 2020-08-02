#include <stdio.h>           
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <poll.h>
#include <ctype.h>


#define  QUIT     "quit"
#define  SERVER_PORT     1259
#define  SERVER_IP  "192.168.75.156"
#define  CLIENT_IP	"192.168.75.156"
#define  CLIENT_PORT  6669
#define   ARRAY_SIZE(x)   (sizeof(x)/sizeof(x[0])) //结构体数组的大小
void pipesig_handler(int signo)
{   
	printf("捕获到了SIGPIPE信号\n");  
	printf("客户端未连接或者套接字有问题\n");
}
void get_sigsegv(int signo)
{   
	printf("捕获到了SIGSEGV信号\n");  
	printf("客户端未连接或者套接字有问题\n");
	exit(-1);
}


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
	serv_addr.sin_port=htons(SERVER_PORT);//端口号//服务器端口号
	//设置客户端IP地址和端口号
	struct sockaddr_in clnt_addr;//客户端地址
	memset(&clnt_addr,0,sizeof(clnt_addr));//地址大小
	clnt_addr.sin_family=AF_INET;//IP地址类型:ipv4
	clnt_addr.sin_addr.s_addr=inet_addr(CLIENT_IP);//客户端地址
	clnt_addr.sin_port=htons(CLIENT_PORT);//客户端端口号

	//绑定客户端
	if(bind(serv_sock,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr))<0)//将套接字与特定的IP地址和端口号绑定起来
	{
		perror("bind server");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("bind server");
		printf("客户端就绪\n");
	}

	if(connect(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)//客户端与服务器端进行连接  TCP三次握手连接
	{
		perror("connect server");//连接失败
		exit(EXIT_FAILURE);
	}
	else
		perror("connect server");//连接成功

	char buffersend[BUFSIZ]={0};//客户端发送缓冲区

	//创建集合，初始化集合
	int maxfd=serv_sock;//最大的文件描述符
	struct pollfd  fds_array[1024];//存储感兴趣的描述符以及他们待发生的事件
	for(int i = 0;i < ARRAY_SIZE(fds_array);i++)   //遍历结构体数组，将每个结构体的成员 fd 设置为  -1，即这个位置时空位
	{
		fds_array[i].fd = -1;
	}
	//将要用到的文件描述符加入到结构体数组中
	fds_array[0].fd=0;
	fds_array[0].events=POLLIN;

	fds_array[1].fd=serv_sock;
	fds_array[1].events=POLLIN;

	int retval,ret;

	while(1)
	{
		signal(SIGPIPE, pipesig_handler);//添加信号处理函数
		signal(SIGSEGV,get_sigsegv);
		maxfd=serv_sock;
		retval = poll(fds_array,2,5000);

		if (retval == -1)//poll error
		{
			perror("poll");
			exit(EXIT_FAILURE);
		}
		else if(retval==0)//timeout
		{
			//	printf("timeout within 5 seconds.\n");
			//	sleep(10);
			continue;
		}
		else if (retval>0)//事件响应
		{
			//判断一下是否错
			if(fds_array[1].revents & POLLERR){
				puts("---------套接字出错");
				continue;
			}
			//判断是否关闭
			else if(fds_array[1].revents & POLLHUP){
				puts("---------服务器关闭");
				break;
			}
			if(fds_array[0].revents & POLLIN)//响应键盘输入事件
			{
				bzero(buffersend,BUFSIZ);
				while(((ret=read(0,buffersend,BUFSIZ-1))<0)&&(EINTR==errno))//读取键盘输入的数据到缓冲区
				{
					perror("read");
					continue;
				}

               if(ret<=0)
               {
                   perror("read");
               }
               else if(ret>0)
               {
                   perror("read");
                   printf("从键盘中读到的数据是:%s\n",buffersend);
               }   
               

				if(write(serv_sock,buffersend,strlen(buffersend))<0)//将缓冲区的数据写入套接字发给服务端
				{
					perror("write");
					exit(1);
				}
				else
				{
					perror("weite");
					printf("写入套接字的内容:%s",buffersend);
				}
				if(!strncasecmp(buffersend,QUIT,strlen(QUIT)))
				{
					printf("***客户端退出***\n");
					break;
				}
			}
			else if(fds_array[1].revents & POLLIN)//服务端发送数据的时候接收数据
			{
				printf("服务端发送了数据\n");
				bzero(buffersend,BUFSIZ);
				printf("111111111\n");
				ret=read(fds_array[1].fd,buffersend,BUFSIZ-1);

				if((ret<0)&&(EINTR==errno))//读取键盘输入的数据到缓冲区
				{
					perror("read");
					continue;
				}
				else if(ret==0)
				{
					perror("read 0");
					printf("read 0 character\n");
					break;
				}
				else if(ret>0)//读取成功
				{
					perror("read");
					printf("已收到：%s \n",buffersend);
					if(!strncasecmp(buffersend,QUIT,strlen(QUIT)))
					{
						printf("***因为服务器断开了连接，所以客户端退出***\n");
						break;
					}
				}
			}
		}

	}//end while
	printf("退出while循环\n");
	close(serv_sock);
	printf("111111111111111111111111111111\n");
	return 0;
}
