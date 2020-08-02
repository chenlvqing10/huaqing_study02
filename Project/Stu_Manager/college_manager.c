#include "head.h"

bool check_college_empty(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	bool isempty=false;

	sprintf(query,"select * from college_info;");
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
	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		isempty=true;

	init_sql(res,query,row);
	return isempty;
}



void college_manager(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	//自动生成编号 0001开始

	char collegeno[20]={0};//学院编号
	char *pt_collegeno=collegeno;//指针指向学院编号
	pt_collegeno=get_tableno(mysql,res,row,query,pt_collegeno,3,NULL);

	printf("请输入需要添加的学院的名字:");
	scanf("%s",collegeinfo->college_name);

	if(mysql_query(mysql, "set names \'utf8\'"))  //这个是关键
	{
		printf("字符集:%s\n",mysql_error(mysql));
	}

	sprintf(query,"insert into college_info(college_no,college_name)VALUES(\"%s\",\"%s\");",collegeno,collegeinfo->college_name);

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
