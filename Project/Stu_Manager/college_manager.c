#include "head.h"

//学院信息管理模块

//学院信息操作界面
void collegeinfo_ui()
{
	printf("/******************************学院信息处理界面*********************************/\n");
	printf("/**************按0:返回上一个界面*******************/\n");
	printf("/**************按1:添加学院信息*************************************/\n");
	printf("/**************按2:更新学院信息*************************************/\n");
	printf("/**************按3:删除学院信息*************************************/\n");
	printf("/**************按4:查询学院信息*************************************/\n");
}
/*更新学院信息----学院名称*/
void collegeinfo_update(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{

	int fields				 = 0;//表中的字段数
	int row_count			 = 0;//行数
	int row_ops				 = 0;//记录数i
	char collegeno[50][30]	 = {0};//保存学院编号
	char collegename[50][30] = {0};//保存学院名称
	char newcollegename[20]  = {0};//新的学院信息
	init_sql(res,query,row);                                                                                                   

	sprintf(query,"select * from college_info;");
	mysql_real_query(mysql,query,strlen(query));//执行数据库查询 成功返回0
	//查询成功后将服务端内容送到客户端 
	res=mysql_store_result(mysql);
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		fields=mysql_num_fields(res);
		if(row_count==0)
		{
			printf("学院信息:\n");
			printf("+-------------+----------------+\n");
			printf("| college_no  |  college_name  |\n");
			printf("+-------------+----------------+\n");
		}
		printf("|%-13s|%-15s|\n",row[fields-2],row[fields-1]);//左对齐
		strcpy(collegeno[row_count],row[fields-2]);
		strcpy(collegename[row_count],row[fields-1]);
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");

	//选择修改的数据记录是哪一条(要修改哪一个学院的名称)
	printf("现在存在[%d]条学院信息,请输入你想要修改的是哪一条记录:",row_count);
	scanf("%d",&row_ops);
	printf("你想要修改第[%d]条记录,学院编号[%s],学院名称[%s]\n",row_ops,collegeno[row_ops],collegename[row_ops]);

	//执行更新
	printf("请输入新的学院信息:");
	scanf("%s",newcollegename);
	sprintf(query,"update college_info set college_info.college_name = \"%s\" where college_info.college_no = \"%s\";",newcollegename,collegeno[row_ops]);
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

/*删除学院信息-----外键注意*/
void collegeinfo_delete(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{

	int fields				 = 0;//表中的字段数
	int row_count			 = 0;//行数
	int row_ops				 = 0;//记录数i
	char collegeno[50][30]	 = {0};//保存学院编号
	char collegename[50][30] = {0};//保存学院名称
	init_sql(res,query,row);                                                                                                   

	sprintf(query,"select * from college_info;");
	mysql_real_query(mysql,query,strlen(query));//执行数据库查询 成功返回0
	//查询成功后将服务端内容送到客户端 
	res=mysql_store_result(mysql);
	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		fields=mysql_num_fields(res);
		if(row_count==0)
		{
			printf("学院信息:\n");
			printf("+-------------+----------------+\n");
			printf("| college_no  |  college_name  |\n");
			printf("+-------------+----------------+\n");
		}
		printf("|%-13s|%-15s|\n",row[fields-2],row[fields-1]);//左对齐
		strcpy(collegeno[row_count],row[fields-2]);
		strcpy(collegename[row_count],row[fields-1]);
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");

	//选择修改的数据记录是哪一条(要修改哪一个学院的名称)
	printf("现在存在[%d]条学院信息,请输入你想要删除的是哪一条记录:",row_count);
	scanf("%d",&row_ops);
	printf("你想要删除第[%d]条记录,学院编号[%s],学院名称[%s]\n",row_ops,collegeno[row_ops],collegename[row_ops]);

	//执行删除
	sprintf(query,"delete from college_info where college_info.college_no = \"%s\";",collegeno[row_ops]);
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

/*查询学院信息*/
void collegeinfo_select(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int fields = 0;//表中的字段数
	int row_count = 0;//行数

	init_sql(res,query,row);                                                                                                   

	sprintf(query,"select * from college_info;");
	printf("college_info sql语句=%s\n",query);
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


	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		fields=mysql_num_fields(res);
		if(row_count==0)
		{
			printf("学院信息:\n");
			printf("+-------------+----------------+\n");
			printf("| college_no  |  college_name  |\n");
			printf("+-------------+----------------+\n");
		}
		printf("|%-13s|%-15s|\n",row[fields-2],row[fields-1]);//左对齐
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");
}

bool check_college_empty(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	init_sql(res,query,row);
	bool isempty=false;

	sprintf(query,"select * from college_info where college_info.college_name = \"%s\";",collegeinfo->college_name);
	printf("sql语句=%s\n",query);
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
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		isempty=true;

	printf("isempty = %d\n",isempty);
	return isempty;
}


void  collegeinfo_insert(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{

	//自动生成编号 0001开始
	char collegeno[20]={0};//学院编号
	char *pt_collegeno=collegeno;//指针指向学院编号
	pt_collegeno=get_tableno(mysql,res,row,query,pt_collegeno,3,NULL);
	strncpy(collegeinfo->college_no,collegeno,4);
	collegeinfo->college_no[5] = '\0';
	
	//学院名称
	printf("请输入需要添加的学院的名字:");
	scanf("%s",collegeinfo->college_name);

	//设置中文编码
	if(mysql_query(mysql, "set names \'utf8\'"))  //这个是关键
	{
		printf("字符集:%s\n",mysql_error(mysql));
	}

	printf("插入时的学院编号:%s\n",collegeinfo->college_no);

	sprintf(query,"insert into college_info(college_no,college_name)VALUES(\"%s\",\"%s\");",collegeinfo->college_no,collegeinfo->college_name);

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



void college_manager(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	char ch;//输入的字符:1,2,3,4
	collegeinfo_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		printf("file:%s  func:%s  line:%d\n",__FILE__,__FUNCTION__,__LINE__);
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				collegeinfo_insert(collegeinfo,mysql,res,row,query);//添加学院信息
				break;
			case '2':
				collegeinfo_update(collegeinfo,mysql,res,row,query);//更新学院信息
				break;
			case '3':
				collegeinfo_delete(collegeinfo,mysql,res,row,query);//删除学院信息
				break;
			case '4':
				collegeinfo_select(collegeinfo,mysql,res,row,query);//查询学院信息
				break;
			default:
				break;
		}
		collegeinfo_ui();
	}

}
