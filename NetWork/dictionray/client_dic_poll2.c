#include "database.h"                                                                      
static struct sockaddr_in serv_addr;//服务器端地址　保存了服务器端的IP地址和端口号
static struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号
static int flag=-1;//标志位　控制流程走向
int main()
{
	int serv_sock=tcp4bind(TYPE_CLIENT,CLIENT_PORT2,serv_addr,clnt_addr);
	char buffer[BUFSIZ]={0};//客户端缓冲区
	char word[WORD_SIZE]={0};//单词

	//创建集合，初始化集合
	int maxfd=-1;//最大的文件描述符
	int retval=-1,ret=-1;
	struct pollfd  fds_array[1024];//存储感兴趣的描述符以及他们待发生的事件
	int count=0;

	userinfo_t     *userinfo;//定义结用户构体指针
	historyinfo_t  *historyinfo;//定义历史信息结构体指针
	userinfo=(userinfo_t*)malloc(sizeof(userinfo_t));//动态分配内存   
	historyinfo=(historyinfo_t*)malloc(sizeof(historyinfo_t));

	for(int i = 0;i < ARRAY_SIZE(fds_array);i++)   //遍历结构体数组，将每个结构体的成员 fd 设置为  -1，即这个位置时空位
	{
		fds_array[i].fd = -1;
	}
	//将要用到的文件描述符加入到结构体数组中
	fds_array[0].fd=0;
	fds_array[0].events=POLLIN;

	fds_array[1].fd=serv_sock;
	fds_array[1].events=POLLIN;

	while(1)
	{
		signal(SIGPIPE, pipesig_handler);//添加信号处理函数
		signal(SIGSEGV,get_sigsegv);
		maxfd=serv_sock;
		retval = poll(fds_array,2,1000);

		if (retval == -1)//poll error
		{
			perror("poll");
			exit(EXIT_FAILURE);
		}
		else if(retval==0)//timeout
		{
			if(count<=0)
				printf("请在键盘上输入任意字符激活客户端操作界面.\n");
			count++;
			//	sleep(10);
			continue;
		}
		else if (retval>0)//事件响应
		{
			if(flag==1)
			{
				//user_operator_menu();
				//flag=2;
			}
			else if(flag==-1)
			{
				user_login_regist_menu();//客户端操作界面  没有事件响应 timeout=5s
				flag=0;
			}
		//	printf("flag=%d\n",flag);


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
				bzero(buffer,BUFSIZ);
				char c;
				char name[100]={0};//用户名
				char password[100]={0};//密码 10位密码
				char current_pwd[100]={10};//注册时候的确认密码
				char* ptr_buf=NULL;
				bzero(name,sizeof(name));
				bzero(password,sizeof(password));
				bzero(current_pwd,sizeof(current_pwd));

				while((c=getchar() )!= '5')
				{
					switch(c)
					{
						case '1':
							if(flag==0)
							{
								bzero(name,sizeof(name));
								bzero(password,sizeof(password));
								bzero(current_pwd,sizeof(current_pwd));

								printf("用户注册操作\n");
								ptr_buf=get_buffer(name,password,current_pwd,c);
								strcpy(buffer,ptr_buf);
							//	printf("buffer=%s\n",buffer);

								//客户端将数据发送给客户端
								Write(serv_sock,buffer,strlen(buffer));//写入套接字
							}
							break;
						case '2':
							if(flag==0)
							{
								ptr_buf=NULL;
								bzero(name,sizeof(name));
								bzero(password,sizeof(password));
								bzero(current_pwd,sizeof(current_pwd));

								printf("用户登录操作\n");
								ptr_buf=get_buffer(name,password,NULL,c);
								strcpy(buffer,ptr_buf);
								//printf("buffer=%s\n",buffer);

								//客户端将数据发送给客户端
								Write(serv_sock,buffer,strlen(buffer));//写入套接字
							}
							break;
						case '3':
							//printf("flag=%d\n",flag);
							if(flag==1)
							{
								printf("单词查询操作\n");
								printf("请输入要查询的单词:");
								scanf("%s",word);
								strcpy(buffer,word);
								//printf("buffer=%s\n",buffer);
								sprintf(buffer,"%c %s",c,word);
								//printf("buffer=%s\n",buffer);

								//客户端将数据发送给客户端
								Write(serv_sock,buffer,strlen(buffer));//写入套接字
							}
							break;
						case '4':
							if(flag==1)
							{
								printf("历史记录查询操作\n");
								sprintf(buffer,"4");
								//printf("buffer=%s\n",buffer);
								//客户端将数据发送给客户端
								Write(serv_sock,buffer,strlen(buffer));//写入套接字
							}
							break;
						case '0':
							printf("退出系统\n");
							sprintf(buffer,"0");
							//客户端将数据发送给客户端
							Write(serv_sock,buffer,strlen(buffer));//写入套接字
							exit(EXIT_SUCCESS);
							break;
						default:
							break;
					}//end Switch

					if((c=='3')||(c=='1')||(c=='2')||(c=='4'))//处理服务器端发来的单词解释
						break;
				}//end whlle
			}
			else if(fds_array[1].revents & POLLIN)//服务端发送数据的时候接收数据
			{
				//printf("服务端发送了数据\n");
				bzero(buffer,BUFSIZ);
				ret=read(fds_array[1].fd,buffer,BUFSIZ-1);

				if((ret<0)&&(EINTR==errno))//读取键盘输入的数据到缓冲区
				{
					perror("read");
					continue;
				}
				else if(ret==0)
				{
				//	perror("read 0");
					printf("read 0 character\n");
					break;
				}
				else if(ret>0)//读取成功
				{
				//	perror("read");


					if(strcmp(buffer,"10")==0)
					{
						printf("用户注册失败,请按1键重新注册\n");
					}
					else if(strcmp(buffer,"11")==0)
					{
						printf("用户注册成功,请按2键登录\n");
					}
					else if(strcmp(buffer,"20")==0)
					{
						printf("用户不存在,请按1键注册,按2重新登录\n");
					}
					else if(strcmp(buffer,"21")==0)
					{
						printf("密码不正确,请按2重新登录\n");
					}
					else if(strcmp(buffer,"22")==0)
					{
						printf("登录成功,进入用户操作界面\n");
						user_operator_menu();
						flag=1;
					}
					else if(strcmp(buffer,"4")==0)
					{
						printf("历史记录:\n");
						sqlite3* db=NULL;
						char* sql=NULL;
						char* errmsg=NULL;
						select_historyinfo(db,sql,errmsg);
						Close_Database(db);
					}
					else
					{ 
						printf("单词查询结果:%s::%s\n",word,buffer);
					}
					if(!strncasecmp(buffer,QUIT,strlen(QUIT)))
					{
						printf("***因为服务器断开了连接，所以客户端退出***\n");
						break;
					}
				}
			}//end 服务端发送数据的时候接收数据
		}//end retcal>0 
	}//end while
	printf("退出while循环\n");
	close(serv_sock);
	free(userinfo);
	free(historyinfo);

	return 0;
}
