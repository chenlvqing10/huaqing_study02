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
#include <poll.h>
#include <ctype.h>

#define  QUIT     "quit"
#define  SERVER_PORT     1259
#define  SERVER_IP  "192.168.75.156"
#define  CLIENT_IP  "192.168.75.156"
#define  CLIENT_PORT  6667                       

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

/*利用poll机制实现多路复用服务器*/
int main()
{
	signal(SIGPIPE, pipesig_handler);//添加信号处理函数
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

	//定义客户端地址的结构体
	struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
	socklen_t clnt_addr_size=sizeof(clnt_addr);//客户端地址的长度

	//创建集合，初始化集合
	int newsock;
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
	int maxfd=serv_sock;//当前的文件描述符个数
	int retval=-1;
	int ret=-1;
	int setfd,input_t;

	//I0多路复用
	while(1)
	{
		//printf("向客户端发送数据，请按任意键继续\n");
		//printf("客户端号   内容\n");
		signal(SIGPIPE, pipesig_handler);// 捕获SIGPIPE信号  添加信号处理函数
		signal(SIGSEGV,get_sigsegv);

		retval = poll(fds_array,maxfd-1,0);//调用poll函数

		if (retval == -1)//poll error
		{
			perror("poll");
			exit(EXIT_FAILURE);
		}
		else if(retval==0)//timeout
		{
			//printf("timeout within 5 seconds.\n");
			//sleep(10);
			continue;
		}
		else if (retval>0)//有事件响应
		{   printf("111111111\n");
			printf("retval=%d  maxfd=%d \n",retval,maxfd);

			if(fds_array[0].revents & POLLIN)//真实事件是键盘输入产生事件  服务器发数据给客户端
			{
				bzero(buffer,BUFSIZ);
				input_t = scanf("%d %s",&setfd,buffer);
				printf("向客户端[%d]发送的数据是:%s\n",setfd,buffer);
				if(!strncasecmp(buffer,QUIT,strlen(QUIT)))
				{
					printf("***服务端退出了哈哈哈哈***\n");
					for(int i=2;i<maxfd;i++)
					{
						fds_array[i].fd = -1;//客户端关联文件描述法集合清空
						close(fds_array[i].fd);//关闭所有新建立的套接字 
					}
					break;
				}
				while(getchar()!='\n');
				if(input_t !=2)
				{
					puts("输入错误！请按格式输入：客户端号+空格+消息内容");
					continue;
				}
				if((fds_array[setfd-2].fd==-1)||(setfd<=2))
				{
					puts("输入fd号错误，没有这个链接！");
					continue;
				}	

				int ret_w=write(fds_array[setfd-2].fd,buffer,strlen(buffer));// 需要连接客户端  连接客户端的时候 产生新的文件描述符 应该使用maxfd

				if(ret_w<0)//将缓冲区的数据写入套接字发给客户端                                
				{
					perror("write");
					exit(EXIT_FAILURE);
				}
				else
				{
					perror("write");
					printf("写入客户端[%d]的内容:%s\n",setfd,buffer);
				}

			}
			else if(fds_array[1].revents & POLLIN)//有新的客户端建立连接
			{
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

				for(int i = 2;i < ARRAY_SIZE(fds_array);i++)   //找出空房间，让客人入住  0,1已经有人了   同样的如果客户端关闭了，也要整理房间，即让房间变空
				{
					if(fds_array[i].fd < 0)
					{
						maxfd = newsock > maxfd ? newsock : maxfd;//判断新的客户端的fd是否是最大的
						fds_array[i].fd = newsock;//将建立连接的客户端新的文件描述符加入到结构体数组中
						fds_array[i].events = POLLIN;   //设置等待事件
						printf("Put new client[%d] into fds_array[%d].fd\n",newsock,i);
						break;
					}
				}
				printf("退出激活键盘输入的for循环\n");
			}
			else//处理客户端发送过来的数据
			{
				bzero(buffer,BUFSIZ);

				for(int i = 2;i < ARRAY_SIZE(fds_array);i++)   //遍历整个数组,查看是哪个客户端发送了数据
				{
					printf("fsd_arr[%d].fd=%d   fds_array[%d].revents=%d\n",i,fds_array[i].fd,i,fds_array[i].revents);
					if(fds_array[i].fd < 0 || !(fds_array[i].revents & POLLIN)) //两个条件  如果该结构体数据的文件描述符为空  或者没有响应事件  接着判断下一个事件
						continue;

					if((ret = read(fds_array[i].fd,buffer,sizeof(buffer))) <= 0)
					{
						perror("read");
						printf("Read client[%d] failure\n",fds_array[i].fd);
						close(fds_array[i].fd);
						fds_array[i].fd = -1;
						maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
						break;
					}
					else
					{
						perror("read");
						printf("Read %d bytes data from client[%d]:%s\n",ret,fds_array[i].fd,buffer);
					}
					if(!strncasecmp(buffer,QUIT,strlen(QUIT)))
					{   
						printf("client[%d] exit\n",fds_array[i].fd);
						close(fds_array[i].fd);
						fds_array[i].fd = -1;
						maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
						break;
					}

					for(int j = 0;j < ret;j++)
					{
						buffer[j] = toupper(buffer[j]);//将小字母转化位大写字母
					}

					if((ret = write(fds_array[i].fd,buffer,sizeof(buffer))) <= 0)//将缓冲区的数据写入该文件描述符
					{
						perror("write");
						printf("Write to client[%d] failure:%s\n",fds_array[i].fd,strerror(errno));
						close(fds_array[i].fd);
						fds_array[i].fd = -1;
						maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
						break;
					}
					else
					{
						perror("Write");
						printf("write data is %s\n",buffer);
						break;
					}
				}

			}
		}//end retval>0
		printf("继续执行下一次while循环\n");
	}//end while
	printf("while循环退出\n");
	close(newsock);
	close(serv_sock);

	return 0;
}
