#include "head.h"

void stu_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
	printf("/***********************欢迎进入学生操作模块界面******************************/\n");
	printf("/***********************1.查询学生自身的基本信息(单个学生用户)**********************/\n");
	printf("/***********************2.修改学生自身的基本信息************************************/\n");
	printf("/***********************3.查询学生自身不同学期的科目信息(含成绩)********************/\n");
	printf("/***********************4.添加学生自身的基本信息(只有一次添加的机会)************××**/\n");
	printf("/***********************0:返回上一个界面********************************************/\n");
	printf("/***********************************************************************************/\n");
	printf("/***********************************************************************************/\n");
}

void stuinfo_update_ui()
{

	printf("/*********************************************************************************/\n");
	printf("/******************************学生信息修改(更新)界面***************************/\n");
	printf("/******************************请选择你想要更新的学生相关信息*******************/\n");
	printf("/******************************1.修改学生的姓名*********************************/\n");
	printf("/******************************2.修改学生的性别*********************************/\n");
	printf("/******************************3.修改学生的年龄*********************************/\n");
	printf("/******************************4.修改学生的年级*********************************/\n");
	printf("/******************************5.修改学生的班级*********************************/\n");
	printf("/******************************6.修改学生的学院*********************************/\n");
	printf("/******************************0.退出学生修改选项,执行更新***********************/\n");
	printf("/*********************************************************************************/\n");

}

void stusubinfo_manager_ui()
{
	printf("/**************************************************************************************************/\n");
	printf("/**************************************************************************************************/\n");
	printf("/**************************************************************************************************/\n");
	printf("/***********************欢迎进入学生科目操作模块界面***********************************************/\n");
	printf("/***********************1.添加不同学院不同专业的学生科目信息(指定某个学生)*************************/\n");
	printf("/***********************2.修改不同学院不同专业的学生科目信息(指定某个学生)*************************/\n");
	printf("/***********************3.删除不同学院不同专业的学生科目信息(指定某个学生)*************************/\n");
	printf("/***********************4.查询不同学院不同专业的学生科目信息(指定某个学生)*************************/\n");
	printf("/***********************0:返回上一个界面***********************************************************/\n");
	printf("/**************************************************************************************************/\n");
	printf("/**************************************************************************************************/\n");
}

void stuscoreinfo_manager_ui()
{
	printf("/************************************************************************************************************/\n");
	printf("/************************************************************************************************************/\n");
	printf("/************************************************************************************************************/\n");
	printf("/***********************欢迎进入学生科目成绩操作模块界面*****************************************************/\n");
	printf("/***********************1.添加不同学院不同专业的学生不同科目的成绩信息(指定某个学生)*************************/\n");
	printf("/***********************2.修改不同学院不同专业的学生不同科目的成绩信息(指定某个学生)*************************/\n");
	printf("/***********************3.删除不同学院不同专业的学生不同科目的成绩信息(指定某个学生)*************************/\n");
	printf("/***********************4.查询不同学院不同专业的学生不同科目的成绩信息(指定某个学生)*************************/\n");
	printf("/***********************0:返回上一个界面*********************************************************************/\n");
	printf("/************************************************************************************************************/\n");
	printf("/************************************************************************************************************/\n");
}

int getstusubCount(MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char *stuno)
{
	int count = 0;
	for(int i=1;i<12;i++)
	{
		sprintf(query,"select stu_sub.stu_sub_no%d from stu_sub where stu_sub.stu_no = \"%s\";",i,stuno);
	//	printf("sql语句:%s\n",query);
		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		if((row=mysql_fetch_row(res)) != NULL)
		{
			if(strcmp(row[0],""))
				count ++;
		}
	}

	return count;
}
bool check_stuinfo_empty(user_info_t *userinfo,stu_info_t * stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int logintype)
{
	bool is_stuinfo_empty = false;
	init_sql(res,query,row);

	//根据不同的登录用户类型执行不同的SQL语句
	if(logintype == LOGINTYPE_ADMIN)
		sprintf(query,"select * from stu_info;");//查询学生基本信息表中所有的学生信息
	else
		sprintf(query,"select * from stu_info where stu_info.stu_no =\
				(select stu_info.stu_no from stu_info where stu_info.user_no = \"%s\");",userinfo->user_no);//查询该登录学生用户的学生信息

	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		is_stuinfo_empty = true;

	return is_stuinfo_empty;
}

bool check_stusubinfo_empty(user_info_t *userinfo,stu_info_t * stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int logintype)
{
	bool is_stusubinfo_empty = false;
	init_sql(res,query,row);

	if(logintype == LOGINTYPE_ADMIN)
		sprintf(query,"select * from stu_sub;");//查询学生科目表中所有的学生科目信息
	else
		sprintf(query,"select * from stu_sub where stu_sub.stu_no = \
				(select stu_info.stu_no from stu_info where stu_info.user_no =\
				 \"%s\");",userinfo->user_no);//查询该登录学生用户的学生科目信息

	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		is_stusubinfo_empty = true;

	return is_stusubinfo_empty;
}

bool check_stusubinfo_empty_bystuno(stu_info_t * stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	bool is_stusubinfo_empty = false;
	init_sql(res,query,row);

	sprintf(query,"select * from stu_sub where stu_sub.stu_no = \"%s\";",stuinfo->stu_no);

	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		is_stusubinfo_empty = true;

	return is_stusubinfo_empty;
}

bool check_stuscoreinfo_empty_bystuno(stu_info_t * stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	bool is_stuscoreinfo_empty = false;
	init_sql(res,query,row);

	sprintf(query,"select * from stu_score where stu_score.stu_no = \"%s\";",stuinfo->stu_no);//查询学生科目成绩表中所有的学生科目成绩信息

	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		is_stuscoreinfo_empty = true;

	return is_stuscoreinfo_empty;
}

bool check_stuscoreinfo_empty(user_info_t *userinfo,stu_info_t * stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int logintype)
{
	bool is_stuscoreinfo_empty = false;
	init_sql(res,query,row);

	if(logintype == LOGINTYPE_ADMIN)
		sprintf(query,"select * from stu_score;");//查询学生科目成绩表中所有的学生科目成绩信息
	else
		sprintf(query,"select * from stu_score where stu_socre.stu_no = (\
			select stu_info.user_no = \"%s\" );",userinfo->user_no);//查询该登录学生用户的学生科目成绩

	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		is_stuscoreinfo_empty = true;

	return is_stuscoreinfo_empty;
}

//检查学生信息表中该学生用户的信息是否不为空
bool check_stuinfo_empty_byuserid(user_info_t *userinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	bool is_stuinfo_empty_byuserid =true; 
	sprintf(query,"select stu_info.* from stu_info,user_info where user_info.usertype = 1 and stu_info.user_no = \"%s\" GROUP BY stu_info.stu_no;",userinfo->user_no);
	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);
	if((row = mysql_fetch_row(res)) != NULL)
		is_stuinfo_empty_byuserid = false;

	return is_stuinfo_empty_byuserid;
}


//添加学生信息  管理员用户  学生用户 都有此权限  -----学生用户只有一次添加的机会
void stuinfo_insert(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	//init_sql(res,query,row);//管理员模块调用的时候如果学生信息查询函数(stuinfo_select())也调用了该初始化函数,那么会造成二次释放的问题

	//局部变量声明
	char stuno[9]			= {0};           //学生编号
	int  year				= 1900;         //入校年份声明并初始化
	int  month				= 0;           //入校月份申明并初始化
	char substuno[2]        = {0};         //得学生编号的后两位数值
	char *pt_substuno       = substuno;    //指针指向substuno

	int  gender=0;//性别 0--male  1--femal
	char college_name[20]="信息技术学院";//学院名称
	time_t timep;//获取时间
	struct tm *p_time;
	char profs_name[20] = "C语言工程师";//专业名称

	//结构体声明和初始化
	college_info_t  *collegeinfo;//学院
	profs_info_t    *profsinfo;//专业            
	collegeinfo     = (college_info_t*)malloc(sizeof(college_info_t));
	profsinfo       = (profs_info_t*)malloc(sizeof(profs_info_t));
	memset(collegeinfo,0,sizeof(college_info_t));
	memset(profsinfo,0,sizeof(college_info_t));

	//得到学生的用户ID
	if(logintype==LOGINTYPE_ADMIN)//管理员
	{
		//1.查询用户表显示学生用户的记录条数
		sprintf(query,"select * from user_info where user_info.usertype = 1;");
		printf("sql语句:%s\n",query);
		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		int row_count = 0;
		int fields    = 0;
		int row_ops   = 0;
		char userid[MAXSIZE_TABLE][20] = {0};
		char username[MAXSIZE_TABLE][20] = {0};  

		//获取数据集  char**类型  每一行的数据
		while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
		{
			fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
			if(row_count==0)
			{
				printf("数据库用户表中含有的学生用户信息:\n");
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
		printf("username = %s\n",username[0]);
		printf("请选择为那个学生用户添加学生基本信息(输入记录数):");
		scanf("%d",&row_ops);
		strncpy(userinfo->user_no,userid[row_ops],7);
		strcpy(userinfo->username,username[row_ops]);
		userinfo->user_no[7] = '\0';
		printf("选择了用户编号[%s] 用户名称[%s]的学生添加学生信息\n",userinfo->user_no,userinfo->username);
	}
	else
	{
		printf("学生的用户编号:%s\n",userinfo->user_no);
	}

	//2.检查数据库学生信息表中是否已经具有该学生用户的信息  insert操作需要检查
	if(check_stuinfo_empty_byuserid(userinfo,mysql,res,row,query) == false)
	{
		if((logintype == LOGINTYPE_ADMIN)&&(optype == OPTYPE_ADMIN_STU_INSERT))
		{
			printf("该学生用户的基本信息已经存在了，不能重复添加!!!\n");
		}
		else if((logintype == LOGINTYPE_ADMIN)&&(optype == OPTYPE_STUDENT_STU_INSERT))
		{

			printf("你的基本信息已经存在了，不用进行重复的添加\n");
		}
	}
	else
	{
		//1.得到学生编号
		strcpy(stuinfo->user_no,userinfo->user_no);
		//printf("stuinfo->user_no = %s\n",stuinfo->user_no);

		//输入年份和月份，自动生成学生编号
		printf("请输入入校年份:");
		scanf("%d",&year);
		printf("请输入入校月份:");
		scanf("%d",&month);

		pt_substuno=get_tableno(mysql,res,row,query,pt_substuno,6,NULL);//得到学生编号最后两位

		//年份和月份的检查
		time(&timep);
		p_time=localtime(&timep);
		while((year>p_time->tm_year+1900)||(year<1900))
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
			sprintf(stuno,"%d0%d%s",year,month,substuno);
		}
		else if((month>=10)&&(month<=12))
		{
			sprintf(stuno,"%d%d%s",year,month,substuno);
		}
		while((month<0)||(month>12))
		{
			printf("月份有问题，请重新输入入校月份\n!!!");
			scanf("%d",&month);
		}

		strncpy(stuinfo->stu_no,stuno,8);//得到8位的学生编号
		printf("学生编号:%s\n",stuinfo->stu_no);

		//2.其他基本数据的输入
		printf("请输入学生的姓名:");
		scanf("%s",stuinfo->stu_name);
		printf("姓名:%s\n",stuinfo->stu_name);

		printf("请输入学生的性别编号(0--male,1--femal):");
		scanf("%d",&gender);
		if(gender==0)
			strcpy(stuinfo->gender,"男");
		else if(gender==1)
			strcpy(stuinfo->gender,"女");
		printf("性别:%s\n",stuinfo->gender);

		printf("请输入学生的年龄:");//排除输入字符的情况
		int ret = scanf("%d",&stuinfo->stu_age);
		while(ret<=0)
		{
			//清缓冲区
			while(getchar()!='\n');
			printf("请重新输入学生的年龄:");
			ret = scanf("%d",&stuinfo->stu_age);
		}
		printf("年龄:%d\n",stuinfo->stu_age);
		printf("性别:%s\n",stuinfo->gender);

		printf("请输入学生的年级:");
		scanf("%d",&stuinfo->stu_grade);
		printf("年级:%d\n",stuinfo->stu_grade);

		printf("请输入学生的班级:");
		scanf("%d",&stuinfo->stu_class);
		printf("班级:%d\n",stuinfo->stu_class);

		printf("请输入学生所在的学院:");
		scanf("%s",college_name);

		//3.检查该学院是否存在
		strcpy(collegeinfo->college_name,college_name);
		bool is_college_empty = check_college_empty(collegeinfo,mysql,res,row,query);
		if(is_college_empty == true)
		{
			printf("请先进行学院信息[%s]的添加后再继续此操作\n",college_name);
		}
		else
		{
			//得到学院编号
			sprintf(query,"select college_info.college_no from college_info where college_info.college_name = \"%s\";",collegeinfo->college_name);
			printf("sql语句:%s\n",query);
			mysql_real_query(mysql,query,strlen(query));//执行sql语句
			res=mysql_store_result(mysql);//获取查询结果集
			if((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
				strcpy(stuinfo->college_no,row[0]);
			printf("学院编号:%s\n",stuinfo->college_no);

			//得到用户编号
			strcpy(stuinfo->user_no,userinfo->user_no);
			printf("用户编号:%s\n",stuinfo->user_no);

			//4.检查专业是否为空
			printf("请输入学生所在的专业:");
			scanf("%s",profs_name);
			strcpy(profsinfo->profs_name,profs_name);
			bool is_profs_empty = check_profs_empty(profsinfo,collegeinfo,mysql,res,row,query);

			if(is_profs_empty == true)
			{
				printf("请先进行学院[%s]的专业信息[%s]的添加\n",college_name,profs_name);
			}
			else
			{
				//得到专业的编号
				sprintf(query,"select profs_info.profs_no from profs_info where profs_info.profs_name = \"%s\";",profsinfo->profs_name);
				printf("sql语句:%s\n",query);
				mysql_real_query(mysql,query,strlen(query));//执行sql语句
				res=mysql_store_result(mysql);//获取查询结果集
				if((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
					strcpy(stuinfo->profs_no,row[0]);
				printf("stuinfo->college_no = %s stuinfo->profs_no = %s \n",stuinfo->college_no,stuinfo->profs_no);

				//printf("性别:%s\n",stuinfo->gender);

				//5.设置中文编码
				if(mysql_query(mysql, "set names \'utf8\'"))  //处理汉字的编码
				{
					printf("字符集:%s\n",mysql_error(mysql));
				}
				if(mysql_query(mysql,"alter table stu_info change stu_gender stu_gender varchar(4)  character  set utf8 NOT NULL;"))
				{
					printf("alter utf8 error\n");
				}


				//6.插入到数据表中,执行插入操作
				sprintf(query,"insert into stu_info(stu_no,stu_name,stu_gender,stu_age,stu_grade,stu_class,college_no,profs_no,user_no)\
						VALUES\
						(\"%s\",\"%s\",\"%s\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\",\"%s\");",\
						stuinfo->stu_no,stuinfo->stu_name,stuinfo->gender,stuinfo->stu_age,stuinfo->stu_grade,stuinfo->stu_class,stuinfo->college_no,stuinfo->profs_no,stuinfo->user_no);
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

			}//end profsinfo is not empty
		}//end collegeinfo is not empty
	}//end stuinfo is empty

	//释放内存
	free(collegeinfo);
	free(profsinfo);
}//end function



//修改学生基本信息   学生用户有此权限  管理员用户有此权限
void stuinfo_update(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	/*----------------可以修改的信息:学生的姓名  性别  年龄 年级 班级 学院 专业 -------------学号不能修改，只能让管理员先删除在添加*/
	//数据库初始化
	init_sql(res,query,row);

	//初始化结构体-----形参
	int fields = 0;
	int row_count = 0;
	int row_ops = 0;
	college_info_t  *collegeinfo =  (college_info_t*)malloc(sizeof(college_info_t)); 
	memset(collegeinfo,0,sizeof(college_info_t));
	//1.显示所有学生的基本信息
	if(logintype == LOGINTYPE_ADMIN)
	{
		sprintf(query,"select stu_info.*,college_info.college_name,profs_info.profs_name  from stu_info,college_info,profs_info\
				where stu_info.college_no = college_info.college_no and stu_info.profs_no = profs_info.profs_no;");
	}
	else if(logintype == LOGINTYPE_STUDENT)
	{
		sprintf(query,"select stu_info.*,college_info.college_name,profs_info.profs_name  from stu_info,college_info,profs_info\
				where stu_info.college_no = college_info.college_no and stu_info.profs_no = profs_info.profs_no and \
				stu_info.user_no = \"%s\";",userinfo->user_no);

	}
	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);

	//记录原来的学生基本信息
	char stuno[MAXSIZE_TABLE][9]      = {0};
	char stuname[MAXSIZE_TABLE][20]   = {0};
	char stugender[MAXSIZE_TABLE][4]  = {0};
	int  stuage[MAXSIZE_TABLE]        = {0};
	int  stugrade[MAXSIZE_TABLE]      = {0};
	int  stuclass[MAXSIZE_TABLE]      = {0};
	char collegeno[MAXSIZE_TABLE][5]  = {0};
	char profsno[MAXSIZE_TABLE][5]    = {0};
	char userno[MAXSIZE_TABLE][8]     = {0};

	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(row_count==0)
		{
			printf("数据库中学生的基本信息:\n");
			printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
			printf("| stu_no   | stu_name | stu_gender | stu_age | stu_grade | stu_class | college_no | profs_no | user_no | college_name       | profs_name               |\n");
			printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
		}
		printf("|%-12s|%-20s||%-10s|%-26s||%-9s|%-10s||%-12s|%-21s|%-15s|%-25s|%-35s|\n",\
				row[fields-11],row[fields-10],row[fields-9],row[fields-8],row[fields-7],row[fields-6],\
				row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐

		strcpy(stuno[row_count],row[fields-11]);//学号
		strcpy(stuname[row_count],row[fields-10]);//学生姓名
		strcpy(stugender[row_count],row[fields-9]);//性别
		stuage[row_count] = atoi(row[fields-8]);//年龄
		stugrade[row_count] = atoi(row[fields-7]);//年级
		stuclass[row_count] = atoi(row[fields-6]);//班级
		strcpy(collegeno[row_count],row[fields-5]);//学院编号
		strcpy(profsno[row_count],row[fields-4]);//专业编号
		strcpy(userno[row_count],row[fields-3]);//用户编号

		row_count++;
	}
	printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
	if(logintype == LOGINTYPE_ADMIN)
	{
		printf("现在有[%d]个学生的基本信息,输入你想要修改那个学生的基本信息(记录数):",row_count);
		scanf("%d",&row_ops);
		printf("你选择了学生编号[%s]学生姓名[%s]的学生\n",stuno[row_ops],stuname[row_ops]);
	}
	else if(logintype == LOGINTYPE_STUDENT)
	{
		row_ops = 0;
	}
	//2.打印选择的学生信息  并构造旧的学生信息
	printf("stuno = %s  stuname = %s stugender = %s stuage = %d stugrade = %d stuclass = %d coolegeno = %s profsno = %s userno = %s\n",\
			stuno[row_ops],stuname[row_ops],stugender[row_ops],stuage[row_ops],stugrade[row_ops],stuclass[row_ops],collegeno[row_ops],profsno[row_ops],userno[row_ops]);
	strcpy(stuinfo->stu_no,stuno[row_ops]);
	strcpy(stuinfo->stu_name,stuname[row_ops]);
	strcpy(stuinfo->gender,stugender[row_ops]);
	stuinfo->stu_age = stuage[row_ops];
	stuinfo->stu_grade = stugrade[row_ops];
	stuinfo->stu_class = stuclass[row_ops];
	strcpy(stuinfo->college_no,collegeno[row_ops]);
	strcpy(stuinfo->profs_no,profsno[row_ops]);
	strcpy(stuinfo->user_no,userno[row_ops]);

	//3..进行学生基本信息的修改  修改的同事构造新的学生信息
	char ch = 99;
	int gender = 0;
	char newcollege_name[20] = {0};
	char newcollegeno[20]={0};
	char newprofsno[MAXSIZE_TABLE][5]   = {0};
	char newprofsname[MAXSIZE_TABLE][20] = {0};
	char *pt_collegeno=newcollegeno;
	stuinfo_update_ui();
	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("请输入要修改的学生姓名:");
				scanf("%s",stuinfo->stu_name);
				printf("修改后的姓名:%s\n",stuinfo->stu_name);
				break;
			case '2':
				printf("请输入要修改的学生的性别编号(0--male,1--femal):");
				scanf("%d",&gender);
				if(gender==0)
					strcpy(stuinfo->gender,"男");
				else if(gender==1)
					strcpy(stuinfo->gender,"女");
				printf("修改后的性别:%s\n",stuinfo->gender);
				break;
			case '3':
				printf("请输入要修改的学生年龄:");
				scanf("%d",&stuinfo->stu_age);
				printf("修改后的年龄:%d\n",stuinfo->stu_age);
				break;
			case '4':
				printf("请输入要修改的学生年级:");
				scanf("%d",&stuinfo->stu_grade);
				printf("修改后的学生年级:%d\n",stuinfo->stu_grade);
				break;
			case '5':
				printf("请输入要修改的学生班级:");
				scanf("%d",&stuinfo->stu_class);
				printf("修改后的学生班级:%d\n",stuinfo->stu_class);
				break;
			case '6':
				//如果修改了该学生的学院信息，那么他/她的科目信息和科目成绩信息也会进行相应的变化，所以需要同时进行删除
				printf("请输入你想要修改的学院名称:");
				scanf("%s",newcollege_name);
				strcpy(collegeinfo->college_name,newcollege_name);
				//判断输入的学院名称是否为空
				while(check_college_empty(collegeinfo,mysql,res,row,query) == true)
				{
					printf("请重新输入学院的名称:");
					//while(getchar() != '\n');
					scanf("%s",newcollege_name);
					strcpy(collegeinfo->college_name,newcollege_name);
				}
				pt_collegeno=get_tableno(mysql,res,row,query,pt_collegeno,5,newcollege_name);//得到学院编号
				//4.根据学院编号显示专业信息  更新学生的专业信息
				row_count = 0;
				row_ops   = 0;

				sprintf(query,"select * from profs_info where profs_info.college_no = \"%s\";",stuinfo->college_no);	
				mysql_real_query(mysql,query,strlen(query));//执行数据库查询 成功返回0                                                                                                                  
				res=mysql_store_result(mysql);//获取查询结果的数据
				while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
				{
					fields=mysql_num_fields(res);
					if(row_count==0)
					{
						printf("学院专业信息:\n");
						printf("+-----------+--------------+------------+----------------+\n");
						printf("| profs_no  |  profs_name  |  college_no|  college_name  |\n");
						printf("+-----------+--------------+------------+----------------+\n");
					}
					printf("|%-11s|%-14s|%-12s|%-16s|\n",row[fields-3],row[fields-2],row[fields-1],newcollege_name);//左对齐
					strcpy(newprofsno[row_count],row[fields-3]);
					strcpy(newprofsname[row_count],row[fields-2]);
					row_count++;
				}
				printf("+---------+------------+----------+-----------+\n");

				printf("学院[%s] 现在有[%d]个专业 请选择为该学生添加的专业(记录数):",newcollege_name,row_count);
				scanf("%d",&row_ops);
				printf("你选择了学院编号[%s] 学院名称[%s] 专业编号[%s] 专业名称[%s] 的学生\n",newcollegeno,newcollege_name,newprofsno[row_ops],newprofsname[row_ops]);

				if((strcmp(stuinfo->college_no,newcollegeno)==0)&&(strcmp(stuinfo->profs_no,newprofsno[row_ops])==0))
				{
					printf("学院和专业是一样的，没有修改的必要");
				}
				else
				{
					strcpy(stuinfo->college_no,newcollegeno);
					strcpy(stuinfo->profs_no,newprofsno[row_ops]);

					//删除该学生的专业信息和科目信息
					printf("删除相关联的数据表\n");
					sprintf(query," delete stu_sub,stu_score from stu_sub left join stu_score on stu_sub.stu_no = stu_score.stu_no where stu_sub.stu_no = \"%s\";",stuinfo->stu_no);
					printf("sql语句:%s\n",query);
					if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
					{
						printf("mysql_real_query():%s\n",mysql_error(mysql));
						exit(-1);
					}
					else
					{
						printf("数据删除成功\n");
					}
				}
				break;
			default:
				break;
		}
	}

	//5.stu_info结构体检查
	printf("stuno = %s  stuname = %s stugender = %s stuage = %d stugrade = %d stuclass = %d coolegeno = %s profsno = %s userno = %s\n",\
			stuinfo->stu_no,stuinfo->stu_name,stuinfo->gender,stuinfo->stu_age,stuinfo->stu_grade,stuinfo->stu_class,stuinfo->college_no,stuinfo->profs_no,stuinfo->user_no);


	//6.stu_info数据表的更新操作
	sprintf(query,"update stu_info set stu_info.stu_no = \"%s\",stu_info.stu_name = \"%s\",stu_info.stu_gender = \"%s\",stu_info.stu_age = \"%d\",\
			stu_info.stu_grade = \"%d\",stu_info.stu_class = \"%d\",stu_info.college_no = \"%s\",stu_info.profs_no = \"%s\",stu_info.user_no = \"%s\"\
			where stu_info.stu_no = \"%s\";", stuinfo->stu_no,stuinfo->stu_name,stuinfo->gender,stuinfo->stu_age,stuinfo->stu_grade,stuinfo->stu_class,\
			stuinfo->college_no,stuinfo->profs_no,stuinfo->user_no,stuinfo->stu_no);	
	printf("SQL语句:%s\n",query);
	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("数据更新成功\n");
	}

}


//删除学生信息   管理员用户有此权限
void stuinfo_delete(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	int fields     = 0;
	int row_count  = 0;
	int row_ops    = 0;
	char stuno[MAXSIZE_TABLE][9] = {0};

	printf("\ncall %s\n",__FUNCTION__);
	if(logintype == LOGINTYPE_ADMIN)
	{
		//1.显示所有学生的记录，如果没有学生信息则不做任何动作
		if(check_stuinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype) == true)
		{
			printf("没有学生信息,请先添加学生信息\n");
		}
		else
		{
			sprintf(query,"select stu_info.*,college_info.college_name,profs_info.profs_name  from stu_info,college_info,profs_info\
					where stu_info.college_no = college_info.college_no and stu_info.profs_no = profs_info.profs_no;");
			printf("sql语句:%s\n",query);
			mysql_real_query(mysql,query,strlen(query));
			res = mysql_store_result(mysql);

			while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
			{
				fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
				if(row_count==0)
				{
					printf("数据库中学生的基本信息:\n");
					printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
					printf("| stu_no   | stu_name | stu_gender | stu_age | stu_grade | stu_class | college_no | profs_no | user_no | college_name       | profs_name               |\n");
					printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
				}
				printf("|%-12s|%-20s||%-10s|%-26s||%-9s|%-10s||%-12s|%-21s|%-15s|%-25s|%-35s|\n",\
						row[fields-11],row[fields-10],row[fields-9],row[fields-8],row[fields-7],row[fields-6],\
						row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
				strcpy(stuno[row_count],row[fields-11]);
				row_count++;
			}
			printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");

			printf("请选择你想要删除哪位学生的基本信息(记录数):\n");
			scanf("%d",&row_ops);
			printf("你选择了学号[%s]的学生\n",stuno[row_ops]);

			//2.执行删除操作
			sprintf(query,"delete from stu_info where stu_info.stu_no = \"%s\";",stuno[row_ops]);
			//执行删除
			if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
			{
				printf("mysql_real_query():%s\n",mysql_error(mysql));
				exit(-1);
			}
			else
			{
				printf("数据删除成功\n");
			}

		}
	}
	else if(logintype == LOGINTYPE_STUDENT)
	{
		printf("你是学生用户,无此权限,你讲强制退出\n");
		exit(-1);
	}

}

//修改不同学院不同专业不同学期不同学生的不同科目的信息
void stuinfo_subinfo_update(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);

	//初始化变量,结构体
	int fields    = 0;
	int row_count = 0;
	int row_ops   = 0;
	init_sql(res,query,row);

	stu_sub_t *stu_subinfo = (stu_sub_t*)malloc(sizeof(stu_sub_t));
	memset(stu_subinfo,0,sizeof(stu_sub_t));

	//一些需要从sql语句中取得的变量
	char stuno[MAXSIZE_TABLE][10]    = {0};//学号
	char stuname[MAXSIZE_TABLE][12]  = {0};//学生姓名
	char collegeno[MAXSIZE_TABLE][5] = {0};//学院编号  多加1个字节 防止字符串拷贝的时候由于数组内存连续,数组首元素会循环添加每一次拷贝的字符串
	char profsno[MAXSIZE_TABLE][5]   = {0};//专业编号
	char subno[MAXSIZE_TABLE][5]     = {0};//科目编号
	char subname[MAXSIZE_TABLE][30]  = {0};//科目名称
	char stu_subno[MAXSIZE_TABLE][5] = {0};
	char stu_subname[MAXSIZE_TABLE][30] = {0};
	char yearno[MAXSIZE_TABLE][7] = {0};
	char yearname[MAXSIZE_TABLE][22] = {0};

	//2.得到数据库中不同学院不同学期不同学生的不同科目信息
	sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
			profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
			stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3\
			from college_info,profs_info,stu_info,year_info,stu_sub\
			where college_info.college_no = stu_sub.college_no\
			and profs_info.profs_no = stu_sub.profs_no\
			and stu_info.stu_no =  stu_sub.stu_no\
			and year_info.stu_year_no =stu_sub.stu_year_no\
			GROUP BY stu_sub.stu_no;");

	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);

	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据

		if(row_count==0)
		{
			printf("数据库学生科目信息表:\n");
			printf("+----------+-----------+------------+------------------+----------+------------------+-------------+---------------------+-------------+-------------+-------------+\n");
			printf("| stu_no   | stu_name  | college_no | college_name     | profs_no | profs_name       | stu_year_no | stu_year_name       | stu_sub_no1 | stu_sub_no2 | stu_sub_no3 |+\n");
		}

		printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n",row[fields-11],row[fields-10],row[fields-9],\
				row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(collegeno[row_count],row[fields-9]);
		strcpy(profsno[row_count],row[fields-7]);
		strcpy(stuno[row_count],row[fields-11]);
		strcpy(stuname[row_count],row[fields-10]);
		strcpy(yearno[row_count],row[fields-5]);
		strcpy(yearname[row_count],row[fields-4]);
		row_count++;
	}
	printf("+----------+-----------+------------+------------------+----------+------------------+-------------+---------------------+-------------+-------------+-------------+\n");

	//3.进行更新处理的学生的选择
	printf("现在有[%d]条学生科目的信息,请选择你要更新的学生科目信息记录:\n",row_count);
	scanf("%d",&row_ops);
	printf("你选择了学生编号[%s]  学生姓名[%s] 学院编号[%s] 专业编号[%s] 学期编号[%s] 学期名称[%s]的学生科目信息\n",stuno[row_ops],stuname[row_ops],collegeno[row_ops],profsno[row_ops]\
			,yearno[row_ops],yearname[row_ops]);

	//4.得到该学生的科目数量
	int count_stusub = 0;

	for(int i=1;i<12;i++)
	{
		sprintf(query,"select stu_sub.stu_sub_no%d from stu_sub where stu_sub.stu_no = \"%s\";",i,stuno[row_ops]);
		printf("sql语句:%s\n",query);
		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		if((row=mysql_fetch_row(res)) != NULL)
		{
			if(strcmp(row[0],""))
				count_stusub ++;
		}

	}
	printf("+------------+------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+------------+-----------+------------+\n");
	printf("| sub_name1  | sub_name2  | sub_name3 | sub_name4 | sub_name5 | sub_name6 | sub_name7 | sub_name8 | sub_name9 | sub_name10 | sub_name11| sub_name12 |\n");

	printf("该学生[%s]学期有[%d]门专业课\n",yearname[row_ops],count_stusub);

	//3.显示该学生该学期的专业科目信息
	for(int i=1;i<=count_stusub;i++)
	{
		sprintf(query,"select sub_info.sub_name from sub_info,stu_sub where stu_sub.stu_sub_no%d = sub_info.sub_no  GROUP BY sub_info.sub_no;",i);
		printf("sql语句:%s\n",query);
		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		if((row=mysql_fetch_row(res)) != NULL)
		{
			printf("|%-12s|\n",row[0]);
			strcpy(stu_subname[i],row[0]);
		}
	}//end for
	printf("\n+------------+------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+------------+-----------+------------+\n");

	//4.重新设置科目信息
	sprintf(query,"select sub_info.*,profs_info.profs_name from sub_info,profs_info where sub_info.profs_no = profs_info.profs_no\
			and profs_info.college_no = \"%s\" and sub_info.profs_no = \"%s\";",collegeno[row_ops],profsno[row_ops]);
	printf("SQL语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);
	int sub_count = 0;
	int  count_stu_subinfo = 0;

	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(sub_count==0)
		{
			printf("数据库中学院编号[%s]专业编号[%s]的科目信息如下:\n",collegeno[row_ops],profsno[row_ops]);
			printf("+--------+-----------------------+----------+--------------------------+\n");
			printf("| sub_no | sub_name              | profs_no | profs_name               |\n");
			printf("+--------+-----------------------+----------+--------------------------+\n");
		}
		printf("|%-8s|%-30s|%-10s|%-26s|\n",row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(subno[sub_count],row[fields-4]);
		strcpy(subname[sub_count],row[fields-3]);
		sub_count++;
	}
	printf("+--------+-----------------------+----------+--------------------------+\n");

	printf("该学生所在专业所在专业拥有%d条科目记录\n",sub_count);
	if(sub_count == 0)
	{
		printf("该学院还没有设置科目信息,请为学院编号[%s]的专业编号[%s]添加科目信息\n",collegeno[row_ops],profsno[row_ops]);
	}
	else
	{
		for(int i = 0;i<sub_count;i++)
		{
			printf("这是科目编号[%s]科目名称[%s],你要添加么?添加请按1,不添加请按0\n",subno[i],subname[i]);
			char ch = '2';
			while(getchar()!='\n');
			if((ch=getchar())=='1')
			{
				strcpy(stu_subno[i],subno[i]);
				strcpy(stu_subname[i],subname[i]);
				count_stu_subinfo++;
			}
		}
	}

	//5.stu_sub结构体的构造
	strcpy(stu_subinfo->stu_no,stuno[row_ops]);//学号
	strcpy(stu_subinfo->stu_year_no,yearno[row_ops]);//学期
	strcpy(stu_subinfo->college_no,collegeno[row_ops]);//学院编号
	strcpy(stu_subinfo->profs_no,profsno[row_ops]);//专业编号
	for(int i=0;i<count_stu_subinfo;i++)
	{
		switch(i)
		{
			case 0:
				strcpy(stu_subinfo->stu_sub_no1,stu_subno[i]);
				break;
			case 1:
				strcpy(stu_subinfo->stu_sub_no2,stu_subno[i]);
				break;
			case 2:
				strcpy(stu_subinfo->stu_sub_no3,stu_subno[i]);
				break;
			case 3:
				strcpy(stu_subinfo->stu_sub_no4,stu_subno[i]);
				break;
			case 4:
				strcpy(stu_subinfo->stu_sub_no5,stu_subno[i]);
				break;
			case 5:
				strcpy(stu_subinfo->stu_sub_no6,stu_subno[i]);
				break;
			case 6:
				strcpy(stu_subinfo->stu_sub_no7,stu_subno[i]);
				break;
			case 7:
				strcpy(stu_subinfo->stu_sub_no8,stu_subno[i]);
				break;
			case 8:
				strcpy(stu_subinfo->stu_sub_no9,stu_subno[i]);
				break;
			case 9:
				strcpy(stu_subinfo->stu_sub_no10,stu_subno[i]);
				break;
			case 10:
				strcpy(stu_subinfo->stu_sub_no11,stu_subno[i]);
				break;
			case 11:
				strcpy(stu_subinfo->stu_sub_no12,stu_subno[i]);
				break;
			default:
				break;
		}
	}
	printf("stu_no = %s,stu_year_no = %s,college_no = %s,profs_no=%s,stu_sub_no1=%s,stu_sub_no2=%s,stu_sub_no3=%s\n",\
			stu_subinfo->stu_no,stu_subinfo->stu_year_no,stu_subinfo->college_no,stu_subinfo->profs_no,stu_subinfo->stu_sub_no1,stu_subinfo->stu_sub_no2,stu_subinfo->stu_sub_no3);

	//6.执行insert语句进行插入操作
	sprintf(query,"update stu_sub set stu_sub.stu_sub_no1 = \"%s\",stu_sub.stu_sub_no2 = \"%s\",stu_sub.stu_sub_no3 = \"%s\",stu_sub.stu_sub_no4 = \"%s\",stu_sub.stu_sub_no5 = \"%s\",\
			stu_sub.stu_sub_no6 = \"%s\",stu_sub.stu_sub_no7 = \"%s\",stu_sub.stu_sub_no8 = \"%s\",stu_sub.stu_sub_no9 = \"%s\",\
			stu_sub.stu_sub_no10 = \"%s\",stu_sub.stu_sub_no11 = \"%s\",stu_sub.stu_sub_no12 = \"%s\" where stu_sub.stu_no = \"%s\";"\
			,stu_subinfo->stu_sub_no1,stu_subinfo->stu_sub_no2,stu_subinfo->stu_sub_no3,stu_subinfo->stu_sub_no4,stu_subinfo->stu_sub_no5,stu_subinfo->stu_sub_no6,\
			stu_subinfo->stu_sub_no7,stu_subinfo->stu_sub_no8,stu_subinfo->stu_sub_no9,stu_subinfo->stu_sub_no10,\
			stu_subinfo->stu_sub_no11,stu_subinfo->stu_sub_no12,stu_subinfo->stu_no);

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


}

//删除不同学院不同专业不同学期不同学生的不同科目的信息
void stuinfo_subinfo_delete(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);

	//初始化变量,结构体
	int fields    = 0;
	int row_count = 0;
	int row_ops   = 0;
	init_sql(res,query,row);


	//一些需要从sql语句中取得的变量
	char stuno[MAXSIZE_TABLE][10]    = {0};//学号
	char stuname[MAXSIZE_TABLE][12]  = {0};//学生姓名
	char collegeno[MAXSIZE_TABLE][5] = {0};//学院编号  多加1个字节 防止字符串拷贝的时候由于数组内存连续,数组首元素会循环添加每一次拷贝的字符串
	char profsno[MAXSIZE_TABLE][5]   = {0};//专业编号
	char yearno[MAXSIZE_TABLE][7] = {0};
	char yearname[MAXSIZE_TABLE][22] = {0};

	//2.得到数据库中不同学院不同学期不同学生的不同科目信息
	sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
			profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
			stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3\
			from college_info,profs_info,stu_info,year_info,stu_sub\
			where college_info.college_no = stu_sub.college_no\
			and profs_info.profs_no = stu_sub.profs_no\
			and stu_info.stu_no =  stu_sub.stu_no\
			and year_info.stu_year_no =stu_sub.stu_year_no\
			GROUP BY stu_sub.stu_no;");

	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);

	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据

		if(row_count==0)
		{
			printf("数据库学生科目信息表:\n");
			printf("+----------+-----------+------------+------------------+----------+------------------+-------------+---------------------+-------------+-------------+-------------+\n");
			printf("| stu_no   | stu_name  | college_no | college_name     | profs_no | profs_name       | stu_year_no | stu_year_name       | stu_sub_no1 | stu_sub_no2 | stu_sub_no3 |+\n");
		}

		printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n",row[fields-11],row[fields-10],row[fields-9],\
				row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(collegeno[row_count],row[fields-9]);
		strcpy(profsno[row_count],row[fields-7]);
		strcpy(stuno[row_count],row[fields-11]);
		strcpy(stuname[row_count],row[fields-10]);
		strcpy(yearno[row_count],row[fields-5]);
		strcpy(yearname[row_count],row[fields-4]);
		row_count++;
	}
	printf("+----------+-----------+------------+------------------+----------+------------------+-------------+---------------------+-------------+-------------+-------------+\n");

	//3.进行更新处理的学生的选择
	printf("现在有[%d]条学生科目的信息,请选择你要更新的学生科目信息记录:\n",row_count);
	scanf("%d",&row_ops);
	printf("你选择了学生编号[%s]  学生姓名[%s] 学院编号[%s] 专业编号[%s] 学期编号[%s] 学期名称[%s]的学生科目信息\n",stuno[row_ops],stuname[row_ops],collegeno[row_ops],profsno[row_ops]\
			,yearno[row_ops],yearname[row_ops]);

	//4.进行删除处理
	sprintf(query,"delete from stu_sub where stu_sub.stu_no = \"%s\";",stuno[row_ops]);

	printf("sql语句:%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("数据删除成功\n");
	}
}

//查询不同学院不同专业不同学期不同学生的不同科目的信息
void stuinfo_subinfo_select(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	int fields = 0;
	int row_count = 0;
	init_sql(res,query,row);

	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
	if(check_stuinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
	{
		printf("学生基本信息表中没有数据,请先添加学生基本信息\n");
		stuinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
	}
	else
	{
		printf("学生基本信息表中有数据\n");

		//2.stu_sub检查
		if(check_stusubinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
		{
			printf("学生科目表中没有数据,请先添加学生学期科目信息\n");
		}
		else
		{
			if(logintype == LOGINTYPE_STUDENT)//学生用户只能查询自己的信息
			{
				sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
						profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
						stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3\
						from college_info,profs_info,stu_info,year_info,stu_sub\
						where college_info.college_no = stu_sub.college_no\
						and profs_info.profs_no = stu_sub.profs_no\
						and stu_info.stu_no =  stu_sub.stu_no\
						and year_info.stu_year_no =stu_sub.stu_year_no\
						and stu_info.stu_no = \"%s\" GROUP BY stu_sub.stu_no;",stuinfo->stu_no);
			}
			else if(logintype == LOGINTYPE_ADMIN)//管理员用户可以查询相同学院相同专业学生的科目信息  也可以查询全部结果 也即查询方式可以不同  这部分业务逻辑可以添加与修改
			{
				sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
						profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
						stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3\
						from college_info,profs_info,stu_info,year_info,stu_sub\
						where college_info.college_no = stu_sub.college_no\
						and profs_info.profs_no = stu_sub.profs_no\
						and stu_info.stu_no =  stu_sub.stu_no\
						and year_info.stu_year_no =stu_sub.stu_year_no\
						GROUP BY stu_sub.stu_no;");
			}

			mysql_real_query(mysql,query,strlen(query));
			res = mysql_store_result(mysql);

			//获取数据集  char**类型  每一行的数据
			while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
			{
				fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据

				if(row_count==0)
				{
					printf("数据库学生科目信息表:\n");
					printf("+----------+-----------+------------+------------------+----------+------------------+-------------+---------------------+-------------+-------------+-------------+\n");
				}

				printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n",row[fields-11],row[fields-10],row[fields-9],\
						row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
				row_count++;
			}
			printf("+----------+-----------+------------+------------------+----------+------------------+-------------+---------------------+-------------+-------------+-------------+\n");

			printf("sizeof(query) = %ld \n",strlen(query));
		}
	}
}
//添加不同学院不同专业学生不同学期的科目信息    判断是否未满-----------------?????????????  一些局部变量可以不需要  减少内存
void stuinfo_subinfo_insert(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	if(logintype == LOGINTYPE_STUDENT)
	{
		printf("你是学生用户,无此权限,你讲强制退出\n");
		exit(-1);
	}
	else
	{
		init_sql(res,query,row);

		//变量声明初始化
		stu_sub_t *stu_subinfo = (stu_sub_t*)malloc(sizeof(stu_sub_t));//初始化结构体对象,并分配内存
		memset(stu_subinfo,0,sizeof(stu_sub_t));

		sprintf(query,"select * from stu_info;");
		//1.查询学生基本信息表中学生信息的记录
		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		int row_count = 0;
		int fields    = 0;
		int row_ops   = 0;

		/*将数据结合中的数据放在局部二维字符数组中*/
		char stuno[MAXSIZE_TABLE][10]    = {0};//学号
		char stuname[MAXSIZE_TABLE][12]  = {0};//学生姓名
		char collegeno[MAXSIZE_TABLE][5] = {0};//学院编号  多加1个字节 防止字符串拷贝的时候由于数组内存连续,数组首元素会循环添加每一次拷贝的字符串
		char profsno[MAXSIZE_TABLE][5]   = {0};//专业编号
		char subno[MAXSIZE_TABLE][5]     = {0};//科目编号
		char subname[MAXSIZE_TABLE][30]  = {0};//科目名称

		//获取数据集  char**类型  每一行的数据
		while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
		{
			fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
			printf("fields = %d\n",fields);
			if(row_count==0)
			{
				printf("数据库学生基本信息表中含有的学生信息:\n");
				printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+\n");
				printf("| stu_no   | stu_name | stu_gender | stu_age | stu_grade | stu_class | college_no | profs_no | user_no |\n");
				printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+\n");
			}
			printf("|%-9s|%-10s|%-12s|%-9s|%-10s|%-10s|%-9s|%-10s|%-10s|\n",row[fields-9],row[fields-8],row[fields-7],row[fields-6],row[fields-5]\
					,row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
			strcpy(stuno[row_count],row[fields-9]);
			strcpy(stuname[row_count],row[fields-8]);
			strcpy(collegeno[row_count],row[fields-3]);
			strcpy(profsno[row_count],row[fields-2]);

			row_count++;
		}
		printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+\n");

		printf("stuno[0] = %s stuno[1] = %s stuno[2] = %s\n",stuno[0],stuno[1],stuno[2]);


		printf("请选择为哪位学生进行科目信息的添加(输入记录数):");
		scanf("%d",&row_ops);
		printf("选择学院编号[%s]专业编号[%s]的学号[%s]学生姓名[%s]的学生\n",collegeno[row_ops],profsno[row_ops],stuno[row_ops],stuname[row_ops]);

		//2.检查学生科目信息表中是否含有该学生的数据   通过学号
		strcpy(stuinfo->stu_no,stuno[row_ops]);//学号
		if(check_stusubinfo_empty_bystuno(stuinfo,mysql,res,row,query) == false)
		{
			printf("数据库中学生科目信息表中已经含有该学生的科目数据,不能重复添加\n");	
		}
		else
		{

			//2.得到该学生的科目数据集
			sprintf(query,"select sub_info.*,profs_info.profs_name from sub_info,profs_info where sub_info.profs_no = profs_info.profs_no\
					and profs_info.college_no = \"%s\" and sub_info.profs_no = \"%s\";",collegeno[row_ops],profsno[row_ops]);
			printf("SQL语句:%s\n",query);
			mysql_real_query(mysql,query,strlen(query));
			res = mysql_store_result(mysql);
			int sub_count = 0;


			while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
			{
				fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
				if(sub_count==0)
				{
					printf("数据库中学院编号[%s]专业编号[%s]的科目信息如下:\n",collegeno[row_ops],profsno[row_ops]);
					printf("+--------+-----------------------+----------+--------------------------+\n");
					printf("| sub_no | sub_name              | profs_no | profs_name               |\n");
					printf("+--------+-----------------------+----------+--------------------------+\n");
				}
				printf("|%-8s|%-30s|%-10s|%-26s|\n",row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
				strcpy(subno[sub_count],row[fields-4]);
				strcpy(subname[sub_count],row[fields-3]);
				sub_count++;
			}
			printf("+--------+-----------------------+----------+--------------------------+\n");

			printf("该学生所在专业所在专业拥有%d条科目记录\n",sub_count);
			if(sub_count == 0)
			{
				printf("该学院还没有设置科目信息,请为学院编号[%s]的专业编号[%s]添加科目信息\n",collegeno[row_ops],profsno[row_ops]);
			}
			else
			{
				//定义存放用户学选择添加的科目编号 和 科目名称
				char stu_subno[MAXSIZE_TABLE][5] = {0};
				char stu_subname[MAXSIZE_TABLE][30] = {0};
				int  count_stu_subinfo = 0;
				for(int i = 0;i<sub_count;i++)
				{
					printf("这是科目编号[%s]科目名称[%s],你要添加么?添加请按1,不添加请按0\n",subno[i],subname[i]);
					char ch = '2';
					while(getchar()!='\n');
					if((ch=getchar())=='1')
					{
						strcpy(stu_subno[i],subno[i]);
						strcpy(stu_subname[i],subname[i]);
						count_stu_subinfo++;
					}
				}

				//3.根据该学院该专业的科目信息为该学生添加本学期的科目表 
				int count_yearinfo = 0;
				char yearno[MAXSIZE_TABLE][7] = {0};
				char yearname[MAXSIZE_TABLE][22] = {0};

				//查询数据库得到学期信息表
				sprintf(query,"select * from year_info;");
				printf("SQL语句:%s\n",query);
				mysql_real_query(mysql,query,strlen(query));
				res = mysql_store_result(mysql);
				row_count = 0;

				while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
				{
					fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
					if(row_count==0)
					{
						printf("数据库中学期信息:\n");
						printf("+-------------+---------------------+\n");
						printf("| stu_year_no | stu_year_name       |\n");
						printf("+-------------+---------------------+\n");
					}
					printf("|%-13s|%-25s|\n",row[fields-2],row[fields-1]);//左对齐
					strcpy(yearno[row_count],row[fields-2]);
					strcpy(yearname[row_count],row[fields-1]);
					row_count++;
				}
				printf("+-------------+---------------------+\n");

				printf("yearno[0] = %s,yearno[1] =%s,yearno[2] =%s,yearno[3] =%s\n",yearno[0],yearno[1],yearno[2],yearno[3]);
				//得到选择的学期信息
				printf("请输入你要添加的学期(输入记录数):");
				scanf("%d",&count_yearinfo);
				printf("选择了学期编号[%s]学期名称[%s]\n",yearno[count_yearinfo],yearname[count_yearinfo]);
				printf("stuno[0] = %s stuno[1] = %s stuno[2] = %s\n",stuno[0],stuno[1],stuno[2]);


				//4.构造stu_sub表的结构体
				strcpy(stu_subinfo->stu_no,stuno[row_ops]);//学号
				strcpy(stu_subinfo->stu_year_no,yearno[count_yearinfo]);//学期
				strcpy(stu_subinfo->college_no,collegeno[row_ops]);//学院编号
				strcpy(stu_subinfo->profs_no,profsno[row_ops]);//专业编号
				printf("添加的科目记录条数:%d\n",count_stu_subinfo);
				for(int i=0;i<count_stu_subinfo;i++)
				{
					switch(i)
					{
						case 0:
							strcpy(stu_subinfo->stu_sub_no1,stu_subno[i]);
							break;
						case 1:
							strcpy(stu_subinfo->stu_sub_no2,stu_subno[i]);
							break;
						case 2:
							strcpy(stu_subinfo->stu_sub_no3,stu_subno[i]);
							break;
						case 3:
							strcpy(stu_subinfo->stu_sub_no4,stu_subno[i]);
							break;
						case 4:
							strcpy(stu_subinfo->stu_sub_no5,stu_subno[i]);
							break;
						case 5:
							strcpy(stu_subinfo->stu_sub_no6,stu_subno[i]);
							break;
						case 6:
							strcpy(stu_subinfo->stu_sub_no7,stu_subno[i]);
							break;
						case 7:
							strcpy(stu_subinfo->stu_sub_no8,stu_subno[i]);
							break;
						case 8:
							strcpy(stu_subinfo->stu_sub_no9,stu_subno[i]);
							break;
						case 9:
							strcpy(stu_subinfo->stu_sub_no10,stu_subno[i]);
							break;
						case 10:
							strcpy(stu_subinfo->stu_sub_no11,stu_subno[i]);
							break;
						case 11:
							strcpy(stu_subinfo->stu_sub_no12,stu_subno[i]);
							break;
						default:
							break;
					}
				}

				//5.test 
				printf("stu_no = %s,stu_year_no = %s,college_no = %s,profs_no=%s,stu_sub_no1=%s,stu_sub_no2=%s,stu_sub_no3=%s\n",\
						stu_subinfo->stu_no,stu_subinfo->stu_year_no,stu_subinfo->college_no,stu_subinfo->profs_no,stu_subinfo->stu_sub_no1,stu_subinfo->stu_sub_no2,stu_subinfo->stu_sub_no3);

				//6.执行insert语句进行插入操作
				sprintf(query,"insert into stu_sub(stu_no,stu_year_no,stu_sub_no1,stu_sub_no2,stu_sub_no3,stu_sub_no4,stu_sub_no5,\
					stu_sub_no6,stu_sub_no7,stu_sub_no8,stu_sub_no9,stu_sub_no10,stu_sub_no11,stu_sub_no12,college_no,profs_no)\
					VALUES(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");"\
					,stu_subinfo->stu_no,stu_subinfo->stu_year_no,stu_subinfo->stu_sub_no1,stu_subinfo->stu_sub_no2,\
					stu_subinfo->stu_sub_no3,stu_subinfo->stu_sub_no4,stu_subinfo->stu_sub_no5,stu_subinfo->stu_sub_no6,
					stu_subinfo->stu_sub_no7,stu_subinfo->stu_sub_no8,stu_subinfo->stu_sub_no9,stu_subinfo->stu_sub_no10,
					stu_subinfo->stu_sub_no11,stu_subinfo->stu_sub_no12,stu_subinfo->college_no,stu_subinfo->profs_no);

				printf("sql语句:%s\n",query);

				if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
				{
					printf("mysql_real_query():%s\n",mysql_error(mysql));
					exit(-1);
				}
				else
				{
					printf("数据插入成功\n");
				}
			}//end stu subinfo is empty
		}
		//7.释放内存
		free(stu_subinfo);
	}
}


//修改不同学院不同专业不同学期不同学生的不同科目的成绩信息
void stuinfo_subscore_update(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
	init_sql(res,query,row);

	//变量的初始化
	int fields = 0;
	int row_count = 0;
	int row_ops   = 0;
	//一些需要从sql语句中取得的变量
	char stuno[MAXSIZE_TABLE][10]    = {0};//学号
	char stuname[MAXSIZE_TABLE][12]  = {0};//学生姓名
	char collegeno[MAXSIZE_TABLE][5] = {0};//学院编号  多加1个字节 防止字符串拷贝的时候由于数组内存连续,数组首元素会循环添加每一次拷贝的字符串
	char profsno[MAXSIZE_TABLE][5]   = {0};//专业编号
	char stu_subno[12][5]			 = {0};
	char stu_subname[12][30]         = {0};
	int  stu_score[12]               = {0};
	char yearno[MAXSIZE_TABLE][7]    = {0};
	char yearname[MAXSIZE_TABLE][22] = {0};

	//结构体的初始化
	stu_score_t* stu_scoreinfo = malloc(sizeof(stu_score_t));
	memset(stu_scoreinfo,0,sizeof(stu_score_t));
	//1.得到所有学生的科目成绩信息
	sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
			profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
			stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3,stu_score.sub_no1_sc,stu_score.sub_no2_sc,stu_score.sub_no3_sc\
			from college_info,profs_info,stu_info,year_info,stu_sub,stu_score\
			where college_info.college_no = stu_sub.college_no\
			and profs_info.profs_no = stu_sub.profs_no\
			and stu_info.stu_no =  stu_sub.stu_no\
			and stu_info.stu_no =  stu_score.stu_no\
			and year_info.stu_year_no =stu_sub.stu_year_no\
			GROUP BY stu_sub.stu_no;");
	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);

	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据

		if(row_count==0)
		{
			printf("数据库学生科目成绩信息表:\n");
			printf("+------+--------+----------+------------+----------+-----------+-------------+-------------+------------+-----------+-----------+-----------+----------+------------+\n");
			printf("|stu_no|stu_name|college_no|college_name|profs_no  |profs_name | stu_year_no |stu_year_name| stu_sub_no1|stu_sub_no2|stu_sub_no3|sub_no1_sc |sub_no2_sc| sub_no3_sc |\n");
		}

		printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n",row[fields-14],row[fields-13],row[fields-12],row[fields-11],row[fields-10],row[fields-9],\
				row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		printf("+------+--------+----------+------------+----------+-----------+-------------+-------------+------------+-----------+-----------+-----------+----------+------------+\n");
		strcpy(stuno[row_count],row[fields-14]);
		strcpy(stuname[row_count],row[fields-13]);
		strcpy(collegeno[row_count],row[fields-12]);
		strcpy(profsno[row_count],row[fields-10]);
		strcpy(yearno[row_count],row[fields-8]);
		strcpy(yearname[row_count],row[fields-7]);
		row_count++;
	}
	printf("+------+------+-------+-----------+----------+-----------+-------------+-----------+---------+--------+---------+-----------+----------+------------+\n");
	printf("sizeof(query) = %ld \n",strlen(query));

	//2.选择某一个学生  得到该学生的科目信息和成绩信息
	printf("现在有[%d]条学生科目成绩的信息,请选择你要更新的学生科目成绩信息记录:\n",row_count);
	scanf("%d",&row_ops);
	printf("你选择了学生编号[%s]  学生姓名[%s] 学院编号[%s] 专业编号[%s] 学期编号[%s] 学期名称[%s]的学生科目成绩信息\n",stuno[row_ops],stuname[row_ops],collegeno[row_ops],profsno[row_ops]\
			,yearno[row_ops],yearname[row_ops]);

	//4.得到该学生的科目数量
	int count_stusub = getstusubCount(mysql,res,row,query,stuno[row_ops]);
	printf("该学生[%s]学期有[%d]门专业课\n",yearname[row_ops],count_stusub);

	//3.显示该学生该学期的专业科目信息与科目成绩信息
	for(int i=1;i<=count_stusub;i++)
	{
		sprintf(query,"select sub_info.sub_no,sub_info.sub_name,stu_score.sub_no%d_sc from sub_info,stu_sub,stu_score where stu_sub.stu_sub_no%d = sub_info.sub_no\
				and   stu_sub.stu_no  = stu_score.stu_no and   stu_score.stu_no = \"%s\";",i,i,stuno[row_ops]);

		//printf("sql语句:%s\n",query);
		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		if((row=mysql_fetch_row(res)) != NULL)
		{
			printf("|%-12s|%-12s|%-12d|\n",row[0],row[1],atoi(row[2]));
			strcpy(stu_subno[i],row[0]);
			strcpy(stu_subname[i],row[1]);
			stu_score[i] = atoi(row[2]);
		}
	}//end for
	printf("+------------+------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+------------+-----------+------------+\n");

	//4.得到科目成绩信息
	int count_subscore = 0;
	char ch = '2';
	while(count_subscore < count_stusub)
	{       printf("得到旧的成绩\n");
		switch(count_subscore)
		{
			case 0:
				stu_scoreinfo->sub_no1_sc = stu_score[count_subscore+1];
				break;
			case 1:
				stu_scoreinfo->sub_no2_sc = stu_score[count_subscore+1];
				break;
			case 2:
				stu_scoreinfo->sub_no3_sc = stu_score[count_subscore+1];
				break;
			case 3:
				stu_scoreinfo->sub_no4_sc = stu_score[count_subscore+1];
				break;
			case 4:
				stu_scoreinfo->sub_no5_sc = stu_score[count_subscore+1];
				break;
			case 5:
				stu_scoreinfo->sub_no6_sc = stu_score[count_subscore+1];
				break;
			case 6:
				stu_scoreinfo->sub_no7_sc = stu_score[count_subscore+1];
				break;
			case 7:
				stu_scoreinfo->sub_no8_sc = stu_score[count_subscore+1];
				break;
			case 8:
				stu_scoreinfo->sub_no9_sc = stu_score[count_subscore+1];
				break;
			case 9:
				stu_scoreinfo->sub_no10_sc = stu_score[count_subscore+1];
				break;
			case 10:
				stu_scoreinfo->sub_no11_sc = stu_score[count_subscore+1];
				break;
			case 11:
				stu_scoreinfo->sub_no12_sc = stu_score[count_subscore+1];
				break;
			default:
				break;
		}
		//显示该学生该科目现在的成绩,并根据选择设置新的科目成绩
		printf("该学生[%s]的科目%d是[%s] 成绩是[%d]\n",stuname[row_ops],count_subscore+1,stu_subname[count_subscore+1],stu_score[count_subscore+1]);
		printf("你是否想为科目[%s]设置新的成绩(0-100),如果想,请输入1,否则输入0:\n",stu_subname[count_subscore+1]);
		while(getchar()!='\n');
		if((ch=getchar())=='1')
		{
			printf("请输入新的成绩:");
			switch(count_subscore)
			{
				case 0:
					scanf("%d",&stu_scoreinfo->sub_no1_sc);
					break;
				case 1:
					scanf("%d",&stu_scoreinfo->sub_no2_sc);
					break;
				case 2:
					scanf("%d",&stu_scoreinfo->sub_no3_sc);
					break;
				case 3:
					scanf("%d",&stu_scoreinfo->sub_no4_sc);
					break;
				case 4:
					scanf("%d",&stu_scoreinfo->sub_no5_sc);
					break;
				case 5:
					scanf("%d",&stu_scoreinfo->sub_no6_sc);
					break;
				case 6:
					scanf("%d",&stu_scoreinfo->sub_no7_sc);
					break;
				case 7:
					scanf("%d",&stu_scoreinfo->sub_no8_sc);
					break;
				case 8:
					scanf("%d",&stu_scoreinfo->sub_no9_sc);
					break;
				case 9:
					scanf("%d",&stu_scoreinfo->sub_no10_sc);
					break;
				case 10:
					scanf("%d",&stu_scoreinfo->sub_no11_sc);
					break;
				case 11:
					scanf("%d",&stu_scoreinfo->sub_no12_sc);
					break;
				default:
					break;
			}//end switch
		}
		count_subscore ++;
	}

	//6.test 新的科目成绩
	printf("score1 = %d  score2 = %d score3 = %d   score4 = %d score5 = %d score6 = %d score7 = %d score8 = %d score9 = %d score10 = %d  score11 = %d score12 = %d \n",\
			stu_scoreinfo->sub_no1_sc,stu_scoreinfo->sub_no2_sc,stu_scoreinfo->sub_no3_sc,stu_scoreinfo->sub_no4_sc,stu_scoreinfo->sub_no5_sc,stu_scoreinfo->sub_no6_sc,\
			stu_scoreinfo->sub_no7_sc,stu_scoreinfo->sub_no8_sc,stu_scoreinfo->sub_no9_sc,stu_scoreinfo->sub_no10_sc,stu_scoreinfo->sub_no11_sc,stu_scoreinfo->sub_no12_sc);

	//7.更新数据库学生科目成绩表
	sprintf(query,"update stu_score set stu_score.sub_no1_sc = \"%d\",stu_score.sub_no2_sc = \"%d\",stu_score.sub_no3_sc = \"%d\",stu_score.sub_no4_sc = \"%d\",\
			stu_score.sub_no5_sc = \"%d\",stu_score.sub_no6_sc = \"%d\",stu_score.sub_no7_sc = \"%d\",stu_score.sub_no8_sc = \"%d\",stu_score.sub_no9_sc = \"%d\",\
			stu_score.sub_no10_sc = \"%d\",stu_score.sub_no11_sc = \"%d\",stu_score.sub_no12_sc = \"%d\" where stu_score.stu_no = \"%s\";",stu_scoreinfo->sub_no1_sc,\
			stu_scoreinfo->sub_no2_sc,stu_scoreinfo->sub_no3_sc,stu_scoreinfo->sub_no4_sc,stu_scoreinfo->sub_no5_sc,stu_scoreinfo->sub_no6_sc,\
			stu_scoreinfo->sub_no7_sc,stu_scoreinfo->sub_no8_sc,stu_scoreinfo->sub_no9_sc,stu_scoreinfo->sub_no10_sc,stu_scoreinfo->sub_no11_sc,stu_scoreinfo->sub_no12_sc,stuno[row_ops]);
	printf("sql语句:%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
    {
        printf("mysql_real_query():%s\n",mysql_error(mysql));
        exit(-1);
    }
    else
    {
        printf("mysql_real_query() sucess!!! 更新数据成功\n");
    }

}

//删除不同学院不同专业不同学期不同学生的不同科目的成绩信息
void stuinfo_subscore_delete(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
	int fields = 0;
	int row_count = 0;
	int row_ops   = 0;
	char stuno[MAXSIZE_TABLE][10]    = {0};//学号
	char stuname[MAXSIZE_TABLE][12]  = {0};//学生姓名
	init_sql(res,query,row);

	//1.得到所有学生的科目成绩信息
	sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
			profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
			stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3,stu_score.sub_no1_sc,stu_score.sub_no2_sc,stu_score.sub_no3_sc\
			from college_info,profs_info,stu_info,year_info,stu_sub,stu_score\
			where college_info.college_no = stu_sub.college_no\
			and profs_info.profs_no = stu_sub.profs_no\
			and stu_info.stu_no =  stu_sub.stu_no\
			and stu_info.stu_no =  stu_score.stu_no\
			and year_info.stu_year_no =stu_sub.stu_year_no\
			GROUP BY stu_sub.stu_no;");
	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);

	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据

		if(row_count==0)
		{
			printf("数据库学生科目成绩信息表:\n");
			printf("+------+--------+----------+------------+----------+-----------+-------------+-------------+------------+-----------+-----------+-----------+----------+------------+\n");
			printf("|stu_no|stu_name|college_no|college_name|profs_no  |profs_name | stu_year_no |stu_year_name| stu_sub_no1|stu_sub_no2|stu_sub_no3|sub_no1_sc |sub_no2_sc| sub_no3_sc |\n");
		}

		printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n",row[fields-14],row[fields-13],row[fields-12],row[fields-11],row[fields-10],row[fields-9],\
				row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		printf("+------+--------+----------+------------+----------+-----------+-------------+-------------+------------+-----------+-----------+-----------+----------+------------+\n");
		strcpy(stuno[row_count],row[fields-14]);
		strcpy(stuname[row_count],row[fields-13]);
		row_count++;
	}
	printf("+------+------+-------+-----------+----------+-----------+-------------+-----------+---------+--------+---------+-----------+----------+------------+\n");

	printf("sizeof(query) = %ld \n",strlen(query));

	//2.选择要删除的记录条数
	printf("现在有[%d]条学生科目成绩信息,选择你想要删除的学生科目成绩信息:",row_count);
	scanf("%d",&row_ops);
	while(row_ops>=row_count)
	{
		printf("记录数越界,请重新输入\n");
		while(getchar()!='\n');//清楚键盘输入多个字符
		scanf("%d",&row_ops);
	}
	printf("你选择了学生编号[%s] 学生姓名[%s]的学生信息\n",stuno[row_ops],stuname[row_ops]);

	//3.执行删除操作
	sprintf(query,"delete from stu_score where stu_score.stu_no = \"%s\";",stuno[row_ops]);
	printf("sql语句:%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("数据删除成功\n");
	}

}

//查询不同学院不同专业不同学期不同学生的不同科目的成绩信息
void stuinfo_subscore_select(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
	int fields = 0;
	int row_count = 0;
	init_sql(res,query,row);
	//1.stu_info检查
	if(check_stuinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
	{
		printf("学生基本信息表中没有数据,请先添加学生基本信息\n");
	}
	else
	{
		printf("学生基本信息表中有数据\n");
		//2.stu_sub检查
		if(check_stusubinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
		{
			printf("学生科目表中没有数据,请先添加学生学期科目信息\n");
			stuinfo_subinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
		}
		else
		{
			printf("学生科目表中有数据\n");
			//3.stu_score检查
			if(check_stuscoreinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
			{
				printf("学生成绩表中没有数据，请先添加学生学科目成绩信息\n");
			}
			else
			{
				printf("学生成绩表中有数据\n");
				if(logintype == LOGINTYPE_STUDENT)//学生用户只能查询自己的信息
				{
					sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
							profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
							stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3,stu_score.sub_no1_sc,stu_score.sub_no2_sc,stu_score.sub_no3_sc\
							from college_info,profs_info,stu_info,year_info,stu_sub,stu_score\
							where college_info.college_no = stu_sub.college_no\
							and profs_info.profs_no = stu_sub.profs_no\
							and stu_info.stu_no =  stu_sub.stu_no\
							and stu_info.stu_no =  stu_score.stu_no\
							and year_info.stu_year_no =stu_sub.stu_year_no\
							and stu_info.stu_no = \"%s\"\
							GROUP BY stu_sub.stu_no;",stuinfo->stu_no);
				}
				else if(logintype == LOGINTYPE_ADMIN)//管理员用户可以查询相同学院相同专业学生的科目信息  也可以查询全部结果 也即查询方式可以不同  这部分业务逻辑可以添加与修改
				{
					sprintf(query,"select stu_info.stu_no,stu_info.stu_name,college_info.college_no,college_info.college_name,\
							profs_info.profs_no,profs_info.profs_name,year_info.stu_year_no,year_info.stu_year_name,\
							stu_sub.stu_sub_no1,stu_sub.stu_sub_no2,stu_sub.stu_sub_no3,stu_score.sub_no1_sc,stu_score.sub_no2_sc,stu_score.sub_no3_sc\
							from college_info,profs_info,stu_info,year_info,stu_sub,stu_score\
							where college_info.college_no = stu_sub.college_no\
							and profs_info.profs_no = stu_sub.profs_no\
							and stu_info.stu_no =  stu_sub.stu_no\
							and stu_info.stu_no =  stu_score.stu_no\
							and year_info.stu_year_no =stu_sub.stu_year_no\
							GROUP BY stu_sub.stu_no;");
				}

				mysql_real_query(mysql,query,strlen(query));
				res = mysql_store_result(mysql);
				printf("sql语句:%s\n",query);
				//获取数据集  char**类型  每一行的数据
				while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
				{
					fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据

					if(row_count==0)
					{
						printf("数据库学生科目成绩信息表:\n");
						printf("+------+------+-------+-----------+----------+-----------+-------------+-----------+---------+--------+---------+-----------+----------+------------+\n");
						printf("|stu_no|stu_name|college_no|college_name|profs_no  |profs_name | stu_year_no |stu_year_name| stu_sub_no1|stu_sub_no2|\
								stu_sub_no3|sub_no1_sc |sub_no2_sc| sub_no3_sc |\n");
					}

					printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n",\
							row[fields-14],row[fields-13],row[fields-12],row[fields-11],row[fields-10],row[fields-9],\
							row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
					printf("+------+------+-------+-----------+----------+-----------+-------------+-----------+---------+--------+---------+-----------+----------+------------+\n");
					row_count++;
				}
				printf("+------+------+-------+-----------+----------+-----------+-------------+-----------+---------+--------+---------+-----------+----------+------------+\n");

				printf("sizeof(query) = %ld \n",strlen(query));

			}
		}
	}
}
//添加不同学院不同专业不同学期不同学生的不同科目的成绩信息     判断是否为满   ---------?????
void stuinfo_subscore_insert(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
	//数据库变量的初始化
	init_sql(res,query,row);
	if(logintype == LOGINTYPE_STUDENT)
	{
		printf("你是学生用户,你没有权限的进行成绩的添加,强制退出系统\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		//结构体变量的初始化
		stu_score_t *stu_scoreinfo  = (stu_score_t*) malloc(sizeof(stu_score_t));
		memset(stu_scoreinfo,0,sizeof(stu_score_t));

		//1.通过学生科目表得到该学生的基本信息
		sprintf(query,"select college_info.college_no,college_info.college_name,profs_info.profs_no,profs_info.profs_name,\
				stu_info.stu_no,stu_info.stu_name,year_info.stu_year_no,year_info.stu_year_name\
				from college_info,profs_info,stu_info,year_info,stu_sub\
				where college_info.college_no = stu_sub.college_no \
				and profs_info.profs_no = stu_sub.profs_no\
				and stu_info.stu_no =  stu_sub.stu_no\
				and year_info.stu_year_no =stu_sub.stu_year_no\
				GROUP BY stu_sub.stu_no;");

		mysql_real_query(mysql,query,strlen(query));
		res = mysql_store_result(mysql);
		int row_count = 0;
		int fields    = 0;
		char stuno[MAXSIZE_TABLE][10]    = {0};//学号
		//char stuname[MAXSIZE_TABLE][12]  = {0};//学生姓名
		char collegeno[MAXSIZE_TABLE][5] = {0};//学院编号  多加1个字节 防止字符串拷贝的时候由于数组内存连续,数组首元素会循环添加每一次拷贝的字符串
		char profsno[MAXSIZE_TABLE][5]   = {0};//专业编号
	//	char subno[MAXSIZE_TABLE][5]     = {0};//科目编号
		//char subname[MAXSIZE_TABLE][30]  = {0};//科目名称
		//char stu_subno[MAXSIZE_TABLE][5] = {0};
		char stusubname[MAXSIZE_TABLE][30] = {0};
		char yearno[MAXSIZE_TABLE][7] = {0};
		char yearname[MAXSIZE_TABLE][22] = {0};

		while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
		{
			fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
			if(row_count==0)
			{
				printf("数据库中学生的基本信息:\n");
				printf("+------------+--------------------+----------+--------------------------+----------+----------+-------------+---------------------+\n");
				printf("| college_no | college_name       | profs_no | profs_name               | stu_no   | stu_name | stu_year_no | stu_year_name       |\n");
				printf("+------------+--------------------+----------+--------------------------+----------+----------+-------------+---------------------+\n");
			}
			printf("|%-12s|%-20s||%-10s|%-26s||%-9s|%-10s||%-12s|%-21s|\n",row[fields-8],row[fields-7],row[fields-6],row[fields-5],row[fields-4],row[fields-3],\
					row[fields-2],row[fields-1]);//左对齐

			strcpy(collegeno[row_count],row[fields-8]);
			strcpy(profsno[row_count],row[fields-6]);
			strcpy(stuno[row_count],row[fields-4]);
			strcpy(yearno[row_count],row[fields-2]);
			strcpy(yearname[row_count],row[fields-1]);
			row_count++;
		}
		printf("+------------+--------------------+----------+--------------------------+----------+----------+-------------+---------------------+\n");

		for(int i=0;i<row_count;i++)
			printf("stu_no = %s,stu_year_no = %s,college_no = %s,profs_no=%s\n",stuno[i],yearno[i],collegeno[i],profsno[i]);


		int row_ops = 0;
		printf("共有[%d]位学生的基本信息,请选择为哪位学生的哪个学期进行成绩的添加:",row_count);
		scanf("%d",&row_ops);
		printf("你选择了学院编号[%s]专业编号[%s]学号[%s]学期[%s]的学生\n",collegeno[row_ops],profsno[row_ops],stuno[row_ops],yearno[row_ops]);
		strcpy(stuinfo->stu_no,stuno[row_ops]);	
		//检查数据库中是否已经添加了该学生的科目成绩信息
		if(check_stuscoreinfo_empty_bystuno(stuinfo,mysql,res,row,query) == false)
		{
			printf("该学生的成绩已经添加了,如果要修改请去修改界面\n");
		}
		else
		{

			//2.统计数据库含有多少条该学生该学期的专业科目信息
			//得到该学生的科目数量
			int count_stusub = getstusubCount(mysql,res,row,query,stuno[row_ops]);
			printf("+------------+------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+------------+-----------+------------+\n");
			printf("该学生[%s]学期有[%d]门专业课\n",yearname[row_ops],count_stusub);
			//3.显示该学生该学期的专业科目信息
			for(int i=0;i<count_stusub;i++)
			{
				sprintf(query,"select sub_info.sub_no,sub_info.sub_name,stu_score.sub_no%d_sc from sub_info,stu_sub,stu_score where stu_sub.stu_sub_no%d = sub_info.sub_no\
								and   stu_sub.stu_no  = stu_score.stu_no and   stu_score.stu_no = \"%s\";",i,i,stuno[row_ops]);
				printf("sql语句:%s\n",query);
				mysql_real_query(mysql,query,strlen(query));
				res = mysql_store_result(mysql);
				if((row=mysql_fetch_row(res)) != NULL)
				{
					printf("   |%-12s|  ",row[0]);
					strcpy(stusubname[i],row[0]);
				}
			}//end for
			printf("\n+------------+------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+------------+-----------+------------+\n");

			//4.选择需要添加的科目成绩

			int count_subscore = 0;
			while(count_subscore < count_stusub)
			{
				printf("请为科目[%s]设置成绩(0-100):\n",stusubname[count_subscore]);
				switch(count_subscore)
				{
					case 0:
						scanf("%d",&stu_scoreinfo->sub_no1_sc);
						break;
					case 1:
						scanf("%d",&stu_scoreinfo->sub_no2_sc);
						break;
					case 2:
						scanf("%d",&stu_scoreinfo->sub_no3_sc);
						break;
					case 3:
						scanf("%d",&stu_scoreinfo->sub_no4_sc);
						break;
					case 4:
						scanf("%d",&stu_scoreinfo->sub_no5_sc);
						break;
					case 5:
						scanf("%d",&stu_scoreinfo->sub_no6_sc);
						break;
					case 6:
						scanf("%d",&stu_scoreinfo->sub_no7_sc);
						break;
					case 7:
						scanf("%d",&stu_scoreinfo->sub_no8_sc);
						break;
					case 8:
						scanf("%d",&stu_scoreinfo->sub_no9_sc);
						break;
					case 9:
						scanf("%d",&stu_scoreinfo->sub_no10_sc);
						break;
					case 10:
						scanf("%d",&stu_scoreinfo->sub_no11_sc);
						break;
					case 11:
						scanf("%d",&stu_scoreinfo->sub_no12_sc);
						break;
					default:
						break;
				}//end switch
				count_subscore ++;
			}

			//5.构造结构体 执行插入语句
			strcpy(stu_scoreinfo->stu_no,stuno[row_ops]);
			strcpy(stu_scoreinfo->stu_year_no,yearno[row_ops]);
			strcpy(stu_scoreinfo->college_no,collegeno[row_ops]);
			strcpy(stu_scoreinfo->profs_no,profsno[row_ops]);

			//5.test 
			printf("stu_no = %s,stu_year_no = %s,college_no = %s,profs_no=%s,sub_no1_sc=%d,sub_no2_sc=%d,sub_no3_sc=%d\n",\
					stu_scoreinfo->stu_no,stu_scoreinfo->stu_year_no,stu_scoreinfo->college_no,stu_scoreinfo->profs_no,\
					stu_scoreinfo->sub_no1_sc,stu_scoreinfo->sub_no2_sc,stu_scoreinfo->sub_no3_sc);

			//6.执行insert语句进行插入操作
			sprintf(query,"insert into stu_score(stu_no,stu_year_no,sub_no1_sc,sub_no2_sc,sub_no3_sc,sub_no4_sc,sub_no5_sc,\
				sub_no6_sc,sub_no7_sc,sub_no8_sc,sub_no9_sc,sub_no10_sc,sub_no11_sc,sub_no12_sc,college_no,profs_no)\
				VALUES(\"%s\",\"%s\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\");"\
				,stu_scoreinfo->stu_no,stu_scoreinfo->stu_year_no,stu_scoreinfo->sub_no1_sc,stu_scoreinfo->sub_no2_sc,\
				stu_scoreinfo->sub_no3_sc,stu_scoreinfo->sub_no4_sc,stu_scoreinfo->sub_no5_sc,stu_scoreinfo->sub_no6_sc,
				stu_scoreinfo->sub_no7_sc,stu_scoreinfo->sub_no8_sc,stu_scoreinfo->sub_no9_sc,stu_scoreinfo->sub_no10_sc,
				stu_scoreinfo->sub_no11_sc,stu_scoreinfo->sub_no12_sc,stu_scoreinfo->college_no,stu_scoreinfo->profs_no);

			printf("sql语句:%s\n",query);

			if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
			{
				printf("mysql_real_query():%s\n",mysql_error(mysql));
				exit(-1);
			}
			else
			{
				printf("数据插入成功\n");
			}
		}
		//释放内存
		free(stu_scoreinfo);
	}//end admin
}//end function


//查询学生信息    学生用户有此权限  管理员用户由此权限
void stuinfo_select(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	init_sql(res,query,row);
	int fields = 0;
	int row_count = 0;

	if(logintype==LOGINTYPE_ADMIN)
	{
		printf("\n你是管理员用户,你可以按照不同的组合进行不同形式地查找学生信息，这里会显示所有学生的信息\n");
		//检查stu_info stu_sub stu_score三个表中是否有学生的数据  这三个表的顺序必须以stu_sub开头
		//1.stu_info检查
		if(check_stuinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
		{
			printf("学生基本信息表中没有数据,请先添加学生基本信息\n");
			stuinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
		}
		else
		{
			printf("学生基本信息表中有数据\n");

			//2.查询所有学生的基本信息 ---有数据
			sprintf(query,"select stu_info.*,college_info.college_name,profs_info.profs_name  from stu_info,college_info,profs_info\
					where stu_info.college_no = college_info.college_no and stu_info.profs_no = profs_info.profs_no;");

			printf("sql语句:%s\n",query);
			mysql_real_query(mysql,query,strlen(query));
			res = mysql_store_result(mysql);
			while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
			{
				fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
				if(row_count==0)
				{
					printf("数据库中学生的基本信息:\n");
					printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
					printf("| stu_no   | stu_name | stu_gender | stu_age | stu_grade | stu_class | college_no | profs_no | user_no | college_name       | profs_name               |\n");
					printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
				}
				printf("|%-12s|%-20s||%-10s|%-26s||%-9s|%-10s||%-12s|%-21s|%-15s|%-25s|%-35s|\n",\
						row[fields-11],row[fields-10],row[fields-9],row[fields-8],row[fields-7],row[fields-6],\
						row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐

				row_count++;
			}
			printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");

		}

	}
	else if(logintype==LOGINTYPE_STUDENT)
	{
		printf("你是学生用户,你只能查询到你自己的信息\n");
		//1.stu_info检查
		if(check_stuinfo_empty(userinfo,stuinfo,mysql,res,row,query,logintype)==true)
		{
			printf("学生基本信息表中没有数据,请先添加你的基本信息\n");
			stuinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
		}
		else
		{
			printf("学生基本信息表中有数据\n");

			//2.查询该学生的基本信息 ---有数据
			sprintf(query,"select stu_info.*,college_info.college_name,profs_info.profs_name  from stu_info,college_info,profs_info\
					where stu_info.college_no = college_info.college_no and stu_info.profs_no = profs_info.profs_no and stu_info.user_no = \"%s\";",userinfo->user_no);

			printf("sql语句:%s\n",query);
			mysql_real_query(mysql,query,strlen(query));
			res = mysql_store_result(mysql);
			while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
			{
				fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
				if(row_count==0)
				{
					printf("数据库中学生的基本信息:\n");
					printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
					printf("| stu_no   | stu_name | stu_gender | stu_age | stu_grade | stu_class | college_no | profs_no | user_no | college_name       | profs_name               |\n");
					printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
				}
				printf("|%-12s|%-20s||%-10s|%-26s||%-9s|%-10s||%-12s|%-21s|%-15s|%-25s|%-35s|\n",\
						row[fields-11],row[fields-10],row[fields-9],row[fields-8],row[fields-7],row[fields-6],\
						row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐

				row_count++;
			}
			printf("+----------+----------+------------+---------+-----------+-----------+------------+----------+---------+--------------------+--------------------------+\n");
		}
	}
}




//添加，修改，删除，查看不同学院不同专业学生不同学期的科目信息
void stuinfo_subinfo_manager(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("\n call %s  \n",__FUNCTION__);

	char ch;//输入的字符:1,2,3,4,5,60---退出
	stusubinfo_manager_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("添加学生科目信息\n");
				stuinfo_subinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case '2':
				printf("修改学生科目信息\n");
				stuinfo_subinfo_update(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case '3':
				printf("删除学生科目信息\n");
				stuinfo_subinfo_delete(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case '4':
				printf("查询学生科目信息\n");
				stuinfo_subinfo_select(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
			default:
				break;
		}
		stusubinfo_manager_ui();
		printf("请输入你的选项:\n");//跳出switch继续下一次用户选择
	}

}


//添加,查看,更新,删除不同学院不同专业学生的不同学期的每一门科目的成绩
void stuinfo_stuscore_manager(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,int optype,int logintype)
{
	printf("\n call %s  \n",__FUNCTION__);
	char ch;//输入的字符:1,2,3,4,5,60---退出
	stuscoreinfo_manager_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("添加学生科目成绩信息\n");
				stuinfo_subscore_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);					
				break;
			case '2':
				printf("修改学生科目成绩信息\n");
				stuinfo_subscore_update(userinfo,stuinfo,mysql,res,row,query,optype,logintype);					
				break;
			case '3':
				printf("删除学生科目成绩信息\n");
				stuinfo_subscore_delete(userinfo,stuinfo,mysql,res,row,query,optype,logintype);					
				break;
			case '4':
				printf("查询学生科目成绩信息\n");
				stuinfo_subscore_select(userinfo,stuinfo,mysql,res,row,query,optype,logintype);					
			default:
				break;
		}
		while(getchar()!='\n');
		stuscoreinfo_manager_ui();
		printf("请输入你的选项:\n");//跳出switch继续下一次用户选择
	}

}

/*
   @func:进行针对学生信息进行的处理
   @optype:对数据表的操作  宏定义
   @logintype:登录用户类型 宏定义
   @mysql,res,row,query:数据库操作变量
   */
void stuinfo_manager(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query,int optype,int logintype)
{
	if(logintype == LOGINTYPE_ADMIN)
	{
		switch(optype)
		{
			case OPTYPE_ADMIN_STU_SELECT:
				//管理员查询学生的基本信息
				stuinfo_select(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_ADMIN_STU_UPDATE:
				//管理员更新学生的基本信息
				stuinfo_update(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_ADMIN_STU_DELETE:
				//管理员删除学生的基本信息
				stuinfo_delete(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_ADMIN_STU_INSERT:
				//管理员添加学生的基本信息
				stuinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_ADMIN_STU_SUBJECT:
				//管理员添加不同学院不同专业不同学期的科目信息  学生科目表
				stuinfo_subinfo_manager(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_ADMIN_STU_SCORE:
				//管理员添加不同学院不同专业不同学期不同学生的不同科目成绩  学生科目成绩表
				stuinfo_stuscore_manager(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_ADMIN_STU_SUBINFO_SELECT:
				//管理员查询学生某一学期的科目信息和科目成绩信息
				stuinfo_subscore_select(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			default:
				break;
		}
	}
	else if(logintype == LOGINTYPE_STUDENT)
	{
		switch(optype)
		{
			case OPTYPE_STUDENT_STU_SELECT:
				//查询学生自身基本信息
				stuinfo_select(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_STUDENT_STU_UPDATE:
				//更新学生自身基本信息
				stuinfo_update(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			case OPTYPE_STUDENT_STU_SUBINFO:
				//查询该登录学生不同学期的科目信息(包括成绩)
				stuinfo_subscore_select(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
			case OPTYPE_STUDENT_STU_INSERT:
				//添加学生的基本信息
				stuinfo_insert(userinfo,stuinfo,mysql,res,row,query,optype,logintype);
				break;
			default:
				break;
		}
	}
}


void stu_manager(user_info_t *userinfo,MYSQL *mysql)//学生用户管理  调用此函数说明是学生用户
{
	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[500]={0};//放入sql语句

	//结构体变量的声明
	stu_info_t      *stuinfo;//学生信息
	//分配内存以及初始化
	stuinfo         = (stu_info_t*)malloc(sizeof(stu_info_t));
	memset(stuinfo,0,sizeof(stu_info_t));

	//userinfo结构体中应该包含可学生用户的一些信息
	printf("userinfo->username = %s\n",userinfo->username);
	//得到学生用户的用户ID,用于学生节本信息表的插入
	sprintf(query,"select user_info.user_no from user_info where user_info.username = \"%s\";",userinfo->username);
	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));
	res = mysql_store_result(mysql);
	if((row=mysql_fetch_row(res))!=NULL)
	{
		strcpy(userinfo->user_no,row[0]);
	}
	printf("userinfo->userno = %s\n",userinfo->user_no);
	char ch;//输入的字符:1,2,3,4,5,60---退出
	stu_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("查询学生自身的基本信息\n");
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_STUDENT_STU_SELECT,LOGINTYPE_STUDENT);
				break;
			case '2':
				printf("修改学生自身的信息\n");
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_STUDENT_STU_UPDATE,LOGINTYPE_STUDENT);
				break;
			case '3':
				printf("查询学生自身不同学期的科目信息(含成绩)\n");
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_STUDENT_STU_SUBINFO,LOGINTYPE_STUDENT);
				break;
			case '4':
				printf("添加学生自身的基本信息(只有一次添加的机会)\n");
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_STUDENT_STU_INSERT,LOGINTYPE_STUDENT);
			default:
				break;
		}
		stu_ui();
		printf("请输入你的选项:\n");//跳出switch继续下一次用户选择
	}
	//释放内存
	free(stuinfo);
}
