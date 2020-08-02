#include "head.h"

//检查用户名的唯一性
bool onlyone_username(user_info_t* userinfo,MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	bool isonlyone=true;
	int fields=0;

	sprintf(query,"select user_info.username from user_info");
	//printf("query=%s\n",query);

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
		//统计字段名个数(列数)
		fields=mysql_num_fields(res);
		//printf("fields:%d\n",fields);
		//打印字段的数据
		for(int i=0; i<fields; i++)//行
		{
			//printf("name=%s\n",row[i]);
			//printf("username=%s\n",userinfo->username);
			if(strcmp(userinfo->username,row[i])==0)
			{
				printf("用户名一样\n");
				isonlyone=false;
			}
		}
	}
	init_sql(res,query,row);
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
	pt_userno=get_tableno(mysql,res,row,query,pt_userno,1,NULL);//用户编号
	//将用户信息插入到数据库
	if(usertype==1)//如果是学生用户
		sprintf(query,"insert into user_info(user_no,username,passwd,usertype)VALUES(\"%s\",\"%s\",\"%s\",1);",userno,userinfo->username,userinfo->passwd);
	else if(usertype==2)//管理员用户
		sprintf(query,"insert into user_info(user_no,username,passwd,usertype)VALUES(\"%s\",\"%s\",\"%s\",2);",userno,userinfo->username,userinfo->passwd);

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
void user_regist(user_info_t *userinfo,MYSQL *mysql,int usertype)
{
	if(usertype==1)
		stu_regist_ui();//调用学生用户注册界面
	else if(usertype==2)
		admin_regist_ui();//调用管理员用户注册界面

	char current_passwd[20];//确认用户密码
	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句

	//输入用户名
	printf("请输入你的用户名:");
	scanf("%s",userinfo->username);
	//printf("userinfo-<username=%s\n",userinfo->username);

	//用户名合法性判断，暂不判断
	//密码合法性判断，暂不判断

	//用户名唯一性检查函数
	if(onlyone_username(userinfo,mysql,res,row,query)==false)//不唯一
	{
		printf("用户名重复\n");
		if(usertype==1)
		{
			printf("请重新注册!!!\n");
			user_regist(userinfo,mysql,1);
		}
		else if(usertype==2)
		{
			printf("请重新添加!!!\n");
			user_regist(userinfo,mysql,2);
		}
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
				printf("学生用户注册成功，接下来请在用户登录界面进行登录!!!\n");
				user_manager(userinfo,mysql);
			}
			else if(usertype==2)
			{
				printf("管理员用户添加成功!!!\n");
				admin_manager(userinfo,mysql);//回答管理模块界面
				//printf("按3放回管理员用户管理界面\n");
			}
		}
		else
		{
			printf("前后密码不一致\n");
			if(usertype==1)
			{
				printf("请重新注册!!!\n");
				user_regist(userinfo,mysql,1);
			}
			else if(usertype==2)
			{
				printf("请重新添加!!!\n");
				user_regist(userinfo,mysql,2);
			}
		}
	}
	/*释放内存空间*/
	mysql_free_result(res); 
}
