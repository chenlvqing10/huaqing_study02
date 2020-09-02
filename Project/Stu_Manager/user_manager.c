#include "head.h"


//管理员用户管理界面
void userinfo_ui()
{
	printf("请输入你的选择,以继续操作\n");
	printf("/**************按1:添加新的用户(注册管理员用户和学生用户)*******************************/\n");
	printf("/**************按2:用户信息修改(用户名修改)***********************************/\n");
	printf("/**************按3:用户信息修改(密码修改)*************************************/\n");
	printf("/**************按4:用户信息查询(所有用户信息)*******************************/\n");
	printf("/**************按0:返回上一个界面*******************************************/\n");
}


//进行数据查询,只有管理员有这个权限
void userinfo_select(user_info_t *userinfo,MYSQL *mysql)
{
	MYSQL_RES *res       = NULL;//数据库查询的结果集
	MYSQL_ROW row        = NULL;//char**  指向一个字符串数组，从结果集中取得数据
	int       fields     = 0;
	char      query[500] = {0};//放入sql语句

	sprintf(query,"select * from user_info;");

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询语句 成功返回0
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

	int row_count = 0;
	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(row_count==0)
		{
			printf("数据库用户表中含有的用户信息:\n");
			printf("+---------+------------+----------+-----------+\n");
			printf("| userid  |  username  |  passwd  | usertype  |\n");
			printf("+---------+------------+----------+-----------+\n");
		}
		printf("|%-9s|%-12s|%-10s|%-11s|\n",row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");
	init_sql(res,query,row);
}

//修改用户名  只有管理员才有本权限
void username_update(user_info_t *userinfo,MYSQL *mysql)
{
	char new_username[20] = {0};
	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句
	int  fields = 0;//数据集行数
	sprintf(query,"select * from user_info;");

	//执行sql语句，成功返回0
	if(mysql_real_query(mysql,query,strlen(query)) != 0)
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!! 插入数据成功\n");
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

	char userid[MAXSIZE_TABLE][20] = {0};
	char username[MAXSIZE_TABLE][20] = {0};

	int row_count = 0;
	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(row_count==0)
		{
			printf("数据库用户表中含有的用户信息:\n");
			printf("+---------+------------+----------+-----------+\n");
			printf("| userid  |  username  |  passwd  | usertype  |\n");
			printf("+---------+------------+----------+-----------+\n");
		}
		printf("|%-9s|%-12s|%-10s|%-11s|\n",row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(userid[row_count],row[fields-4]);
		strcpy(username[row_count],row[fields-3]);
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");

	/*
	   for(int i=0;i<row_count;i++)
	   {
	   printf("userid[%d] = %s usrname[%d] = %s \n",i,userid[i],i,username[i]);
	   }
	   */
	int row_op = 0;
	printf("你现在有[%d]条用信息,请选择你要处理的用户信息是哪一条(数据行 从0开始):",row_count);//如果有界面的话，界面会显示出全部的数据，可以通过按钮进行操作
	scanf("%d",&row_op);

	//超级用户权限限制,任何人都无法修改
	if(strcmp(userid[row_op],SUPERUSERID)==0)
	{
		printf("超级用户无法修改\n");
		exit(-1);
	}

	printf("你要处理的是第[%d]条用户信息,现在你的用户ID是[%s],你的用户名是[%s],请输入你想要修改的新的用户名:",row_op,userid[row_op],username[row_op]);
	scanf("%s",new_username);

	//执行更新语句
	sprintf(query,"update user_info set user_info.username = \"%s\" where user_info.user_no = \"%s\";",new_username,userid[row_op]);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!! 用户名更新成功\n");
	}
}
//修改密码 只有管理员才有此权限
void userpwd_update(user_info_t *userinfo,MYSQL *mysql)
{
	char new_passwd[20] = {0};
	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句
	int  fields = 0;//数据集行数
	sprintf(query,"select * from user_info;");

	//执行sql语句，成功返回0
	if(mysql_real_query(mysql,query,strlen(query)) != 0)
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!! 执行sql语句成功\n");
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

	char userid[20][20] = {0};
	char passwd[20][20] = {0};

	int row_count = 0;
	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(row_count==0)
		{
			printf("数据库用户表中含有的用户信息:\n");
			printf("+---------+------------+----------+-----------+\n");
			printf("| userid  |  username  |  passwd  | usertype  |\n");
			printf("+---------+------------+----------+-----------+\n");
		}
		printf("|%-9s|%-12s|%-10s|%-11s|\n",row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(userid[row_count],row[fields-4]);
		strcpy(passwd[row_count],row[fields-2]);
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");
	int row_op = 0;
	char current_passwd[20];//确认用户密码
	int count_pwd = 0;

	printf("你现在有[%d]条用信息,请选择你要处理的用户信息是哪一条(数据行 从0开始):",row_count);//如果有界面的话，界面会显示出全部的数据，可以通过按钮进行操作
	scanf("%d",&row_op);
	//超级用户权限限制,任何人都无法修改
	if(strcmp(userid[row_op],SUPERUSERID)==0)
	{
		printf("超级用户无法修改\n");
		exit(-1);
	}
	printf("你要处理的是第[%d]条用户信息,现在你的用户ID是[%s],你的用户密码是[%s],请输入你想要修改的新的用户密码:",row_op,userid[row_op],passwd[row_op]);
	scanf("%s",new_passwd);

	//输入确认用户密码
	printf("请再次输入修改的密码:");
	scanf("%s",current_passwd);
	//修改的新密码和确认密码的唯一性检查
	while(strcmp(new_passwd,current_passwd)!=0)
	{
		count_pwd++;
		if(count_pwd>=3)
		{
			printf("两次修改的密码不同,已经输错三次,你将退出系统\n");
			exit(EXIT_FAILURE);
		}
		printf("两次修改的密码不一致\n");
		printf("请重新输入确认的修改密码\n");
		scanf("%s",current_passwd);
	}

	if(strcmp(new_passwd,current_passwd)==0)
	{
		printf("两次输入的修改密码一致,执行更新语句\n");
		sprintf(query,"update user_info set user_info.passwd = \"%s\" where user_info.user_no = \"%s\";",new_passwd,userid[row_op]);

		if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
		{
			printf("mysql_real_query():%s\n",mysql_error(mysql));
			exit(-1);
		}
		else
		{
			printf("mysql_real_query() sucess!!! 密码更新成功\n");
		}
	}

}


void userinfo_manager(user_info_t *userinfo,MYSQL *mysql,int logintype)
{
	char ch = '0';
	int usertype =0;

	if(logintype == LOGINTYPE_STUDENT)//登录者是学生　无权限　　一般不会到此逻辑　安全漏洞处理
	{
		printf("你是学生用户,无权进行用户模块操作\n");
		exit(EXIT_FAILURE);//退出系统
	}
	else if(logintype == LOGINTYPE_ADMIN)//登录者是管理员
	{
		userinfo_ui();//界面
		printf("请输入你的选项:");
		while((ch = getchar()) != '0')
		{
			if(ch == '\n')
				continue;
			switch(ch)
			{
				case '1':
					printf("请选择你要添加的用户类型:1---学生用户  2----管理员用户\n");
					scanf("%d",&usertype);
					if(usertype == 1)
						user_regist(userinfo,mysql,USERTYPE_STUDENT,LOGINTYPE_ADMIN);//学生用户注册　管理员登录  注册是否成功呢？
					else if(usertype == 2)
						user_regist(userinfo,mysql,USERTYPE_ADMIN,LOGINTYPE_ADMIN);//管理员用户注册　管理员登录
					break;
				case '2':                                              
					username_update(userinfo,mysql);//用户名修改
					break;
				case '3':
					userpwd_update(userinfo,mysql);//用户密码修改
					break;
				case '4':
					userinfo_select(userinfo,mysql);//用户信息查询
					break;
				case '5':
					userinfo_select(userinfo,mysql);//用户信息删除  注意外键相关的数据表
				default:
					break;
			}
			userinfo_ui();//界面
			printf("请输入你的选项:");
		}
	}
}

//用户管理模块
//@func:根据用户操作类型执行不同的用户用户操作
//@userinfo:用户信息表结构体指针
//@mysql:连接的数据库
//@usertype:操作的对象用户类别
//@logintype:登录的对象用户类别
//@return:NONE
void user_manager(user_info_t *userinfo,MYSQL *mysql,int optype,int usertype,int logintype)//用户管理模块界面
{
	if(optype == USERLOGIN)//用户登录模块 类别的区分在登录函数处理(通过用户名查询) 故不进行传参
		user_login(userinfo,mysql);

	if(optype == USERREGST)//用户注册模块　需要区分操作对象　登录对象　　因为管理员需要添加管理理员用户有时候也可能需要注册学生用户　　学生只能注册学生用户
	{
		user_regist(userinfo,mysql,usertype,logintype);
	}

	if(optype == USERINFOMANAGER)//用户信息管理模块　　　管理员:两类用户的增删改查　　　学生:无此权限
		userinfo_manager(userinfo,mysql,logintype);
}
