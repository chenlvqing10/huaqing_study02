#include "head.h"

void admin_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
	if(login_status==0)
	{
		printf("/***********************欢迎进入管理员操作模块界面********************************/\n");
	}
	else
	{
		printf("/***********************欢迎返回管理员操作模块界面********************************/\n");
	}
	printf("/***********************1.添加管理员用户******************************************/\n");
	printf("/***********************2.查询，添加,修改,删除管理员自身的信息*********************/\n");
	printf("/***********************3.学生信息的查询(包括成绩)********************************/\n");
	printf("/***********************4.学生信息的修改******************************************/\n");
	printf("/***********************5.学生信息的删除******************************************/\n");
	printf("/***********************6.更新学生的成绩******************************************/\n");
	printf("/***********************7.添加,查看,更新,删除学院信息*****************************/\n");
	printf("/***********************8.添加,查看,更新,删除学生学期的科目信息*******************/\n");
	printf("/***********************9.添加,查看,更新,删除学生学期的科目成绩(期末成绩)**********/\n");
	printf("/***********************0.退出管理员管理模块***************************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
}
void admininfo_ui()
{
	printf("请输入你的选择,以继续操作\n");
	printf("/**************按1:管理员信息查看*******************************/\n");
	printf("/**************按2:管理员信息修改*******************************/\n");
	printf("/**************按3:管理员删除删除*******************************/\n");
	printf("/**************按4:返回管理员管理模块(数据处理完了)**************/\n");
	printf("/**************按4:处理写一个管理员用户数据(数据处理未完了)******/\n");
}
void admininfo_insert_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/******************************管理员信息添加界面*********************************/\n");
	printf("/******************************请输入管理员的相关信息*****************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
}

void admininfo_Select_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/******************************管理员信息查看界面**********************************/\n");
	printf("/******************************管理员的信息如下×××××××*****************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
}

void admininfo_select(admin_info_t *admininfo,MYSQL *mysql)
{
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句
	sprintf(query,"select * from admin_info where admin_info.user_no=\"%s\";",admininfo->user_no);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	//else
	//{
	//	printf("mysql_real_query() sucess!!!\n");
	//	}

	//查询成功后将服务端内容送到客户端
	if((res=mysql_store_result(mysql)) == NULL)//获取查询结果的数据
	{   
		printf("mysql_store_result():%s\n",mysql_error(mysql));
		exit(-1);
	}
	//else
	//{
	//	printf("mysql_store_result() success!!!\n");
	//}
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{

		//int fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		//for(int i=0; i<fields; i++)//列数循环,得到用户编号
		//{

		printf("管理员用户ID:%s  管理员姓名:%s  管理员性别:%s   管理员年龄:%s   管理员所在学院:%s\n",row[0],row[1],row[2],row[3],row[4]);
		//}
	}
	init_sql(res,query,row);
}
void admininfo_update_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/******************************管理员信息修改(更新)界面***************************/\n");
	printf("/******************************请选额你想要更新的管理员相关信息*******************/\n");
	printf("/******************************1.修改管理员的姓名*********************************/\n");
	printf("/******************************2.修改管理员的性别*********************************/\n");
	printf("/******************************3.修改管理员的年龄*********************************/\n");
	printf("/******************************4.修改管理员的所在学院*****************************/\n");
	printf("/******************************0.退出管理员修改选项,执行更新***********************/\n");
	printf("/*********************************************************************************/\n");
}
void admininfo_update(admin_info_t *admininfo,MYSQL *mysql)
{
	char ch;
	int gender;
	char college_name[20]="信息技术学院";
	char collegeno[20]={0};//学院编号
	char *pt_collegeno=collegeno;//指针指向学院编号
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句
	
	sprintf(query,"select admin_no,admin_name,admin_gender,admin_age,college_no from admin_info where admin_info.user_no=\"%s\";",admininfo->user_no);//查看数据表中是否有本行用户ID的数据
	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	//else
	//{
	//	printf("mysql_real_query() sucess!!!\n");
	//	}

	//查询成功后将服务端内容送到客户端
	if((res=mysql_store_result(mysql)) == NULL)//获取查询结果的数据
	{   
		printf("mysql_store_result():%s\n",mysql_error(mysql));
		exit(-1);
	}
	//else
	//{
	//	printf("mysql_store_result() success!!!\n");
	//}
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		strcpy(admininfo->admin_no,row[0]);
		strcpy(admininfo->admin_name,row[1]);
		strcpy(admininfo->gender,row[2]);
		admininfo->admin_age=*row[3];
		strcpy(admininfo->college_no,row[4]);
		printf("管理员编号:%s     ",admininfo->admin_no);
		printf("用户编号:%s\n",admininfo->user_no);
	}

	//init_sql(res,query,row);

	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("请输入要修改的管理员姓名:");
				scanf("%s",admininfo->admin_name);
				printf("姓名:%s\n",admininfo->admin_name);
				break;
			case '2':
				printf("请输入要修改的管理员性别编号(0--male,1--femal):");
				scanf("%d",&gender);
				if(gender==0)
					strcpy(admininfo->gender,"男");
				else if(gender==1)
					strcpy(admininfo->gender,"女");
				printf("性别:%s\n",admininfo->gender);
				break;
			case '3':
				printf("请输入要修改的管理员年龄:");
				scanf("%d",&admininfo->admin_age);
				printf("年龄:%d\n",admininfo->admin_age);
				break;
			case '4':
				printf("请输入要修改的管理员所在学院:");
				scanf("%s",college_name);

				pt_collegeno=get_tableno(mysql,res,row,query,pt_collegeno,5,college_name);//得到学院编号
				strcpy(admininfo->college_no,collegeno);
				printf("学院编号:%s\n",admininfo->college_no);
				break;
			default:
				break;
		}
	}


	sprintf(query,"update admin_info set admin_name='%s',admin_gender='%s',admin_age=%d,college_no='%s' where admin_no='%s';"
			,admininfo->admin_name,admininfo->gender,admininfo->admin_age,admininfo->college_no,admininfo->admin_no);//查看数据表中是否有本行用户ID的数据
	
	printf("sql语句:%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("数据更新成功\n");
	}
	init_sql(res,query,row);
}

void admininfo_delete_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/*******************************管理员信息删除界面********************************/\n");
	printf("/******************请确认你是否真得要删除管理员信息!!!(谨慎操作)×*****************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
}
bool check_admininfo_byuserno(user_info_t *userinfo,admin_info_t *admininfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	bool is_empty=true;
	init_sql(res,query,row);

	//关联用户数据表和管理员信息表中的user_no来进行数据的查询
	sprintf(query,"select * from admin_info where admin_info.user_no=\"%s\";",admininfo->user_no);//查看数据表中是否有本行用户ID的数据

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
	if((row=mysql_fetch_row(res))!=NULL) //不为空
		is_empty=false;

	init_sql(res,query,row);
	return is_empty; 
}

void admininfo_insert(user_info_t *userinfo,admin_info_t *admininfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	init_sql(res,query,row);
	//局部变量声明
	char adminno[8]={0};//管理员编号
	int year=1900;//入校年份声明并初始化
	int month=0;//入校月份申明并初始化
	char subadminno[8]={0};//得到管理员编号的后两位数值
	char *pt_subadminno=subadminno;//指针先指向subadminno
	int  gender=0;//性别 0--male  1--femal
	char college_name[20]="信息技术学院";
	char collegeno[20]={0};//学院编号
	char *pt_collegeno=collegeno;//指针指向学院编号
	time_t timep;
	struct tm *p_time;

	printf("用户编号:%s\n",admininfo->user_no);

	//输入年份和月份，自动生成管理员编号
	printf("请输入入校年份:");
	scanf("%d",&year);
	printf("请输入入校月份:");
	scanf("%d",&month);

	pt_subadminno=get_tableno(mysql,res,row,query,pt_subadminno,4,NULL);//得到管理员编号最后两位

	//年份和月份的检查
	time(&timep);
	p_time=localtime(&timep);

	while((year>p_time->tm_year+1900)||(year<1900))
	{
		printf("年份有问题,请重新输入入校年份!!!\n");
		scanf("%d",&year);
	}
	if((month<10)&&(month>=0))
	{
		sprintf(adminno,"%d0%d%s",year,month,subadminno);
	}
	else if((month>=10)&&(month<=12))
	{
		sprintf(adminno,"%d%d%s",year,month,subadminno);
	}
	while((month<0)||(month>12))
	{
		printf("月份有问题，请重新输入入校月份\n!!!");
		scanf("%d",&month);
	}
	strncpy(admininfo->admin_no,adminno,8);//得到8位的管理员编号
	printf("管理员编号:%s\n",admininfo->admin_no);

	printf("请输入管理员的姓名:");
	scanf("%s",admininfo->admin_name);
	printf("姓名:%s\n",admininfo->admin_name);

	printf("请输入管理员的性别编号(0--male,1--femal):");
	scanf("%d",&gender);
	if(gender==0)
		strcpy(admininfo->gender,"男");
	else if(gender==1)
		strcpy(admininfo->gender,"女");
	printf("性别:%s\n",admininfo->gender);

	printf("请输入管理员的年龄:");
	scanf("%d",&admininfo->admin_age);
	printf("年龄:%d\n",admininfo->admin_age);

	printf("请输入管理员所在的学院:");
	scanf("%s",college_name);

	pt_collegeno=get_tableno(mysql,res,row,query,pt_collegeno,5,college_name);//得到学院编号
	strcpy(admininfo->college_no,collegeno);
	printf("学院编号:%s\n",admininfo->college_no);
	printf("用户编号:%s\n",admininfo->user_no);

	//输入数据表

	sprintf(query,"insert into admin_info(admin_no,admin_name,admin_gender,admin_age,college_no,user_no)VALUES(\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\");"
			,admininfo->admin_no,admininfo->admin_name,admininfo->gender,admininfo->admin_age,admininfo->college_no,admininfo->user_no);
	printf("sql语句:%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!! 插入数据成功\n");
	}

	init_sql(res,query,row);
}

//管理员信息管理  查看，添加,修改，删除管理员信息
void admininfo_manager(user_info_t *userinfo,admin_info_t *admininfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	char ch;
	//得到全部的管理员用户ID 需要分别对这些管理员用户进行操作
	sprintf(query,"select user_info.user_no,username from user_info where usertype=2;");

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行数据库查询 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	//else
	//{
	//	printf("mysql_real_query() sucess!!!\n");
	//	}

	//查询成功后将服务端内容送到客户端
	if((res=mysql_store_result(mysql)) == NULL)//获取查询结果的数据
	{   
		printf("mysql_store_result():%s\n",mysql_error(mysql));
		exit(-1);
	}
	//else
	//{
	//	printf("mysql_store_result() success!!!\n");
	//}
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		//用于局部数据库操作的mysql变量
		MYSQL_RES *res1=NULL;
		MYSQL_ROW row1=NULL;
		printf("UserID=%s Username=%s\n",row[0],row[1]);//显示 用户ID和用户名
		int fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		for(int i=0; i<fields; i++)//列数循环,得到用户编号
		{
			strcpy(admininfo->user_no,row[0]);
		}
		bool is_admininfo_empty=check_admininfo_byuserno(userinfo,admininfo,mysql,res1,row1,query);//查看管理员信息是否为空
		if(is_admininfo_empty==true)//数据为空
		{
			printf("用户ID=%s的管理员信息不存在\n",admininfo->user_no);
			admininfo_insert_ui();//插入界面
			admininfo_insert(userinfo,admininfo,mysql,res1,row1,query);
		}
		else//不为空,根据选项进行其他操作
		{
			printf("用户ID=%s的管理员信息存在\n",admininfo->user_no);
			admininfo_ui();
			while((ch = getchar()) != '4')
			{
				if(ch == '\n')
					continue;
				switch(ch)
				{
					case '1':
						admininfo_Select_ui();
						admininfo_select(admininfo,mysql);
						admininfo_ui();
						break;
					case '2':
						admininfo_update_ui();
						admininfo_update(admininfo,mysql);
						admininfo_ui();
						break;
						break;
					case '3':
						admininfo_delete_ui();
						break;
					default:
						break;
				}
			}
		}
	}
}
//管理员管理模块
void admin_manager(user_info_t *userinfo,MYSQL *mysql)
{
	//结构体变量的声明
	admin_info_t    *admininfo;//管理员信息
	stu_info_t      *stuinfo;//学生信息
	stu_sub_t       *stusub;//学生学期科目
	stu_score_t     *stuscore;//学生学期科目成绩
	college_info_t  *collegeinfo;//学院
	profs_info_t    *profsinfo;//专业
	sub_info_t      *subinfo;//科目

	//分配内存以及初始化
	collegeinfo = (college_info_t*)malloc(sizeof(college_info_t));
	admininfo   = (admin_info_t*)malloc(sizeof(admin_info_t));
	memset(admininfo,0,sizeof(admin_info_t));

	//管理员管理模块界面
	admin_ui();

	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句

	//根据选项的不同进行界面操作
	char ch;//输入的字符:1,2,3,4,5,6,7,8,9,0---退出
	printf("请输入你的选项:\n");

	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("添加管理员用户\n");
				user_regist(userinfo,mysql,2);//进入用户注册界面
				break;
			case '2':
				printf("你可以在这里进行管理员信息的查看,添加,修改,删除\n");
				printf("先检查学院信息,如果学院信息为空要先添加相应的学院信息\n");//管理员信息表与学院用户表相联系
				if(check_college_empty(collegeinfo,mysql,res,row,query)==true)//学院信息为空
				{
					printf("学院信息为空\n");
					college_manager(collegeinfo,mysql,res,row,query);
					printf("按2添加管理员用户信息\n");
					printf("按7继续添加学院信息\n");
				}
				else
				{
					printf("学院信息不为空,进入管理员信息操作界面\n");
					admininfo_manager(userinfo,admininfo,mysql,res,row,query);
					printf("用户按了4，所以我返回到了这里!!!\n");
					admin_ui();
				}
				break;
			case '3':
				printf("学生信息的查询(包括成绩)\n");
				break;
			case '4':
				printf("学生信息的修改\n");
				break;
			case '5':
				printf("学生信息的删除\n");
				break;
			case '6':
				printf("更新学生的成绩\n");
				break;
			case '7':
				printf("添加学院信息\n");
				college_manager(collegeinfo,mysql,res,row,query);
				admin_ui();
				break;
			case '8':
				printf("添加学生学期的科目信息\n");
				break;
			case '9':
				printf("添加学生学期的科目成绩(期末成绩)\n");
				break;
			default:
				break;

		}
	}
	//释放内存
	free(collegeinfo);
	free(admininfo);
}
