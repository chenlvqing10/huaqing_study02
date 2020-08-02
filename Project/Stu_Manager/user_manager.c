#include "head.h"

static int count_username=0;		//用户名检查次数  静态全局变量
static int count_passwd=0;			//密码检查次数    静态全局变量
static char usertype;				//用户类型        静态全局变量 
//用户登录界面
void user_ui()
{
	printf("/**********************************************************************/\n");
	printf("/*****************用户登录界面*****************************************/\n");
	printf("/*****************请输入用户名和密码进行登录***************************/\n");
	printf("/**********************************************************************/\n");

}


//检查用户名是否正确
bool check_username(user_info_t *userinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	bool is_username=false;
	//输入用户名
	printf("用户名:");
	scanf("%s",userinfo->username);
	//	printf("userinfo-<username=%s\n",userinfo->username);

	//输入密码
	printf("密码：");
	scanf("%s",userinfo->passwd);
	//	printf("userinfo->passwd:%s\n",userinfo->passwd);
	//检查用户名
	sprintf(query,"select * from user_info where user_info.username=\"%s\";",userinfo->username);
	//	printf("query=%s\n",query);
	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		//		printf("mysql_real_query() sucess!!!\n");
	}

	//查询成功后将服务端内容送到客户端
	if((res=mysql_store_result(mysql)) == NULL)//获取查询结果的数据
	{
		printf("mysql_store_result():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		//		printf("mysql_store_result() success!!!\n");
	}

	if((row=mysql_fetch_row(res))!=NULL) //取得查询结果集数据	
	{
		is_username=true;
	}
	else
	{
		count_username++;
		//		printf("静态局部变量:%d\n",count_username);
	}

	//	printf("is_username=%d\n",is_username);
	init_sql(res,query,row);
	return is_username;
}

//检查用户密码是否和用户名匹配  用户类???
bool check_passwd(user_info_t *userinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	//int fields=0;//数据表中的字段数
	bool is_passwd=false;
	sprintf(query,"select user_info.username,user_info.passwd,user_info.usertype from user_info where user_info.username=\"%s\" and user_info.passwd=\"%s\";",
			userinfo->username,userinfo->passwd);
	//	printf("query=%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		//		printf("mysql_real_query() sucess!!!\n");
	}

	//查询成功后将服务端内容送到客户端
	if((res=mysql_store_result(mysql)) == NULL)//获取查询结果的数据
	{
		printf("mysql_store_result():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		//		printf("mysql_store_result() success!!!\n");
	}

	row=mysql_fetch_row(res); //取得查询结果集数据	
	if(row==NULL)//密码错误
	{
		count_passwd++;//检查次数+1
	}
	else//密码正确 得到用户类型
	{
		is_passwd=true;
		/*
		//统计字段名个数(列数)
		fields=mysql_num_fields(res);
		printf("fields:%d\n",fields);
		//打印字段的数据
		for(int i=0; i<fields; i++)
		{
		printf("%s\t",row[i]);
		}
		printf("\n");
		*/
		usertype=*row[2];
	}

	init_sql(res,query,row);
	return is_passwd;
}

void lock_exit_system()
{
	if(count_username>=3)
	{
		printf("用户名三次输出错误!!!,锁定30分钟,退出系统");
		//sleep(1800);
		exit(-1);
	}

	if(count_passwd>=3)//密码输错三次，锁定30分钟，退出系统
	{
		printf("密码输错三次，锁定30分钟，退出系统\n");
		//sleep(1800);
		exit(-1);
	}
}
bool check_username_three(user_info_t* userinfo,MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,bool is_username)
{
	printf("请重新输入用户名和密码!!!\n");//输错三次就退出系统
	//printf("count:%d\n",count_username);

	if(check_username(userinfo,mysql,res,row,query)==false)//第二次三次判断
	{
		lock_exit_system();//判断是否已经满足三次
		printf("用户名错误\n");
		printf("按2继续\n");
	}
	else//用户名正确
	{
		printf("用户名正确，调用密码检查函数");
		count_username=0;//输错次数清零
		printf("按3退出用户名检查\n");
		is_username=true;
	}
	return is_username;
}

bool check_passwd_three(user_info_t* userinfo,MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,bool is_passwd)
{
	bool is_username=false;
	is_username=check_username(userinfo,mysql,res,row,query);//再次检查用户名
	if(is_username==false)//仍然有错
	{
		count_passwd++;//当用户名出错的时候次数也要加1
		lock_exit_system();//判断是否已经满足三次
		printf("用户名或者密码错误，请重新输入!!!\n");
		printf("请按4继续\n");
	}
	else if(is_username==true)
	{
		is_passwd=check_passwd(userinfo,mysql,res,row,query);
		lock_exit_system();//判断是否已经满足三次
		if(is_passwd==false)
		{
			printf("用户名或者密码错误，请重新输入!!!\n");
			printf("请按4继续\n");
		}
		else
		{
			printf("用户名和密码都是正确的\n");
			count_passwd=0;//密码输错次数清零
			is_passwd=true;//退出循环
			printf("按3退出密码检查\n");
		}
	}
	return is_passwd;
}

//用户管理模块
void user_manager(user_info_t *userinfo,MYSQL *mysql)//用户管理模块界面
{
	printf("login_status:%c\n",login_status);
	if(login_status=='0')//未登录状态
	{
		//用户登录界面
		user_ui();

		/*与数据库进行交互 变量声明*/
		MYSQL_RES *res = NULL;//数据库查询的结果集
		MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
		char query[500]={0};//放入sql语句
		bool is_username=false;
		bool is_passwd=false;
		//int fields=0;//数据表中的字段数  列数
		//int row_count=0;//行数

		//进行用户名的检查
		is_username=check_username(userinfo,mysql,res,row,query);
		while(is_username==false)//检查用户名时错误  当用户名正确时退出循环
		{
			char ch;
			printf("用户名错误或者用户未注册,请重新输入用户名或者请先注册\n");
			printf("按1到用户注册界面\n");
			printf("按2重新输入用户名\n");
			//printf("用户名输错次数:%d\n",count_username);
			while((ch=getchar())!='3')//按3退出循环
			{
				if(ch == '\n')
					continue;
				switch(ch)
				{
					case '1':
						printf("转到用户注册界面\n");
						user_regist(userinfo,mysql,1);
						break;
					case '2':
						is_username=check_username_three(userinfo,mysql,res,row,query,is_username);//处理是否三次输入用户名错误
						break;
					default:
						break;
				}
			}
		}
		//	printf("用户名输错次数:%d 密码输错次数:%d\n",count_username,count_passwd);
		if(is_username==true)//检查用户名时正确
		{
			char ch_passwd;
			is_passwd=check_passwd(userinfo,mysql,res,row,query);
			while(is_passwd==false)//密码错误
			{
				printf("密码错误,请重新输入用户名和密码!!!\n");
				printf("请按4继续\n");
				while((ch_passwd=getchar())!='3')//按3退出
				{
					switch(ch_passwd)
					{
						case '4':
							//printf("密码输错的次数:%d\n",count_passwd);
							is_passwd=check_passwd_three(userinfo,mysql,res,row,query,is_passwd);//密码输错三次检查
							break;
						default:
							break;
					}
				}
			}

			//printf("is_username=%d  is_passwd=%d\n",is_username,is_passwd);//这里登录应该成功了
			if(is_passwd==true)//密码正确
			{
				printf("用户登录成功\n");
				login_status='1';//登录成功将用户登录状态设为0
				init_sql(res,query,row);//重新初始化
				//检查密码并判断用户类型，进入不同的操作界面
				if(usertype=='2')
				{
					userinfo->usertype=2;
					printf("你是管理员用户,你将进入管理员操作界面\n");
					admin_manager(userinfo,mysql);//进入用户管理模块 admin_manager.c

					printf("管理员按0后你返回到了这里\n");
				}
				else if(usertype=='1')
				{
					userinfo->usertype=1;
					printf("你是学生用户,你将进入学生操作界面\n");
					stu_manager(userinfo,mysql);//进入学生管理模块

					printf("学生用户按0后你返回到了这里\n");
				}
			}
		}
		/*释放内存空间*/
		mysql_free_result(res); 
	}
}
