#include "head.h"

void admin_ui()
{
	printf("/*********************************************************************************************************/\n");
	printf("/*********************************************************************************************************/\n");
	printf("/*********************************************************************************************************/\n");
	printf("/***********************欢迎管理员操作模块界面********************************/\n");
	printf("/***********************1.添加,修改,删除,查询用户信息(包括管理员用户和学生用户)***************************/\n");
	printf("/***********************2.查询，添加,修改,删除管理员自身的信息********************************************/\n");
	printf("/***********************3.学生信息的查询******************************************************************/\n");
	printf("/***********************4.学生基本信息的修改**************************************************************/\n");
	printf("/***********************5.学生基本信息的删除**************************************************************/\n");
	printf("/***********************6.学生基本信息的添加**************************************************************/\n");
	printf("/***********************7.添加,查询,更新,删除学院信息*****************************************************/\n");//按学院编号查询
	printf("/***********************8.添加,查看,更新,删除不同学院的专业信息*******************************************/\n");//按专业编号查询
	printf("/***********************9.添加,查看,更新,删除不同学院不同专业的科目信息***********************************/\n");//按科目编号查询
	printf("/***********************A.添加,查看,更新,删除不同学院不同专业学生的不同学期的科目信息*********************/\n");//联合查询
	printf("/***********************B.添加,查看,更新,删除不同学院不同专业学生的不同学期的每一门科目的成绩*************/\n");//联合查询
	printf("/***********************C.查询某一学生的科目信息(包括成绩)************************************************/\n");//按学号查询
	printf("/***********************D.设置学期信息(添加,查看,更新,删除)***********************************************/\n");
	printf("/***********************0.退出管理员管理模块**************************************************************/\n");
	printf("/*********************************************************************************************************/\n");
	printf("/*********************************************************************************************************/\n");
	printf("/*********************************************************************************************************/\n");
}
void admininfo_ui()
{
	printf("/******************************管理员信息处理界面*********************************/\n");
	printf("/**************按0:返回管理员管理模块(数据处理完了)*******************/\n");
	printf("/**************按1:管理员信息查看*************************************/\n");
	printf("/**************按2:管理员信息修改*************************************/\n");
	printf("/**************按3:管理员信息删除*************************************/\n");
	printf("/**************按4:添加管理员信息*************************************/\n");
	printf("/**************按其他键:处理下一个管理员用户数据(数据处理未完了)******/\n");
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

void admininfo_delete_ui()
{
	printf("/*********************************************************************************/\n");
	printf("/*******************************管理员信息删除界面********************************/\n");
	printf("/******************请确认你是否真得要删除管理员信息!!!(谨慎操作)×*****************/\n");
	printf("/*********************************************************************************/\n");
	printf("/*********************************************************************************/\n");
}

//管理员信息数据查询
int admininfo_select(MYSQL *mysql,MYSQL_ROW row,MYSQL_RES* res,char* query)
{
	int fields = 0;
	//得到全部的管理员信息
	sprintf(query,"select * from admin_info;");

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
	int row_count = 0;
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(row_count==0)
		{
			printf("数据库中含有的用户信息:\n");
			printf("+-----------+--------------+----------------+------------+--------------+-----------+\n");
			printf("| admin_no  |  admin_name  |  admin_gender  | admin_age  |  college_no  |  user_no  |\n");
			printf("+-----------+--------------+----------------+------------+--------------+-----------+\n");
		}
		printf("|%-11s|%-14s|%-16s|%-11s|%-13s|%-11s|\n",row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		row_count++;
	}
	printf("+-----------+--------------+----------------+------------+--------------+-----------+\n");
	init_sql(res,query,row);

	return row_count;
}

//管理员信息数据更新　指定是更新的哪一行数据　　即哪一位管理员
void admininfo_update(admin_info_t *admininfo,MYSQL *mysql,char *adminid,int fields,MYSQL_ROW row,MYSQL_RES* res,int row_op)
{
	char ch;
	int gender;
	char college_name[20]="信息技术学院";
	char collegeno[20]={0};//学院编号
	char *pt_collegeno=collegeno;//指针指向学院编号
	char query[500]={0};//放入sql语句

	//进行初始化结构体
	strcpy(admininfo->admin_no,adminid);
	sprintf(query,"select * from admin_info where admin_info.admin_no = \"%s\";",adminid);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//将数据库服务器端获得的数据传送到客户端
	if((row=mysql_fetch_row(res)) != NULL)//得到数据
	{
		strcpy(admininfo->admin_name,row[1]);
		strcpy(admininfo->gender,row[2]);
		admininfo->admin_age = atoi(row[3]);
		strcpy(admininfo->college_no,row[4]);
	}

	admininfo_update_ui();
	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("请输入要修改的管理员姓名:");
				scanf("%s",admininfo->admin_name);
				printf("修改后的姓名:%s\n",admininfo->admin_name);
				break;
			case '2':
				printf("请输入要修改的管理员性别编号(0--male,1--femal):");
				scanf("%d",&gender);
				if(gender==0)
					strcpy(admininfo->gender,"男");
				else if(gender==1)
					strcpy(admininfo->gender,"女");
				printf("修改后的性别:%s\n",admininfo->gender);
				break;
			case '3':
				printf("请输入要修改的管理员年龄:");
				scanf("%d",&admininfo->admin_age);
				printf("修改后的年龄:%d\n",admininfo->admin_age);
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

//联合查询用户数据表中管理员用户的数据条数,如果有发现用户表中的数据和管理员信息表中的数据不同的情况下 保存不同的userno
bool check_admininfo_byuserno(user_info_t *userinfo,admin_info_t *admininfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char (*userno)[20])//指针数组类型(char*)[20]
{
	init_sql(res,query,row);

	//查询user_info表中是否存在admin_info表中没有的user_no
	sprintf(query,"select user_info.user_no from user_info left join admin_info on user_info.user_no = admin_info.user_no where user_info.usertype = 2 and admin_info.admin_no is NULL;");

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
	int i=0;
	while((row=mysql_fetch_row(res))!=NULL) //不为空
	{
		printf("存在不包含的用户ID\n");
		printf("userid = %s\n",row[0]);
		strcpy(userno[i],row[0]);
		printf("userno = %s\n",userno[i]);
		i++;
	}

	if(i==0)
		return true;

	init_sql(res,query,row);
	return false; //表示两表中的数据不匹配
}

//管理员用户的添加
//用到的表:用户表　　管理员信息表　　　学院信息表  　　根据用户ID插入数据
void admininfo_insert(user_info_t *userinfo,admin_info_t *admininfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char* userid)
{
	printf("11111111111111\n");
	init_sql(res,query,row);
	//局部变量声明
	char adminno[8]={0};//管理员编号
	int year=1900;//入校年份声明并初始化
	int month=0;//入校月份申明并初始化
	char subadminno[8]={0};//得到管理员编号的后两位数值
	char *pt_subadminno=subadminno;//指针先指向subadminno
	int  gender=0;//性别 0--male  1--femal
	char collegeno[20]={0};//学院编号
	char *pt_collegeno=collegeno;//指针指向学院编号
	time_t timep;
	struct tm *p_time;

	printf("11111111111111\n");
	strcpy(admininfo->user_no,userid);
	printf("请输入用户编号[%s]的用户信息:\n",admininfo->user_no);

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
	scanf("%s",collegeinfo->college_name);
	//检查学院信息是否为空
	if(check_college_empty(collegeinfo,mysql,res,row,query)==true)//空
	{
		//返回管理员界面　　添加学院信息
		printf("学院信息为空,需要回到管理员操作界面\n");
	}

	pt_collegeno=get_tableno(mysql,res,row,query,pt_collegeno,5,collegeinfo->college_name);//得到学院编号
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

}

//进行管理员信息的删除 
void admininfo_delete(admin_info_t *admininfo,char* adminid,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	//输入数据表
	strcpy(admininfo->admin_no,adminid);
	sprintf(query,"delete from admin_info where admin_info.admin_no = \"%s\";",admininfo->admin_no);
	printf("sql语句:%s\n",query);

	if(mysql_real_query(mysql,query,strlen(query)) != 0)//执行sql语句 成功返回0
	{
		printf("mysql_real_query():%s\n",mysql_error(mysql));
		exit(-1);
	}
	else
	{
		printf("mysql_real_query() sucess!!! 删除数据成功\n");
	}

}

//管理员信息管理  查看，添加,修改，删除管理员信息
void admininfo_manager(user_info_t *userinfo,admin_info_t *admininfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query)
{
	int fields = 0;
	//得到全部的管理员信息
	sprintf(query,"select * from admin_info;");

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



	char adminid[20][20] = {0};//管理员编号
	char userid[20][20] = {0};//用户编号

	int row_count = 0;
	//获取数据集  char**类型  每一行的数据
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数 获取的row是char**类型的
	{
		fields=mysql_num_fields(res);//列数 row[i]代表该行第几个字段的数据
		if(row_count==0)
		{
			printf("数据库中含有的管理员信息:\n");
			printf("+-----------+--------------+----------------+------------+--------------+-----------+\n");
			printf("| admin_no  |  admin_name  |  admin_gender  | admin_age  |  college_no  |  user_no  |\n");
			printf("+-----------+--------------+----------------+------------+--------------+-----------+\n");
		}
		printf("|%-11s|%-14s|%-16s|%-11s|%-13s|%-11s|\n",row[fields-6],row[fields-5],row[fields-4],row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(adminid[row_count],row[fields-6]);
		strcpy(userid[row_count],row[fields-1]);
		row_count++;
	}
	printf("+-----------+--------------+----------------+------------+--------------+-----------+\n");

	char ch;
	int row_op = 0;
	char userno_nomatch[20][20] = {0};

	int i = 0;
	admininfo_ui();
	printf("请输入你的选项:");
	while((ch = getchar()) != '0')//按0退出循环
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				admininfo_select(mysql,row,res,query);
				break;
			case '2':
				//进行单个用户信息更新(通过选择)
				printf("你现在有[%d]条用信息,请选择你要处理的用户信息是哪一条(数据行 从0开始):",row_count);//如果有界面的话，界面会显示出全部的数据，可以通过按钮进行操作
				scanf("%d",&row_op);
				//超级用户权限限制,任何人都无法修改
				if(strcmp(userid[row_op],SUPERUSERID)==0)
				{
					printf("超级用户无法修改\n");
					exit(-1);
				}
				printf("你要处理的是第[%d]条用户信息,现在你的用户ID是[%s],你的管理员ID是[%s]\n",row_op,userid[row_op],adminid[row_op]);
				admininfo_update(admininfo,mysql,adminid[row_op],fields,row,res,row_op);
				printf("更新成功后继续执行下一个循环\n");
				admininfo_ui();
				break;
			case '3':
				//进行单个用户信息的删除
				printf("你现在有[%d]条用信息,请选择你要处理的用户信息是哪一条(数据行 从0开始):",row_count);//如果有界面的话，界面会显示出全部的数据，可以通过按钮进行操作
				scanf("%d",&row_op);
				//超级用户权限限制,任何人都无法修改
				if(strcmp(userid[row_op],SUPERUSERID)==0)
				{
					printf("超级用户无法修改\n");
					exit(-1);
				}
				printf("你要处理的是第[%d]条用户信息,现在你的用户ID是[%s],你的管理员ID是[%s]\n",row_op,userid[row_op],adminid[row_op]);
				admininfo_delete(admininfo,adminid[row_op],mysql,res,row,query);
				break;
			case '4':
				//进行管理员信息的添加　首先检查是否需要添加(即检查用户表中的数据和管理员信息表中的数据是否匹配)
				if(check_admininfo_byuserno(userinfo,admininfo,mysql,res,row,query,userno_nomatch) == true)
				{
					printf("管理员信息已经全部添加了，不需要重复添加\n");
				}
				else
				{
					while(strcmp(userno_nomatch[i],""))
					{
						printf("userno_nomatah = %s\n",userno_nomatch[i]);
						admininfo_insert(userinfo,admininfo,collegeinfo,mysql,res,row,query,userno_nomatch[i]);
						i++;
					}
				}
				break;
			default:
				break;
		}
		admininfo_ui();
		printf("请输入你的选项:");
	}

	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
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
	year_info_t     *yearinfo;//学期信息

	//分配内存以及初始化
	admininfo		= (admin_info_t*)malloc(sizeof(admin_info_t));
	stuinfo			= (stu_info_t*)malloc(sizeof(stu_info_t));
	stusub			= (stu_sub_t*)malloc(sizeof(stu_sub_t));
	stuscore		= (stu_score_t*)malloc(sizeof(stu_score_t));
	collegeinfo		= (college_info_t*)malloc(sizeof(college_info_t));
	profsinfo		= (profs_info_t*)malloc(sizeof(profs_info_t));
	subinfo			= (sub_info_t*)malloc(sizeof(sub_info_t));
	yearinfo		= (year_info_t*)malloc(sizeof(year_info_t));

	memset(admininfo,0,sizeof(admin_info_t));
	memset(stuinfo,0,sizeof(stu_info_t));
	memset(stusub,0,sizeof(stu_sub_t));
	memset(stuscore,0,sizeof(stu_score_t));
	memset(collegeinfo,0,sizeof(college_info_t));
	memset(profsinfo,0,sizeof(profs_info_t));
	memset(subinfo,0,sizeof(sub_info_t));
	memset(yearinfo,0,sizeof(year_info_t));

	/*与数据库进行交互 变量声明*/
	MYSQL_RES *res = NULL;//数据库查询的结果集
	MYSQL_ROW row=NULL;//char**  指向一个字符串数组，从结果集中取得数据
	char query[1000]={0};//放入sql语句  sql语句的长度有可能会比较长  这里分配的栈空间如果过小会造成栈溢出

	//根据选项的不同进行界面操作
	char ch;//输入的字符:1,2,3,4,5,6,7,8,9,A,0---退出
	admin_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				printf("添加,修改,删除,查看管理员用户和学生用户信息\n");
				user_manager(userinfo,mysql,USERINFOMANAGER,USERTYPE_ADMIN,LOGINTYPE_ADMIN);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case '2':
				printf("进行管理员信息的查看,添加,修改,删除\n");
				admininfo_manager(userinfo,admininfo,collegeinfo,mysql,res,row,query);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case '3':
				printf("学生基本信息的查询\n");
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_SELECT,LOGINTYPE_ADMIN);
				break;
			case '4':
				printf("学生基本信息的修改\n");
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_UPDATE,LOGINTYPE_ADMIN);
				break;
			case '5':
				printf("学生基本信息的删除\n");
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_DELETE,LOGINTYPE_ADMIN);
				break;
			case '6':
				printf("学生基本信息的添加\n");
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				init_sql(res,query,row);
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_INSERT,LOGINTYPE_ADMIN);
				
				break;
			case '7':
				printf("添加,修改,删除,查询学院信息\n");
				college_manager(collegeinfo,mysql,res,row,query);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case '8':
				printf("添加,修改,删除,查询不同学院的专业信息\n");
				profs_manager(profsinfo,collegeinfo,mysql,res,row,query);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case '9':
				printf("添加，修改，删除，查看不同学院不同专业科目信息\n");
				sub_manager(subinfo,profsinfo,collegeinfo,mysql,res,row,query);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case 'A':
				printf("添加，修改，删除，查看不同学院不同专业学生不同学期的科目信息\n");//成绩类别 未添加  可以改进
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_SUBJECT,LOGINTYPE_ADMIN);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case 'B':
				printf("添加,查看,更新,删除不同学院不同专业学生的不同学期的每一门科目的成绩\n");
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_SCORE,LOGINTYPE_ADMIN);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case 'C':
				printf("查询某一学生的科目信息(包括成绩)\n");
				stuinfo_manager(userinfo,stuinfo,mysql,res,row,query,OPTYPE_ADMIN_STU_SUBINFO_SELECT,LOGINTYPE_ADMIN);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
				break;
			case 'D':
				printf("设置学期信息(添加,更新,删除,修改)\n");
				year_manager(yearinfo,mysql,res,row,query);
				printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);
			default:
				break;
		}
		admin_ui();
		printf("请输入你的选项:\n");
	}
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);

	//释放内存
	free(collegeinfo);
	free(admininfo);
	free(stuinfo);
	free(profsinfo);
	free(userinfo);
	free(subinfo);
	free(stusub);
	free(stuscore);
	printf("file:%s  func:%s  line:%d",__FILE__,__FUNCTION__,__LINE__);

}
