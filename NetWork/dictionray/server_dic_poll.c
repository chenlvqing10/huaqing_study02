#include "database.h"

static struct sockaddr_in serv_addr;//服务器端地址　保存了服务器端的IP地址和端口号
static struct sockaddr_in clnt_addr;//客户端地址  保存了客户端的IP地址和端口号

/*利用poll机制实现多路复用服务器*/
int main()
{
	char buffer[BUFSIZ]={0};//定义缓冲区
	socklen_t clnt_addr_size=sizeof(serv_addr);
	int serv_sock=tcp4bind(TYPE_SERVER,-1,serv_addr,clnt_addr); //绑定服务器　监听状态

	//创建集合，初始化集合
	int newsock;
	struct pollfd  fds_array[1024];//存储感兴趣的描述符以及他们待发生的事件
	for(int i = 0;i < ARRAY_SIZE(fds_array);i++)   //遍历结构体数组，将每个结构体的成员 fd 设置为  -1，即这个位置时空位
	{
		fds_array[i].fd = -1;
	}
	userinfo_t     *userinfo;//定义结用户构体指针
	historyinfo_t  *historyinfo;//定义历史信息结构体指针
	userinfo=(userinfo_t*)malloc(sizeof(userinfo_t));//动态分配内存                            
	historyinfo=(historyinfo_t*)malloc(sizeof(historyinfo_t));

	//将要用到的文件描述符加入到结构体数组中
	fds_array[0].fd=0;
	fds_array[0].events=POLLIN;

	fds_array[1].fd=serv_sock;
	fds_array[1].events=POLLIN;

	int maxfd=serv_sock;//当前的文件描述符个数
	int retval=-1;
	int ret=-1;
	//int setfd,input_t;

	//I0多路复用
	while(1)
	{
		signal(SIGPIPE, pipesig_handler);// 捕获SIGPIPE信号  添加信号处理函数
		signal(SIGSEGV,get_sigsegv);

		retval = poll(fds_array,maxfd-1,1000);//调用poll函数

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
		{
			if(fds_array[0].revents & POLLIN)//用于退出服务器
			{
				bzero(buffer,BUFSIZ);
				scanf("%s",buffer);
				printf("向客户端发送的数据是:%s\n",buffer);
				if(!strncasecmp(buffer,QUIT,strlen(QUIT)))
				{
					printf("***服务端退出了***\n");
					for(int i=2;i<maxfd;i++)
					{
						int ret_w=write(fds_array[i].fd,buffer,strlen(buffer));//向客户端发送quit
						if(ret_w<0)//将缓冲区的数据写入套接字发给客户端                                
						{
							perror("write");
							exit(EXIT_FAILURE);
						}
						else
						{
							//perror("write");
							printf("写入客户端的内容:%s\n",buffer);
						}

						fds_array[i].fd = -1;//客户端关联文件描述法集合清空
						close(fds_array[i].fd);//关闭所有新建立的套接字 
					}
					break;
				}
			}
			if(fds_array[1].revents & POLLIN)//有新的客户端建立连接
			{
				newsock=acceptclient(serv_sock,clnt_addr,clnt_addr_size);//产生一个新生成的套接字 接受客户端的请求时候激活accept函数 并打印客户端IP和端口号

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
				//printf("退出激活键盘输入的for循环\n");
			}
			else//处理客户端发送过来的数据
			{
				bzero(buffer,BUFSIZ);//缓冲区清空

				/*单词查询函数*/
				char buffer_explain[200]={0};//从文件中读取单词的解释放在该缓冲区
				char *ptr_explain=NULL;
				const char *pathname="./dict.txt";

				/*用户注册登录操作变量*/
				char c;
				char name[100]={0};//用户名
				char password[100]={0};//密码 9位密码
				char current_pwd[100]={0};//注册时候的确认密码
				char *ptr_name=name;
				char *ptr_pwd=password;
				char *ptr_currentpwd=current_pwd;

				/*数据库变量*/
				sqlite3 * db = NULL;//数据库名
				char* errmsg=NULL;
				const char* sql_userinfo="CREATE TABLE  if not exists userinfo(username varchar(20) primary key,password varchar(10));";
				const char* sql_historyinfo="CREATE TABLE  if not exists historyinfo( historyno int primary key,timeinfo varchar(50),opertype int,oper varchar(200));";
				char  sql[80]={0};
				int   loginstatus=-1;//用户登录状态
				bool  isregist=false;
				char  time_msg[30]={0};	


				for(int i = 2;i < ARRAY_SIZE(fds_array);i++)   //遍历整个数组,查看是哪个客户端发送了数据
				{
					//printf("fsd_arr[%d].fd=%d   fds_array[%d].revents=%d\n",i,fds_array[i].fd,i,fds_array[i].revents);
					if(fds_array[i].fd < 0 || !(fds_array[i].revents & POLLIN)) //两个条件  如果该结构体数据的文件描述符为空  或者没有响应事件  接着判断下一个事件
						continue;

					if((ret = read(fds_array[i].fd,buffer,BUFSIZ-1)) <= 0)
					{
						perror("read");
						printf("Read client[%d] failure\n",fds_array[i].fd);
						close(fds_array[i].fd);
						fds_array[i].fd = -1;
						maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
						break;
					}
					else//读取成功 按照输入的数字进行不同的操作
					{
						//perror("read");
						printf("Read %d bytes data from client[%d]:%s\n",ret,fds_array[i].fd,buffer);

						strncpy(&c,buffer,1);
						//	printf("c=%c\n",c);

						if(c=='1')//服务器端处理用户注册
						{
							char *src=buffer;
							int count=0;
							bzero(name,sizeof(name));
							bzero(password,sizeof(password));
							bzero(current_pwd,sizeof(current_pwd));

							while(*src!='\0')
							{
								if(*src==' ')
								{
									count++;
									src++;
								}
								else
								{
									if(count==1)
									{
										*ptr_name=*src;
										//printf("ptr_name=%s name=%s\n,",ptr_name,name);
										ptr_name++;
									}
									else if(count==2)
									{
										*ptr_pwd=*src;
										//printf("ptr_pwd=%s password=%s\n,",ptr_pwd,password);
										ptr_pwd++;
									}
									else if(count==3)
									{
										//printf("ptr_currentpwd=%s current_pwd=%s\n,",ptr_currentpwd,current_pwd);
										*ptr_currentpwd=*src;
										//printf("ptr_currentpwd=%s current_pwd=%s\n,",ptr_currentpwd,current_pwd);
										ptr_currentpwd++;
									}

									src++;
								}
							}

							ptr_name=NULL;
							ptr_pwd=NULL;
							ptr_currentpwd=NULL;

							//printf("name=%s  pwd=%s  currentpwd=%s\n",name,password,current_pwd);
							strcpy(userinfo->username,name);
							strcpy(userinfo->password,password);
							strcpy(userinfo->current_pwd,current_pwd);

							//执行数据库操作
							//简单判断用户名是否合法　　简单判断密码是否合法　　判断密码和确认密码是否一致
							Create_tables(db,sql_userinfo,errmsg);//创建用户表
							Create_tables(db,sql_historyinfo,errmsg);//创建历史记录表
							isregist=User_Regist(db,sql,userinfo,errmsg);//用户注册是否成功
							bzero(buffer,BUFSIZ);
							if(isregist==true)//注册成功　保存历史交易记录
							{
								sprintf(buffer,"11");
								char  *ptr_tmsg=get_timemsg(time_msg);
								strcpy(time_msg,ptr_tmsg);
								//	printf("time_msg=%s\n",time_msg);
								set_history(db,sql,userinfo,historyinfo,errmsg,'1',1,time_msg,NULL,NULL);//表示注册成功的历史记录

							}
							else//注册失败　　保存历史交易记录
							{
								sprintf(buffer,"10");
								char  *ptr_tmsg=get_timemsg(time_msg);
								strcpy(time_msg,ptr_tmsg);
								//printf("time_msg=%s\n",time_msg);
								set_history(db,sql,userinfo,historyinfo,errmsg,'1',0,time_msg,NULL,NULL);//表示注册不成功的历史记录
							}

							if((ret = write(fds_array[i].fd,buffer,strlen(buffer))) <= 0)//将单词的解释发给客户端
							{
								perror("write");
								printf("Write to client[%d] failure:%s\n",fds_array[i].fd,strerror(errno));
								close(fds_array[i].fd);
								fds_array[i].fd = -1;
								maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
								Close_Database(db);
								break;
							}
							else
							{
								//perror("Write");
								printf("write data is %s\n",buffer);
								Close_Database(db);
								break;
							}
						}//end 1
						else if(c=='2')//服务器端处理用户登录
						{
							char *src=buffer;
							int count=0;
							bzero(name,sizeof(name));
							bzero(password,sizeof(password));

							while(*src!='\0')
							{
								if(*src==' ')
								{
									count++;
									src++;
								}
								else
								{
									if(count==1)
									{
										*ptr_name=*src;
										//printf("ptr_name=%s name=%s\n,",ptr_name,name);
										ptr_name++;
									}
									else if(count==2)
									{
										*ptr_pwd=*src;
										//printf("ptr_pwd=%s password=%s\n,",ptr_pwd,password);
										ptr_pwd++;
									}
									src++;
								}
							}
							ptr_name=NULL;
							ptr_pwd=NULL;

							//printf("name=%s  pwd=%s \n",name,password);
							strcpy(userinfo->username,name);
							strcpy(userinfo->password,password);

							//执行数据库操作
							//查找输入的用户名和密码是否与数据库中的用户名和密码匹配
							Create_tables(db,sql_userinfo,errmsg);//创建用户表
							Create_tables(db,sql_historyinfo,errmsg);//创建历史记录表
							loginstatus=User_login(db,sql,userinfo,errmsg);//用户注册是否成功
							bzero(buffer,BUFSIZ);
							if(loginstatus==0)//用户名不存在  处理历史交易记录
							{
								sprintf(buffer,"20");
								char  *ptr_tmsg=get_timemsg(time_msg);
								strcpy(time_msg,ptr_tmsg);
								//printf("time_msg=%s\n",time_msg);
								set_history(db,sql,userinfo,historyinfo,errmsg,'2',0,time_msg,NULL,NULL);//表示用户登录的时候用户名不存在
							}
							else if(loginstatus==1)//密码不正确
							{
								sprintf(buffer,"21");
								char  *ptr_tmsg=get_timemsg(time_msg);
								strcpy(time_msg,ptr_tmsg);
								//printf("time_msg=%s\n",time_msg);
								set_history(db,sql,userinfo,historyinfo,errmsg,'2',1,time_msg,NULL,NULL);//表示用户登录的时候密码不正确
							}
							else
							{
								sprintf(buffer,"22");
								char  *ptr_tmsg=get_timemsg(time_msg);
								strcpy(time_msg,ptr_tmsg);
								//printf("time_msg=%s\n",time_msg);
								set_history(db,sql,userinfo,historyinfo,errmsg,'2',2,time_msg,NULL,NULL);//表用户登录成功
							}

							if((ret = write(fds_array[i].fd,buffer,strlen(buffer))) <= 0)//将单词的解释发给客户端
							{
								perror("write");
								printf("Write to client[%d] failure:%s\n",fds_array[i].fd,strerror(errno));
								close(fds_array[i].fd);
								fds_array[i].fd = -1;
								maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
								Close_Database(db);
								break;
							}
							else
							{
								//perror("Write");
								printf("write data is %s\n",buffer);
								Close_Database(db);
								break;
							}
							Close_Database(db);
						}
						else if(c=='3')//服务器端处理单词查询
						{
							int len=strlen(buffer);
							char word[100]={0};
							char *des=buffer;
							des=des+2;
							strncpy(des,des,len-2);
							strcpy(buffer,des);
							strcpy(word,buffer);
							//printf("经过变化后的buffer=%s\n",buffer);
							//执行文件操作　进行单词查询
							ptr_explain=getexplain(pathname,buffer);
							strcpy(buffer_explain,ptr_explain);


							if((ret = write(fds_array[i].fd,buffer_explain,sizeof(buffer_explain))) <= 0)//将单词的解释发给客户端
							{
								perror("write");
								printf("Write to client[%d] failure:%s\n",fds_array[i].fd,strerror(errno));
								close(fds_array[i].fd);
								fds_array[i].fd = -1;
								maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
								Close_Database(db);
								break;
							}
							else//处理历史交易记录
							{
								//perror("Write");
								printf("write data is %s\n",buffer_explain);    
								char  *ptr_tmsg=get_timemsg(time_msg);
								strcpy(time_msg,ptr_tmsg);
								//printf("time_msg=%s\n",time_msg);
								set_history(db,sql,userinfo,historyinfo,errmsg,'3',0,time_msg,word,buffer_explain);//表用单词查询记录
								Close_Database(db);
								break;
							}
						}
						else if(c=='4')//查询历史记录
						{
							bzero(buffer,BUFSIZ-1);
							sprintf(buffer,"4");

							if((ret = write(fds_array[i].fd,buffer,sizeof(buffer_explain))) <= 0)//将单词的解释发给客户端
							{
								perror("write");
								printf("Write to client[%d] failure:%s\n",fds_array[i].fd,strerror(errno));
								close(fds_array[i].fd);
								fds_array[i].fd = -1;
								maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
								break;
							}
							else//处理历史交易记录
							{
								//perror("Write");
								printf("write data is %s\n",buffer);   
							}
						}
						else if(c=='0')//退出系统
						{
							printf("客户端[%d] exit\n",fds_array[i].fd);
							close(fds_array[i].fd);
							fds_array[i].fd = -1;
							maxfd = ( fds_array[i].fd == maxfd) ? (--maxfd) : maxfd;//
                      break;

						}

					}//end ret>0 读取成功 打开文件 进行单词的查找

				}//end for　事件队列
			}//end 客户端的请求
		}//end retval>0　有事件响应
		printf("继续执行下一次while循环\n");
	}//end while
	printf("while循环退出\n");
	close(newsock);
	close(serv_sock);
	free(userinfo);
	free(historyinfo);
	return 0;
}
