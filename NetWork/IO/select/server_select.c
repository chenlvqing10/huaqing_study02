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

#define  QUIT     "quit"
#define  SERVER_PORT    4444
#define  SERVER_IP  "192.168.75.156"
#define  CLIENT_IP  "192.168.75.156"
#define  CLIENT_PORT  6667                       


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
	signal(SIGPIPE, pipesig_handler);//添加信号处理函数
	signal(SIGSEGV,get_sigsegv);
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
	serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);//设置服务器端IP
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

	//定义客户端地址的结构体
	struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
	socklen_t clnt_addr_size=sizeof(clnt_addr);//客户端地址的长度

	//创建集合，初始化集合
	fd_set rfds;//文件描述符集合  读写及错误事件位
	fd_set temp;
	int     maxfd,setfd,input_t;//最大的文件描述符
	struct timeval tv={5,0};//timeout时间
	int retval,ret;
	int newsock;//accept创建的文件描述符
	maxfd= serv_sock;//将服务端的套接字赋值给maxfd  初始化  maxfd=3
	FD_ZERO(&rfds);//清空fd集合 设置成0

	FD_SET(0, &rfds);//向fd集合中添加文件描述符(stdin)  rfds[0]=0  rfds[1]=3
	FD_SET(serv_sock,&rfds);//将套接字加入到fd集合中

	//I0多路复用
	while(1)
	{
		signal(SIGPIPE, pipesig_handler);// 捕获SIGPIPE信号  添加信号处理函数
		signal(SIGSEGV,get_sigsegv);
		temp=rfds;//文件描述符集合数组赋值给temp    temp保存了所有新连接的文件描述符
		tv.tv_sec=5;
		tv.tv_usec=0;

		retval = select(maxfd+1, &temp, NULL, NULL, &tv);
		//printf("retval=%d  maxfd=%d \n",retval,maxfd);
		if (retval == -1)//select error
		{
			perror("select()");
			exit(EXIT_FAILURE);
		}
		else if(retval==0)//timeout
		{
			//printf("timeout within 5 seconds.\n");
			//sleep(10);
			continue;
		}
		else if (retval>0)//data is available 有事件响应
		{

			printf("客户端号码 发送内容\n");
			printf("retval=%d  maxfd=%d \n",retval,maxfd);

			//轮训判断那个文件描述符产生事件
			for(int i=0;i<maxfd+1;i++)//rfds=0,3,4,5,6,7
			{
				if(FD_ISSET(i,&temp))//事件响应
				{
					printf("%d is true and maxfd=%d\n",i,maxfd);

					if(i==0)//是键盘输入产生事件  服务器发数据给客户端
					{
						bzero(buffer,BUFSIZ);
						input_t = scanf("%d %s",&setfd,buffer);
						while(getchar()!='\n');
						if(!strncasecmp(buffer,QUIT,strlen(QUIT)))
						{
							printf("***服务端退出了哈哈哈哈***\n");
							//向所有客户端发送退出的消息
							//关闭所有客户端的套接字 清空文件描述符集合
							for(int i=4;i<=maxfd;i++)
							{
								if(FD_ISSET(i,&rfds))
								{
									if(write(i,buffer,strlen(buffer))<0)//将缓冲区的数据写入套接字发给服务端
									{
										perror("write");
										exit(1);
									}
									else
									{
										perror("write");
										printf("写入套接字的内容:%s\n",buffer);
									}
									close(i);//关闭新的套接字
									FD_CLR(i,&rfds);//清空文件描述符集合
									printf("客户端[%d]清空了\n",i);
								}
							}
							maxfd=serv_sock;
							break;
						}
						if(input_t !=2){
							puts("输入错误！请按格式输入：fd+空格+消息内容");
							continue;
						}
						if(!FD_ISSET(setfd,&rfds)){
							puts("输入fd号错误，没有这个链接！");
							continue;
						}
						
						if(setfd<3)
						{
							printf("非客户端套接字\n");
							continue;
						}
						//发出信息

						ret = send(setfd,buffer,strlen(buffer),0);
						while((ret<0)&&(EINTR==errno))//读取键盘输入的数据到缓冲区
						{
							perror("read");
							continue;
						}
						if(ret==0)
						{
							perror("read 0");
							printf("read 0 character\n");
							break;
						}
						else if(ret>0)//读取成功
						{
							perror("read");
							printf("向客户端[%d]发送了数据:%s\n",setfd,buffer);
						}
					}
					else if(i==serv_sock)////如果是socket产生的套接字文件描述符  那就说明是要建立新的客户端连接  存疑   如果第二个客户端连接呢？
					{
						newsock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);//产生一个新生成的套接字 接受客户端的请求时候激活accept函数 
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

						//将产生的新套接字加入文件描述符的集合之中
						FD_SET(newsock,&rfds);
						//更新maxfd（判断那个最大的文件描述符是那个
						maxfd = newsock > maxfd ? newsock : maxfd;
						printf("maxfd=%d\n",maxfd);//打印最大的文件描述符
					}
					else if(i>serv_sock)//剩下的情况就是所有的客户端对应的newfd   处理已经连接好的客户端请求和送来的数据
					{
						//i就是产生事件的客户端对应的fd  从客户端接收消息
						printf("i=%d\n",i);
						bzero(buffer,BUFSIZ);
						while(((ret=read(i,buffer,BUFSIZ-1))<0)&&(EINTR==errno))//读取新的fd的数据到缓冲区
						{
							perror("read");
							continue;
						}

						if(ret>0)//读取成功
						{
							perror("read");
							printf("服务器端已收到客户端[%d]的数据：%s \n",i,buffer);
						}
						else if(ret==0)//客户端关闭  能否在客户端关闭之前得到quit数据？？？？？？？  客户端关闭或错误  不能分离么？
						{
							perror("read 0");
							printf("客户端[%d]关闭时候已收到：%s \n",i,buffer);
							printf("***客户端[%d]退出***\n",i);
							FD_CLR(i,&rfds);//清空文件描述符集合
							close(i);//关闭客户端  新的套接字
							maxfd = ((maxfd==i) ? (--maxfd) : maxfd);//如果关闭的是最大的文件描述符则将文件描述符-1
						}
					}
				}//den ISSET
			}//end for
			printf("end for\n");
			if(maxfd<=serv_sock)//服务端退出的时候退出循环
			{
				printf("客户端已经全部关闭，可以退出系统\n");
				break;
			}
		}//end retval>0
	}//end while
	printf("退出while循环\n");
	close(serv_sock);
	return 0;
}
