#include "head.h"

//学院专业科目信息管理模块

//学院专业科目信息操作界面
void subinfo_ui()
{
	printf("/******************************学院专业科目信息处理界面*********************************/\n");
	printf("/**************按0:返回上一个界面*******************/\n");
	printf("/**************按1:添加学院专业科目信息*************************************/\n");
	printf("/**************按2:更新学院专业科目信息*************************************/\n");
	printf("/**************按3:删除学院专业科目信息*************************************/\n");
	printf("/**************按4:查询学院专业科目信息*************************************/\n");
}

//检查某一学院的专业科目信息是否为空  通过专业名称 需要先设置profs_info_t结构体的profs_name
bool check_subinfo_empty(sub_info_t *subinfo,profs_info_t *profsinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	init_sql(res,query,row);
	bool isempty=false;
	sprintf(query,"select * from sub_info  where sub_info.profs_no = (select profs_info.profs_no from profs_info \
		where profs_info.profs_name = \"%s\") and sub_info.sub_name = \"%s\";",profsinfo->profs_name,subinfo->sub_name);
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


void  subinfo_insert(sub_info_t *subinfo,college_info_t *collegeinfo,profs_info_t *profsinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	//自动生成编号 0001开始
	char subinfono[20]={0};//学院编号
	char *pt_subinfono=subinfono;//指针指向学院编号
	pt_subinfono=get_tableno(mysql,res,row,query,pt_subinfono,GET_SUBNO,NULL);
	strcpy(subinfo->sub_no,subinfono);
	subinfo->sub_no[5] = '\0';
	printf("请输入你要添加的学院名称:\n");
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

	printf("请输入你要添加的专业名称:");
	scanf("%s",profsinfo->profs_name);
	
	//检查输入的专业名称是否正确
    int check_count1 = 0;
    while(check_profs_empty(profsinfo,collegeinfo,mysql,res,row,query)==true)
    {
        check_count1++;
        if(check_count1==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院专业信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",profsinfo->profs_name);
    }

	if(mysql_query(mysql, "set names \'utf8\'"))  //处理汉字的编码
	{
		printf("字符集:%s\n",mysql_error(mysql));
	}
    if(mysql_query(mysql,"alter table sub_info change sub_name sub_name varchar(20)  character  set utf8 NOT NULL;"))
    {
        printf("alter utf8 error\n");
    }

	//得到学院编号
	sprintf(query,"select profs_info.profs_no from profs_info where profs_info.profs_name = \"%s\"\
			and profs_info.college_no = (select college_info.college_no from college_info where college_info.college_name = \"%s\");",profsinfo->profs_name,collegeinfo->college_name);

	mysql_real_query(mysql,query,strlen(query));//执行sql语句 成功返回0
	res=mysql_store_result(mysql);
	if((row=mysql_fetch_row(res))!=NULL)
	{
		strcpy(subinfo->profs_no,row[0]);
	}

	printf("profs_no = %s\n",subinfo->profs_no);
	//输入专业名称，插入操作
	printf("请输入学院[%s],专业[%s]的科目信息:",collegeinfo->college_name,profsinfo->profs_name);
	scanf("%s",subinfo->sub_name);
	sprintf(query,"insert into sub_info(sub_no,sub_name,profs_no) VALUES(\"%s\",\"%s\",\"%s\");",subinfo->sub_no,subinfo->sub_name,subinfo->profs_no);
	printf("SQL语句:%s\n",query);
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


/*查询学院专业的科目信息*/
void subinfo_select(sub_info_t *subinfo,college_info_t *collegeinfo,profs_info_t *profsinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
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

	printf("请输入你要查询的专业名称:");
	scanf("%s",profsinfo->profs_name);
	
	//检查输入的专业名称是否正确
    int check_count1 = 0;
    while(check_profs_empty(profsinfo,collegeinfo,mysql,res,row,query)==true)
    {
        check_count1++;
        if(check_count1==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院专业信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",profsinfo->profs_name);
    }

	//得到该学院专业的科目信息
	sprintf(query,"select * from sub_info where sub_info.profs_no = (select profs_info.profs_no from profs_info  where profs_info.profs_name = \"%s\" \
		and profs_info.college_no =  (select college_info.college_no from college_info where college_info.college_name = \"%s\"));",profsinfo->profs_name,collegeinfo->college_name);
	printf("sub_info sql语句=%s\n",query);
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
			printf("学院专业科目信息:\n");
			printf("+---------+------------+----------+--------------+----------------+\n");
			printf("| sub_no  |  sub_name  |  profs_no|  profs_name  |  college_name  |\n");
			printf("+---------+------------+----------+--------------+----------------+\n");
		}
		printf("|%-9s|%-11s|%-10s|%-15s|%-16s\n",row[fields-3],row[fields-2],row[fields-1],profsinfo->profs_name,collegeinfo->college_name);//左对齐
		row_count++;
	}
	printf("+---------+------------+----------+--------------+----------------+\n");

	if(row_count==0)
	{
		printf("学院[%s]专业[%s]没有科目信息,请先添加科目信息\n",collegeinfo->college_name,profsinfo->profs_name);
	}
}


/*更新学院专业科目信息----学院名称 学院专业名称*/
void subinfo_update(sub_info_t *subinfo,college_info_t *collegeinfo,profs_info_t *profsinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int	 fields		= 0;//表中的字段数
	int  row_count	= 0;//行数
	int  row_ops	= 0;//记录数
	char subno[50][10]   = {0};//保存学院专业科目编号
	char subname[50][30] = {0};//保存学院专业科目名称
	char profsno[50][10] = {0};//保存学院专业编号
	char newsubname[20]  = {0};//新的学院专业科目名称

	init_sql(res,query,row);

	printf("请输入你要修改的学院名称:\n");
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

	printf("请输入你要修改的专业名称:");
	scanf("%s",profsinfo->profs_name);
	
	//检查输入的专业名称是否正确
    int check_count1 = 0;
    while(check_profs_empty(profsinfo,collegeinfo,mysql,res,row,query)==true)
    {
        check_count1++;
        if(check_count1==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院专业信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",profsinfo->profs_name);
    }

	//得到该学院专业的科目信息
	sprintf(query,"select * from sub_info where sub_info.profs_no = (select profs_info.profs_no from profs_info  where profs_info.profs_name = \"%s\" \
		and profs_info.college_no =  (select college_info.college_no from college_info where college_info.college_name = \"%s\"));",profsinfo->profs_name,collegeinfo->college_name);
	printf("sub_info sql语句=%s\n",query);
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
			printf("学院专业科目信息:\n");
			printf("+---------+------------+----------+\n");
			printf("| sub_no  |  sub_name  |  profs_no|\n");
			printf("+---------+------------+----------+\n");
		}
		printf("|%-9s|%-11s|%-10s|\n",row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(subno[row_count],row[fields-3]);
		strcpy(subname[row_count],row[fields-2]);
		strcpy(profsno[row_count],row[fields-1]);
		row_count++;
	}
	printf("+---------+------------+----------+\n");
	if(row_count>0)//有记录数
	{
		//选择修改的数据记录是哪一条(要修改哪一个学院的名称)
		printf("现在存在[%d]条学院信息,请输入你想要修改的是哪一条记录:",row_count);
		scanf("%d",&row_ops);
		printf("你想要修改第[%d]条记录,学院名称[%s],专业编号[%s],专业名称[%s],科目编号[%s],科目名称[%s]\n",
				row_ops,collegeinfo->college_name,profsno[row_ops],profsinfo->profs_name,subno[row_ops],subname[row_ops]);

		//执行更新
		printf("请输入新的学院专业科目信息:");
		char c = 0;
		while((c=getchar())!='\n');//清输入缓冲区 代码中应该修改成这种形式的,信息可能是英文并且带空格的	
		scanf("%[^\n]",newsubname);
		sprintf(query,"update sub_info set sub_info.sub_name = \"%s\" where sub_info.sub_no = \"%s\";",newsubname,subno[row_ops]);
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
		printf("学院[%s]专业[%s]没有科目信息,请先添加科目信息\n",collegeinfo->college_name,profsinfo->profs_name);
	}
}

/*删除学院专业科目信息-----外键注意*/
void subinfo_delete(sub_info_t *subinfo,college_info_t *collegeinfo,profs_info_t *profsinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int	 fields		= 0;//表中的字段数
	int  row_count	= 0;//行数
	int  row_ops	= 0;//记录数
	char subno[50][10]   = {0};//保存学院专业科目编号
	char subname[50][30] = {0};//保存学院专业科目名称
	char profsno[50][10] = {0};//保存学院专业编号
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

	printf("请输入你要删除的专业名称:");
	scanf("%s",profsinfo->profs_name);
	
	//检查输入的专业名称是否正确
    int check_count1 = 0;
    while(check_profs_empty(profsinfo,collegeinfo,mysql,res,row,query)==true)
    {
        check_count1++;
        if(check_count1==3)
        {
            printf("输错3次了,退出系统\n");
            exit(-1);
        }
        printf("输入的学院专业信息有误，请先检查并重新输入，输错三次会退出系统:");
        fflush(stdin);
        fflush(stdout);
        scanf("%s",profsinfo->profs_name);
    }

	//得到该学院专业的科目信息
	sprintf(query,"select * from sub_info where sub_info.profs_no = (select profs_info.profs_no from profs_info  where profs_info.profs_name = \"%s\" \
		and profs_info.college_no =  (select college_info.college_no from college_info where college_info.college_name = \"%s\"));",profsinfo->profs_name,collegeinfo->college_name);
	printf("sub_info sql语句=%s\n",query);
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
			printf("学院专业科目信息:\n");
			printf("+---------+------------+----------+\n");
			printf("| sub_no  |  sub_name  |  profs_no|\n");
			printf("+---------+------------+----------+\n");
		}
		printf("|%-9s|%-11s|%-10s|\n",row[fields-3],row[fields-2],row[fields-1]);//左对齐
		strcpy(subno[row_count],row[fields-3]);
		strcpy(subname[row_count],row[fields-2]);
		strcpy(profsno[row_count],row[fields-1]);
		row_count++;
	}
	printf("+---------+------------+----------+\n");
	if(row_count>0)
	{
		//选择修改的数据记录是哪一条(要修改哪一个学院的名称)
		printf("现在存在[%d]条学院信息,请输入你想要删除的是哪一条记录:",row_count);
		scanf("%d",&row_ops);
		printf("你想要删除第[%d]条记录,学院名称[%s],专业编号[%s],专业名称[%s],科目编号[%s],科目名称[%s]\n",
				row_ops,collegeinfo->college_name,profsno[row_ops],profsinfo->profs_name,subno[row_ops],subname[row_ops]);

		//执行删除
		sprintf(query,"delete from sub_info where sub_info.sub_no = \"%s\";",subno[row_ops]);
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
		printf("学院[%s]专业[%s]没有科目信息,请先添加科目信息\n",collegeinfo->college_name,profsinfo->profs_name);
	}
}

void  sub_manager(sub_info_t *subinfo,profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	char ch;//输入的字符:1,2,3,4
	subinfo_ui();
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		printf("file:%s  func:%s  line:%d\n",__FILE__,__FUNCTION__,__LINE__);
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				subinfo_insert(subinfo,collegeinfo,profsinfo,mysql,res,row,query);//添加学院专业信息
				break;
			case '2':
				subinfo_update(subinfo,collegeinfo,profsinfo,mysql,res,row,query);//更新学院专业信息
				break;
			case '3':
				subinfo_delete(subinfo,collegeinfo,profsinfo,mysql,res,row,query);//删除学院专业信息
				break;
			case '4':
				subinfo_select(subinfo,collegeinfo,profsinfo,mysql,res,row,query);//查询学院专业信息
				break;
			default:
				break;
		}
		subinfo_ui();
		fflush(stdin);
		fflush(stdout);
	}

}
