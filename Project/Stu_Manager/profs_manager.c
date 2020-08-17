#include "head.h"
//学院专业信息管理模块

//学院专业信息操作界面
void profsinfo_ui()
{
	printf("/******************************学院专业信息处理界面*********************************/\n");
	printf("/**************按0:返回上一个界面*******************/\n");
	printf("/**************按1:添加学院专业信息*************************************/\n");
	printf("/**************按2:更新学院专业信息*************************************/\n");
	printf("/**************按3:删除学院专业信息*************************************/\n");
	printf("/**************按4:查询学院专业信息*************************************/\n");
}


//检查某一学院的专业信息是否为空  通过学院名称 调用函数的时候需要知道学院名称(collegeinfo->college_name要set)
bool check_profs_empty(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	init_sql(res,query,row);
	bool isempty=false;
	sprintf(query,"select profs_info.profs_no from profs_info,college_info where profs_info.college_no = college_info.college_no \
			and college_info.college_name = \"%s\" and profs_info.profs_name = \"%s\";",collegeinfo->college_name,profsinfo->profs_name);
	printf("sql语句:%s\n",query);

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

	return isempty;

}


/*更新学院专业信息----学院名称 学院专业名称*/
void profsinfo_update(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int	 fields		= 0;//表中的字段数
	int  row_count	= 0;//行数
	int  row_ops	= 0;//记录数
	char profsno[50][10]   = {0};//保存学院专业编号
	char profsname[50][30] = {0};//保存学院专业名称
	char collegeno[50][10] = {0};//保存学院编号
	char newprofsname[20]  = {0};//新的学院专业信息

	init_sql(res,query,row);

	printf("请输入你要更新的学院名称:\n");
	scanf("%s",collegeinfo->college_name);
    
	//检查输入的学院名称是否正确
    int check_count = 0;
    while(check_college_empty(collegeinfo,mysql,res,row,query)==true)
    {
        check_count++;
        if(check_count==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",collegeinfo->college_name);
    }

	//得到该学员的专业信息
	sprintf(query,"select * from profs_info where profs_info.college_no =\
			\(select college_no from college_info where college_info.college_name = \"%s\");",collegeinfo->college_name);
	printf("profs_info sql语句=%s\n",query);
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
			printf("学院专业信息:\n");
			printf("+-----------+--------------+------------+----------------+\n");
			printf("| profs_no  |  profs_name  |  college_no|  college_name  |\n");
			printf("+-----------+--------------+------------+----------------+\n");
		}
		printf("|%-11s|%-14s|%-12s|%-16s|\n",row[fields-3],row[fields-2],row[fields-1],collegeinfo->college_name);//左对齐
		strcpy(profsno[row_count],row[fields-3]);
		strcpy(profsname[row_count],row[fields-2]);
		strcpy(collegeno[row_count],row[fields-1]);
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");

	//选择修改的数据记录是哪一条(要修改哪一个学院的名称)
	if(row_count>0)
	{
		printf("现在存在[%d]条学院信息,请输入你想要修改的是哪一条记录:",row_count);
		scanf("%d",&row_ops);
		printf("你想要修改第[%d]条记录,学院编号[%s],学院名称[%s],专业编号[%s],专业名称[%s]\n",row_ops,collegeno[row_count],collegeinfo->college_name,profsno[row_ops],profsname[row_ops]);

		//执行更新
		printf("请输入新的学院专业信息:");
		scanf("%s",newprofsname);
		sprintf(query,"update profs_info set profs_info.profs_name = \"%s\" where profs_info.profs_no = \"%s\";",newprofsname,profsno[row_ops]);
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
	else
	{
		printf("请先输入学院[%s]的专业信息\n",collegeinfo->college_name);
	}
}

/*删除学院信息-----外键注意*/
void profsinfo_delete(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int	 fields		= 0;//表中的字段数
	int  row_count	= 0;//行数
	int  row_ops	= 0;//记录数
	char profsno[50][10]   = {0};//保存学院专业编号
	char profsname[50][30] = {0};//保存学院专业名称
	char collegeno[50][10] = {0};//保存学院编号

	init_sql(res,query,row);

	printf("请输入你要删除的学院名称:\n");
	scanf("%s",collegeinfo->college_name);
	
	//检查输入的学院名称是否正确
    int check_count = 0;
    while(check_college_empty(collegeinfo,mysql,res,row,query)==true)
    {
        check_count++;
        if(check_count==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",collegeinfo->college_name);
    }


	//得到该学员的专业信息
	sprintf(query,"select * from profs_info where profs_info.college_no =\
			\(select college_no from college_info where college_info.college_name = \"%s\");",collegeinfo->college_name);
	printf("profs_info sql语句=%s\n",query);
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
			printf("学院专业信息:\n");
			printf("+-----------+--------------+------------+----------------+\n");
			printf("| profs_no  |  profs_name  |  college_no|  college_name  |\n");
			printf("+-----------+--------------+------------+----------------+\n");
		}
		printf("|%-11s|%-14s|%-12s|%-16s|\n",row[fields-3],row[fields-2],row[fields-1],collegeinfo->college_name);//左对齐
		strcpy(profsno[row_count],row[fields-3]);
		strcpy(profsname[row_count],row[fields-2]);
		strcpy(collegeno[row_count],row[fields-1]);
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");

	if(row_count>0)
	{
	//选择删除的数据记录是哪一条(要修改哪一个学院的名称)
	printf("现在存在[%d]条学院信息,请输入你想要删除的是哪一条记录:",row_count);
	scanf("%d",&row_ops);
	printf("你想要删除第[%d]条记录,学院编号[%s],学院名称[%s],专业编号[%s],专业名称[%s]\n",row_ops,collegeno[row_ops],collegeinfo->college_name,profsno[row_ops],profsname[row_ops]);

	//执行删除
	sprintf(query,"delete from profs_info where profs_info.profs_no = \"%s\";",profsno[row_ops]);
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
	else
	{
		printf("请先输入学院[%s]的专业信息\n",collegeinfo->college_name);
	}
}

/*查询学院信息*/
void profsinfo_select(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int fields = 0;//表中的字段数
	int row_count = 0;//行数
	init_sql(res,query,row);

	printf("请输入你要查询的学院名称:\n");
	scanf("%s",collegeinfo->college_name);

	//检查输入的学院名称是否正确
    int check_count = 0;
    while(check_college_empty(collegeinfo,mysql,res,row,query)==true)
    {
        check_count++;
        if(check_count==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",collegeinfo->college_name);
    }



	//得到该学员的专业信息
	sprintf(query,"select * from profs_info where profs_info.college_no =\
			\(select college_no from college_info where college_info.college_name = \"%s\");",collegeinfo->college_name);
	printf("profs_info sql语句=%s\n",query);
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
			printf("学院专业信息:\n");
			printf("+-----------+--------------+------------+----------------+\n");
			printf("| profs_no  |  profs_name  |  college_no|  college_name  |\n");
			printf("+-----------+--------------+------------+----------------+\n");
		}
		printf("|%-11s|%-14s|%-12s|%-16s|\n",row[fields-3],row[fields-2],row[fields-1],collegeinfo->college_name);//左对齐
		row_count++;
	}
	printf("+---------+------------+----------+-----------+\n");
	if(row_count==0)
	{
		printf("学院[%s]还没有专业信息,请先添加专业信息\n",collegeinfo->college_name);
	}
}


void  profsinfo_insert(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	//自动生成编号 0001开始
	char profsno[20]={0};//学院编号
	char *pt_profsno=profsno;//指针指向学院编号
	pt_profsno=get_tableno(mysql,res,row,query,pt_profsno,GET_PROFSNO,NULL);
	strncpy(profsinfo->profs_no,profsno,4);
	profsinfo->profs_no[5] = '\0';

	printf("请输入添加专业的学院名称:");
	scanf("%s",collegeinfo->college_name);

	if(mysql_query(mysql, "set names \'utf8\'"))  //这个是关键 处理汉字的编码
	{
		printf("字符集:%s\n",mysql_error(mysql));
	}

	if(mysql_query(mysql,"alter table profs_info change profs_name profs_name varchar(30)  character  set utf8 NOT NULL;"))
	{
		printf("alter utf8 error\n");
	}

	
	//检查输入的学院名称是否正确
	int check_count = 0;
	while(check_college_empty(collegeinfo,mysql,res,row,query)==true)
	{
		check_count++;
		if(check_count==3)
		{
			printf("输错3次了,退出系统\n");
			exit(-1);
		}
		printf("输入的学院信息有误，请先检查并重新输入，输错三次会退出系统:");
		fflush(stdin);
		fflush(stdout);
		scanf("%s",collegeinfo->college_name);
	}
	//得到学院编号
	init_sql(res,query,row);//需要不同的查询结果集,所以需要先初始化
	sprintf(query,"select college_info.college_no from college_info where college_info.college_name = \"%s\";",collegeinfo->college_name);
	printf("sql语句:%s\n",query);
	mysql_real_query(mysql,query,strlen(query));//执行sql语句 成功返回0
	res=mysql_store_result(mysql);
	if((row=mysql_fetch_row(res))!=NULL)
	{
		printf("row[0] = %s\n",row[0]);
		strcpy(profsinfo->college_no,row[0]);
	}
	else
	{
		printf("row[0] = %s\n",row[0]);
		strcpy(profsinfo->college_no,row[0]);
	}


	printf("collegeno = %s\n",profsinfo->college_no);
	//输入专业名称，插入操作
	printf("请输入学院[%s],学院编号[%s]的专业信息:",collegeinfo->college_name,profsinfo->college_no);
	scanf("%s",profsinfo->profs_name);

	printf("collegeno = %s\n",profsinfo->college_no);
	sprintf(query,"insert into profs_info(profs_no,profs_name,college_no) VALUES(\"%s\",\"%s\",\"%s\");",profsinfo->profs_no,profsinfo->profs_name,profsinfo->college_no);
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



void profs_manager(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	char ch;//输入的字符:1,2,3,4
	profsinfo_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		printf("file:%s  func:%s  line:%d\n",__FILE__,__FUNCTION__,__LINE__);
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				profsinfo_insert(profsinfo,collegeinfo,mysql,res,row,query);//添加学院专业信息
				break;
			case '2':
				profsinfo_update(profsinfo,collegeinfo,mysql,res,row,query);//更新学院专业信息
				break;
			case '3':
				profsinfo_delete(profsinfo,collegeinfo,mysql,res,row,query);//删除学院专业信息
				break;
			case '4':
				profsinfo_select(profsinfo,collegeinfo,mysql,res,row,query);//查询学院专业信息
				break;
			default:
				break;
		}
		profsinfo_ui();
	}

}

