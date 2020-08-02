#include "head.h"

//初始化sql变量
void init_sql(MYSQL_RES *res,char *query,MYSQL_ROW row)
{
	//  printf("初始化\n");
	mysql_free_result(res); //释放本次查询的结果集
	memset(query,0,sizeof(char)*200);//重新初始化
	res=NULL;
	row=NULL;
}

/*系统界面*/
void system_ui()
{
	printf("/************************************************************************/\n");
	printf("/************************************************************************/\n");
	printf("/************************************************************************/\n");
	printf("/*************************欢迎登录学生管理系统***************************/\n");
	printf("/***************按1:进入用户管理模块(管理员用户+已注册学生用户)**********/\n");
	printf("/***************按2:未注册学生用户注册用户信息***************************/\n");
	printf("/***************按3:退出系统界面××××××××××*******************************/\n");
	printf("/************************************************************************/\n");
	printf("/************************************************************************/\n");
	printf("/************************************************************************/\n");
}
MYSQL* connect_database(MYSQL *mysql)
{
	if((mysql=mysql_init(mysql))!=NULL)//初始化mysql 需要返回值 否则连接数据库不成功 会出现段错误
	{
		printf("Init mysql Success!!\n");
	}
	else
	{
		printf("Init mysql Failed!!\n");
		exit(-1);
	}
	if(mysql_library_init(0,NULL,NULL)==0)//初始化mysql库
	{
		printf("Init mysql lib Sucess!!\n");
	}
	else
	{
		printf("Init mysql lib Failed!!\n");
		exit(-1);
	}
	if((mysql=mysql_real_connect(mysql, 0, "root", "123456789", "StuMSystem", 0, NULL, 0))!=NULL)//连接学生管理系统数据库   需要返回值
	{
		printf("Connect StuMSystem database Success!!!\n");
	}
	else
	{
		printf("Connect Success database Failed!!!\n");
	}
	return mysql;
}


int main(int argc, const char *argv[])
{
	/*学生管理系统的界面*/
	system_ui();

	/*相关结构体的声明*/
	user_info_t		*userinfo;//用户信息

	//分配内存
	userinfo = (user_info_t*)malloc(sizeof(user_info_t));

	char ch;//输入的字符:1,2,3,4

	/*连接数据库*/
	MYSQL *mysql=NULL;
	mysql= connect_database(mysql);
	mysql_query(mysql, "set names \'utf8\'");
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '3')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				if(login_status=='0')//用户开始登录时执行段程序
				{
					//用户管理模块 管理员用户+已经注册的学生用户
					printf("进入用户管理模块界面\n");
					user_manager(userinfo,mysql);//用户登录
				}

				if(login_status=='1')//用户登录成功后不在进行重复的登录操作
				{
					printf("你已经登录了，按0后你返回到了这里\n");
					printf("用户类型:%d\n",userinfo->usertype);
					if(userinfo->usertype==2)
					{
						printf("你是管理员用户\n");
						printf("按1回到用户管理模块界面,按2退出系统\n");
						while((ch=getchar())!='3')
						{
							if(ch=='\n')
								continue;
							switch(ch)
							{
								case '1':
									admin_manager(userinfo,mysql);//进入用户管理模块 admin_manager.c
									break;
								case '2':
									exit(-1);
									break;
								default:
									break;
							}
						}
					}
					else if(userinfo->usertype==1)
					{
						printf("你是学生用户\n");
					}

				}
				printf("login_status:%c\n",login_status);
				break;
			case '2':
				//未注册学生进行用户注册
				printf("进入学生注册界面\n");
				user_regist(userinfo,mysql,1);
			default:
				break;
		}
	}

	//释放内存
	mysql_close(mysql);
	mysql_library_end();
	free(userinfo);

	exit(-1);
	return 0;
}
