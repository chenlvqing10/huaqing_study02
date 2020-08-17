#include "head.h"

//学期信息设置


//界面
void yearinfo_ui(void)
{
	printf("/**************学期处理界面*********************************/\n");
	printf("/**************按0:返回上一个界面*******************/\n");
	printf("/**************按1:添加学期信息*************************************/\n");
	printf("/**************按2:更新学期信息*************************************/\n");
	printf("/**************按3:删除学期信息*************************************/\n");
	printf("/**************按4:查询学期信息*************************************/\n");
}
//检查学期信息是否为空
bool check_yearinfo_empty(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	bool isempty = false;
	init_sql(res,query,row);
	sprintf(query,"select * from year_info;");
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集

	if((row=mysql_fetch_row(res))==NULL) //一行一行取得查询结果集数据    行数就是循环次数
		isempty=true;

	return isempty;
}

//插入学期信息
void yearinfo_insert(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int year			= 2020;
	int yeartype	    = 0;
	time_t timep;//得到当前时间
	struct tm *p_time;

	printf("请输入学期的年份:");
	scanf("%d",&year);
	printf("请输入学期的学年(上半学年输入0/下半学年输入1):");
	scanf("%d",&yeartype);

	printf("year = %d yeartype =%d \n",year,yeartype);

	//得到现在的年份
	time(&timep);
	p_time=localtime(&timep);

	//年份的判断
	while((year>p_time->tm_year+1900)||(year<1900))
	{   
		printf("年份有问题,请输入正确的年份!!!\n");
		scanf("%d",&year);
	}

	//学年信息检查
	while(yeartype)
	{
		if(yeartype!=1)
		{
			printf("学年信息输入有问题,请输入正确的学年信息,即输入上半学年(0)或者下半学年(1)\n");
			scanf("%d",&yeartype);
		}
		else
			break;
	}

	//构建学期编号
	if(yeartype==0)
	{
		sprintf(yearinfo->stu_year_no,"%d01",year);
		sprintf(yearinfo->stu_year_name,"%d年上半学期",year);
	}
	else if(yeartype==1)
	{
		sprintf(yearinfo->stu_year_no,"%d02",year);
		sprintf(yearinfo->stu_year_name,"%d年下半学期",year);
	}

	//执行插入操作
	if(mysql_query(mysql, "set names \'utf8\'"))  //这个是关键 处理汉字的编码
	{
		printf("字符集:%s\n",mysql_error(mysql));
	}

	//修改某一列的字符编码格式
	if(mysql_query(mysql,"alter table year_info change stu_year_name stu_year_name varchar(20)  character  set utf8 NOT NULL;"))
	{
		printf("alter utf8 error\n");
	}


	sprintf(query,"insert into year_info(stu_year_no,stu_year_name) VALUES(\"%s\",\"%s\");",yearinfo->stu_year_no,yearinfo->stu_year_name);

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

//更新学期信息
void yearinfo_update(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int fields = 0;
	int row_count = 0;
	char oldyearno[MAXSIZE_TABLE][20] = {0};
	char yearno[MAXSIZE_TABLE][20] = {0};
	char yearname[MAXSIZE_TABLE][30] = {0};

	//查询数据表信息并显示
	init_sql(res,query,row);
	sprintf(query,"select * from year_info;");
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集

	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		fields=mysql_num_fields(res);
		if(row_count==0)
		{
			printf("学期信息:\n");
			printf("+----------+-------------+\n");
			printf("| year_no  |  year_name  |\n");
			printf("+----------+-------------+\n");
		}
		printf("|%-10s|%-12s|\n",row[fields-2],row[fields-1]);//左对齐
		strcpy(oldyearno[row_count],row[0]);
		strcpy(yearno[row_count],row[fields-2]);
		strcpy(yearname[row_count],row[fields-1]);
		row_count++;
	}
	printf("+----------+-------------+\n");

	if(row_count>0)
	{
		int row_ops = 0;
		int newyear = 0;
		char newyeartype[20] = {0};
		char c = '0';
		printf("现在有[%d]条学期信息记录,请选择你想要修改的学期记录数:",row_count);
		while((c=getchar())!='\n');//清空输入缓冲区 由于接收字符类型 如果输入多个数字字符,会导致错误的结果
		scanf("%d",&row_ops);
		printf("你选择了第[%d]条学期信息记录,学期编号[%s],学期名称[%s]\n",row_ops,yearno[row_ops],yearname[row_ops]);
		printf("请输入你想要修改后的年份:");
		scanf("%d",&newyear);
		printf("请输入你想要修改后的学年信息(上半学年/下半学年):");
		scanf("%s",newyeartype);

		time_t timep;//得到当前时间
		struct tm *p_time;

		//得到现在的年份
		time(&timep);
		p_time=localtime(&timep);

		//年份的判断
		while((newyear>p_time->tm_year+1900)||(newyear<1900))
		{   
			printf("年份有问题,请输入正确的年份!!!\n");
			scanf("%d",&newyear);
		}

		//学年信息检查
		while(strcmp(newyeartype,"上半学年"))
		{
			if(strcmp(newyeartype,"下半学年"))
			{
				printf("学年信息输入有问题,请输入正确的学年信息,即输入上半学年或者下半学年\n");
				scanf("%s",newyeartype);
			}
			else
				break;
		}

		//构建新学期编号
		if(!strcmp(newyeartype,"上半学年"))
		{
			sprintf(yearno[row_ops],"%d01",newyear);
			sprintf(yearname[row_ops],"%d年上半学期",newyear);
		}
		else if(!strcmp(newyeartype,"下半学年"))
		{
			sprintf(yearno[row_ops],"%d02",newyear);
			sprintf(yearname[row_ops],"%d年下半学期",newyear);
		}

		//唯一性检查
		bool is_only = true;
		for(int i=0;i<row_count;i++)//比较每一行的数据
		{
			if(i!=row_ops)
			{
				if(!strcmp(yearno[row_ops],yearno[i]))
				{
					printf("已经有相同的学期信息了");
					is_only = false;
					yearinfo_update(yearinfo,mysql,res,row,query);//递归调用
					break;
				}
			}
		}

		//更新操作
		if(is_only == true)
		{
			//执行更新
			sprintf(query,"update year_info set year_info.stu_year_no = \"%s\",year_info.stu_year_name = \"%s\"\
					where year_info.stu_year_no = \"%s\";",yearno[row_ops],yearname[row_ops],oldyearno[row_ops]);

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
	}
	else
	{
		printf("请先添加学期信息\n");
	}
}
void yearinfo_delete(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{

	int fields = 0;
	int row_count = 0;
	char yearno[MAXSIZE_TABLE][20]    = {0};
	char yearname[MAXSIZE_TABLE][20]  = {0};

	init_sql(res,query,row);
	sprintf(query,"select * from year_info;");
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集

	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		fields=mysql_num_fields(res);
		if(row_count==0)
		{
			printf("学期信息:\n");
			printf("+----------+-------------+\n");
			printf("| year_no  |  year_name  |\n");
			printf("+----------+-------------+\n");
		}
		printf("|%-10s|%-12s|\n",row[fields-2],row[fields-1]);//左对齐
		strcpy(yearno[row_count],row[fields-2]);
		strcpy(yearname[row_count],row[fields-1]);
		row_count++;
	}
	printf("+----------+-------------+\n");
	if(row_count>0)
	{
		int row_ops = 0;
		printf("现在有[%d]条学期信息记录,请选择你想要删除的学期记录数:",row_count);
		scanf("%d",&row_ops);

		printf("你选择了第[%d]条学期信息记录,学期编号[%s],学期名称[%s]\n",row_ops,yearno[row_ops],yearname[row_ops]);

		//执行删除操作
		sprintf(query,"delete from year_info where year_info.stu_year_no = \"%s\";",yearno[row_ops]);
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
	else
	{
		printf("请先添加学期信息\n");
	}
}

//查询学期信息
void yearinfo_select(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	int fields = 0;
	int row_count = 0;

	sprintf(query,"select * from year_info;");
	mysql_real_query(mysql,query,strlen(query));//执行sql语句
	res=mysql_store_result(mysql);//获取查询结果集

	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		fields=mysql_num_fields(res);
		if(row_count==0)
		{
			printf("学期信息:\n");
			printf("+----------+-------------+\n");
			printf("| year_no  |  year_name  |\n");
			printf("+----------+-------------+\n");
		}
		printf("|%-10s|%-12s|\n",row[fields-2],row[fields-1]);//左对齐
		row_count++;
	}
	printf("+----------+-------------+\n");
	if(row_count==0)
		printf("请先添加学期信息\n");
}
//管理学期信息的设置
void year_manager(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query)
{
	char ch;//输入的字符:1,2,3,4
	yearinfo_ui();                                                                                                                            
	printf("请输入你的选项:\n");
	while((ch = getchar()) != '0')
	{
		printf("file:%s  func:%s  line:%d\n",__FILE__,__FUNCTION__,__LINE__);
		if(ch == '\n')
			continue;
		switch(ch)
		{
			case '1':
				yearinfo_insert(yearinfo,mysql,res,row,query);//添加学期信息
				break;
			case '2':
				yearinfo_update(yearinfo,mysql,res,row,query);//更新学期信息
				break;
			case '3':
				yearinfo_delete(yearinfo,mysql,res,row,query);//删除学期信息
				break;
			case '4':
				yearinfo_select(yearinfo,mysql,res,row,query);//查询学期信息
				break;
			default:
				break;
		}
		yearinfo_ui();
	}

}

