#include "wrap.h"

//捕捉SIGPIPE
void pipesig_handler(int signo)
{
	printf("捕获到了SIGPIPE信号\n");
	printf("客户端未连接或者套接字有问题\n");
}

//捕捉SIGSEGC
void get_sigsegv(int signo)
{
	printf("捕获到了SIGSEGV信号\n");
	printf("客户端未连接或者套接字有问题\n");
	exit(-1);
}

//绑定IP和PORT
int tcp4bind(int type,int clnt_port,struct sockaddr_in serv_addr,struct sockaddr_in clnt_addr)//type分离服务器端和客户端的操作
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
	if(setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int)) <0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	puts("----设置地址快速重用成功----");


	//设置服务器或者客户端的IP,端口号
	memset(&serv_addr,0,sizeof(serv_addr));//每个字节都用0填充
	memset(&clnt_addr,0,sizeof(clnt_addr));//地址大小

	if(type==TYPE_SERVER)
	{
		serv_addr.sin_family=AF_INET;//使用ipv4地址
		serv_addr.sin_addr.s_addr=htons(INADDR_ANY);//设置服务器端IP 0.0.0.0,任意ip将可以连接
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

	}
	else if(type==TYPE_CLIENT)
	{
		serv_addr.sin_family=AF_INET;//服务器端IP地址类型:ipv4
		serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);//服务器IP地址
		serv_addr.sin_port=htons(SERVER_PORT);//服务器端口号

		clnt_addr.sin_family=AF_INET;//客户端IP地址类型:ipv4
		clnt_addr.sin_addr.s_addr=inet_addr(CLIENT_IP);//客户端IP地址
		clnt_addr.sin_port=htons(clnt_port);//客户端端口号

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

	}

	return serv_sock;
}

int acceptclient(int serv_sock,struct sockaddr_in clnt_addr,socklen_t clnt_addr_size)
{
	int newsock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);//产生一个新生成的套接字 接受客户端的请求时候激活accept函数 
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

	return newsock;
}


char* getexplain(const char* pathname,char* buffer)//从文件中读取客户单输入单词的解释信息,如果单词不存在，则发送不匹配信息 
{
	//int len_word=strlen(buffer);//单词的长度
	//printf("len_word=%d\n",len_word);
	//buffer[len_word-1]='\0';//从键盘read不要输出\n   scanf的话不需要处理
	//printf("buffer=%s\n",buffer);
	char word[WORD_SIZE]={0};
	strcpy(word,buffer);
	bzero(buffer,BUFSIZ);
	int count=0;
	char buffer_w[WORD_SIZE]={0},c;//从文件中读取单词存放在该缓冲区
	char buffer_explain[EXPLAIN_SIZE]={0};//从文件中读取单词的解释放在该缓冲区
	char *ptr_w=buffer_w;
	char *ptr_explain=buffer_explain;

	int fd=open(pathname,O_RDONLY,0777);
	if(fd<0)
	{
		perror("open");
		printf("Cannot open file, press any key to exit!\n");
	}
	else
	{
		perror("open");
	}

	int ret1=read(fd,&c,1);//读取一个字符
	if(ret1<0)
	{
		perror("read word");
	}
	else if(ret1 ==0 )
	{
		perror("read 0 word");
	}

	while(ret1>0)//读到文件末尾
	{
		//perror("reada word");
		count=0;
		bzero(buffer_w,WORD_SIZE);//初始化
		bzero(buffer_explain,EXPLAIN_SIZE);
		ptr_w=buffer_w;//重新指向数组
		ptr_explain=buffer_explain;

		while(c!='\n')//按行读取数据　并将单词和解释分离
		{

			//printf("count=%d c=%c\n",count,c);
			if(c==' ')//如果是空格的话不去做
			{
				if(count==0)//第一次遇到空格的时候count++  单词读玩
					count++;
				else if(count>=2)//再次遇到单词后空格数也要赋值　count>=2 表示读取解释的空格  
				{
					//printf("将文件空格的解释赋值给指针\n");
					//printf("c=%c\n",c);
					*ptr_explain=c;
					ptr_explain++;
					//printf("buffer_explain=%s\n",buffer_explain);

				}
			}
			else if(c!=' ')
			{
				if(count==0)//当没有遇到空格的时候　将读到的单词放在缓冲区内
				{
					//printf("将文件的单词赋值给指针\n");
					//printf("c=%c\n",c);
					*ptr_w=c;
					ptr_w++;
					//printf("buffer_w=%s\n",buffer_w);
				}
				else//当再次遇到单词的时候，全部读出，直到遇到\n  count=1
				{
					count++;//count>=2 表示读取解释的空格
					//printf("将文件的解释赋值给指针\n");
					//printf("c=%c\n",c);
					*ptr_explain=c;
					ptr_explain++;
					//printf("buffer_explain=%s\n",buffer_explain);
				}

			}
			ret1=read(fd,&c,1);//接着读取
		}//end while c !=\n

		if(c=='\n')//接着读取
		{
			ret1=read(fd,&c,1);
		}
		//printf("找到了换行符\n");
		//对客户端发送的数据和从文件中读取的数据进行比较
		//printf("buffer=%s     buffer_w=%s       buffer_explain=%s\n",word,buffer_w,buffer_explain);
		if(strcmp(buffer_w,word)==0)
		{
			//	printf("客户端的数据和文件读到的数据相同\n");
			ptr_w=NULL;
			ptr_explain=NULL;
			bzero(word,WORD_SIZE);
			break;
		}
		else
		{
			//printf("客户端的数据和文件读到的数据不相同\n");
			if(ret1==0)
			{
				bzero(buffer_explain,EXPLAIN_SIZE);
				strcpy(buffer_explain,"字典中没有匹配的单词");
				ptr_w=NULL;
				ptr_explain=NULL;
				bzero(word,WORD_SIZE);
				break;
			}
			continue;
		}
	}//end ret1>0
	//printf("退出判断文件EOF循环\n");
	ptr_explain=buffer_explain;
	//printf("ptr_explain=%p   ptr_explain=%s\n",&ptr_explain,ptr_explain);
	close(fd);	
	return ptr_explain;
}

void* Read(int fd, void *ptr, size_t nbytes)//读取数据到缓冲区
{
	size_t ret=-1;

	while(((ret=read(fd,ptr,nbytes-1))<0)&&(EINTR==errno))//读取键盘输入的数据到缓冲区
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
		//printf("读入缓冲区的数据是:%s\n",(char*)ptr);
	}
	return ptr;
}

ssize_t Write(int fd, void *ptr, size_t nbytes)
{
	int ret;
	if((ret=write(fd,ptr,nbytes))<0)//将缓冲区的数据写入套接字发给服务端
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	else if(ret==0)
	{
		perror("write 0");
	}
	else
	{   
		perror("write");
		//printf("写入套接字的内容:%s\n",(char*)ptr);
	}
	return ret;
}
