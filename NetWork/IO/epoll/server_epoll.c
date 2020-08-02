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
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>


#define  QUIT     "quit"
#define  SERVER_PORT     1259
#define  SERVER_IP  "192.168.75.156"
#define  CLIENT_IP  "192.168.75.156"
#define  CLIENT_PORT  6667                       
#define  SIZE_EVENTS  1024

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
	char buffer[BUFSIZ]={0};//定义缓冲区
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

	//设置服务器的IP,端口号
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));//每个字节都用0填充
	serv_addr.sin_family=AF_INET;//使用ipv4地址
	serv_addr.sin_addr.s_addr=htons(INADDR_ANY);//设置服务器端IP   为什么这样设置???
	serv_addr.sin_port=htons(SERVER_PORT);//端口号

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

	int reval,newsock,ret;
	//创建红黑树
	int epfd=epoll_create(1);//红黑树的根节点
	//将serv_sock上树
	struct epoll_event ev,evs[SIZE_EVENTS];
	ev.events=EPOLLIN;//读事件/边沿触发
	ev.data.fd=serv_sock;
	epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&ev);
	//循环监听树
	while(1)
	{
		reval=epoll_wait(epfd,evs,SIZE_EVENTS,-1);//监听树

		if(reval<0)
		{
			perror("epoll wait");
			continue;
		}
		else if(reval==0)//timeout
		{
			continue;
		}
		else//reval>0
		{
			for(int i=0;i<reval;i++)
			{
				int fd=evs[i].data.fd;

				if((fd==serv_sock)&&(evs[i].events&EPOLLIN))//如果是serv_sock变化 并且是读事件变化  表示有新的客户端进行连接
				{
					//定义客户端地址的结构体
					struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
					socklen_t clnt_addr_size=sizeof(clnt_addr);//客户端地址的长度
					newsock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);//产生一个新生成的套接字 接受客户端的请求时候激活accept函数 
					printf("newsock=%d\n",newsock); 
					if(newsock==-1)//接收失败
					{
						perror("accept client");
						close(newsock);
						exit(EXIT_FAILURE);
					}
					else//接收成功
					{
						perror("accept client");
						printf("newsock=%d\n",newsock);
					}

					//打印客户端信息
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
					
					//将newsock设置成非阻塞
					int flags;
					if((flags=fcntl(newsock,F_GETFL,0))<0)
					{
						perror("flags");
					}
					else
					{
						flags |= O_NONBLOCK;
						if(fcntl(newsock,F_SETFL,flags)<0)
						{
							perror("perror");
						}
					}

					//将新的客户端(新的套接字文件描述符)上树
						ev.data.fd=newsock;
					    ev.events=EPOLLIN | EPOLLET;//读事件
						epoll_ctl(epfd,EPOLL_CTL_ADD,newsock,&ev);
				}
				else if(evs[i].events&EPOLLIN)//如果是newsock变化 并且是读事件  表示客户端有数据发过来
				{
				  ret = read(ev.data.fd,buffer,sizeof(buffer));
                  
				  if(ret<0)
				  {
					if(errno==EAGAIN)//缓冲区无数据
					{
						break;
					}
					else//出错
					{
						perror("read error");
                      //关闭客户端套接字 节点下树
                      close(ev.data.fd);
                      epoll_ctl(epfd,EPOLL_CTL_DEL,ev.data.fd,&evs[i]);
					}
				  }
				  if(ret==0)
                  {
                      printf("client[%d] colse\n",ev.data.fd);
                      //关闭客户端套接字 节点下树
					  close(ev.data.fd);
                      epoll_ctl(epfd,EPOLL_CTL_DEL,ev.data.fd,&evs[i]);
                      break;
                  }
                  
				  if(ret>0)
                  {
                      perror("read");
                      printf("Read %d bytes data from client[%d]:%s\n",ret,ev.data.fd,buffer);
                  }
                  if(!strncasecmp(buffer,QUIT,strlen(QUIT)))
                  {   
                      printf("client[%d] exit\n",ev.data.fd);
                      //关闭客户端套接字 节点下树
                       close(ev.data.fd);
                       epoll_ctl(epfd,EPOLL_CTL_DEL,ev.data.fd,&evs[i]);
                      break;
                  }
				}

			}
		}

	}

	close(serv_sock);

	return 0;
}
