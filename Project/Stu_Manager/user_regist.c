#include "head.h"

static int count_passwd = 0;
//检查用户名的唯一性
bool onlyone_username(user_info_t* userinfo,MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	bool isonlyone=true;
	sprintf(query,"select user_info.username from user_info");

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!!\n");
	}

	//查询成功后将服务端内容送到客户端
	if((res=mysql_store_result(mysql)) == NULL)//获取查询结果的数据
	{
		printf("mysql_store_result():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_store_result() success!!!\n");
	}
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据	行数就是循环次数
	{
		if(strcmp(userinfo->username,row[0])==0)
		{
			printf("用户名一样\n");
			isonlyone=false;
		}
	}
	return isonlyone;
}

//用户注册界面
//usertype=1  学生用户注册界面
void stu_regist_ui()
{
	printf("成功进入学生用户注册界面\n");//用户注册时用户类型默认为1，管理员用户在登录成功后由管理员自身添加管理员用户(权限设置)
	printf("/***************************************************************/\n");
	printf("/***************学生用户注册界面********************************/\n");
	printf("/***************************************************************/\n");
}
//usertype=2  管理员用户注册界面
void admin_regist_ui()
{
	printf("成功进入管理员用户注册界面\n");//用户注册时用户类型默认为1，管理员用户在登录成功后由管理员自身添加管理员用户(权限设置)
	printf("/***************************************************************/\n");
	printf("/***************管理员用户注册界面********************************/\n");
	printf("/***************************************************************/\n");
}

//自动生成学生用户编号并将用户信息插入到数据库的用户信息表中
void user_insert(user_info_t* userinfo,MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int usertype)
{
	char userno[20]={0};//学生用户编号
	char *pt_userno=userno;//指向userno的指针
	//将用户信息插入到数据库
	if(usertype==1)//如果是学生用户
	{
		pt_userno=get_tableno(mysql,res,row,query,pt_userno,GET_USERNO_STUDENT,NULL);//学生用户编号
		sprintf(query,"insert into user_info(user_no,username,passwd,usertype)VALUES(\"%s\",\"%s\",\"%s\",1);",userno,userinfo->username,userinfo->passwd);
	}
	else if(usertype==2)//管理员用户
	{
		pt_userno=get_tableno(mysql,res,row,query,pt_userno,GET_USERNO_ADMIN,NULL);//管理员用户编号
		sprintf(query,"insert into user_info(user_no,username,passwd,usertype)VALUES(\"%s\",\"%s\",\"%s\",2);",userno,userinfo->username,userinfo->passwd);
	}
	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!! 插入数据成功\n");
	}
}


/*----------------用户注册模块-----------------*/
//需要有一个返回值　　界面跳转比较合理
void user_regist(user_info_t *userinfo,MYSQL *mysql,int usertype,int logintype)
{
	if(usertype==USERTYPE_STUDENT)
		stu_regist_ui();//调用学生用户注册界面
	else if(usertype==USERTYPE_ADMIN)
		admin_regist_ui();//调用管理员用户注册界面

	char current_passwd[20];//确认用户密码
	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句

	//输入用户名
	printf("请输入你的用户名:");
	scanf("%s",userinfo->username);

	//用户名合法性判断，暂不判断  由什么字符组成　几位
	//密码合法性判断，暂不判断    由什么字符组成　几位

	//用户名唯一性检查函数
	if(onlyone_username(userinfo,mysql,res,row,query)==false)//不唯一
	{
		printf("请重新注册!!!\n");
		user_regist(userinfo,mysql,usertype,logintype);
	}
	else//用户名唯一
	{
		//输入密码
		printf("请输入你的密码:");
		scanf("%s",userinfo->passwd);
		//printf("userinfo->passwd:%s\n",userinfo->passwd);
		//输入确认用户密码
		printf("请输入确认的用户密码:");
		scanf("%s",current_passwd);
		//密码和确认密码的唯一性检查
		if(strcmp(userinfo->passwd,current_passwd)==0)
		{
			printf("前后密码一致\n");
			user_insert(userinfo,mysql,res,row,query,usertype);//自动生成编号,插入用户信息到数据库用户表中
			if(usertype==1)
			{
				printf("学生用户注册成功\n");
				if(logintype == USERTYPE_STUDENT)//如果登录用户是学生，则跳转到学生登录界面
				{
					printf("你是学生登录用户,学生用户注册成功后将会跳转至学生登录界面\n");
					user_manager(userinfo,mysql,USERLOGIN,USERTYPE_OTHER,LOGINTYPE_STUDENT);//
					login_status = '0';
				}
				else if(logintype == USERTYPE_ADMIN)//如果登录用户是管理员,则跳转至管理员操作界面
				{
					printf("你是管理员登录用户,学生用户添加成功后将会跳转至管理员操作界面\n");

				}
			}
			else if(usertype==2)
			{
				printf("管理员用户添加成功!!!\n");
				admin_manager(userinfo,mysql);//回到管理模块界面
				//printf("按3放回管理员用户管理界面\n");
			}
		}
		else
		{
			printf("前后密码不一致\n");
			count_passwd++;

			if(count_passwd>=3)
			{
				printf("密码输错三次，退出注册程序\n");
				count_passwd = 0;
				exit(EXIT_FAILURE);
			}

			if((usertype==USERTYPE_STUDENT)&&(logintype==LOGINTYPE_STUDENT))
			{
				printf("请重新注册!!!\n");
				user_regist(userinfo,mysql,USERTYPE_STUDENT,LOGINTYPE_STUDENT);
			}
			else if((usertype == USERTYPE_STUDENT)&&(logintype == LOGINTYPE_ADMIN))
			{
				printf("请重新添加学生用户\n");
				user_regist(userinfo,mysql,USERTYPE_STUDENT,LOGINTYPE_ADMIN);
			}
			else if((usertype==USERTYPE_ADMIN)&&(logintype==LOGINTYPE_ADMIN))
			{
				printf("请重新添加管理员用户\n");
				user_regist(userinfo,mysql,USERTYPE_ADMIN,LOGINTYPE_ADMIN);
			}
		}
	}
	/*释放内存空间*/
	mysql_free_result(res); 
}

