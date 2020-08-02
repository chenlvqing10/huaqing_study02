#include "head.h"

//将自动生成编号的函数进行封装  根据数据表的不同，而进行不同的编号生成
//tableno=1  用户表 学生用户   tableno=2 用户表 管理员用户  tableno=3  学院信息表 
char* get_tableno(MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char* pt_tableno,int tableno,char* name)
{  
	int fields=0;
	if(tableno==1)
	{
		sprintf(query,"select user_info.user_no from user_info where usertype=1;");//学生用户编号
	}
	else if(tableno==2)
	{
		sprintf(query,"select user_info.user_no from user_info where usertype=2;");//管理员用户编号
	}
	else if(tableno==3)
	{
		sprintf(query,"select college_info.college_no from college_info;");//学院编号
	}
	else if(tableno==4)
	{
		sprintf(query,"select admin_info.admin_no from admin_info;");
	}
	else if(tableno==5)
	{
		if(name!=NULL)
		{
			mysql_query(mysql, "set names \'utf8\'");
			sprintf(query,"select college_no from college_info where college_name=\"%s\";",name);
			printf("sql语句:%s\n",query);

		}
	}



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


	while((row=mysql_fetch_row(res))!=NULL) //一行一行取得查询结果集数据    行数就是循环次数
	{
		printf("取得数据成功!!!\n");
		//统计字段名个数(列数)
		fields=mysql_num_fields(res);
		//将数据copy到tableno指针指向的内存
		for(int i=0; i<fields; i++)//行
		{
			strcpy(pt_tableno,row[i]);
		}                  
	}

	if((tableno==3))//学院编号  需要进行一定的形式转换
	{
		if((atoi(pt_tableno)>=0)&&(atoi(pt_tableno)<=9))
			sprintf(pt_tableno,"000%d",atoi(pt_tableno)+1);
		else if((atoi(pt_tableno)>=10)&&(atoi(pt_tableno)<=99))
			sprintf(pt_tableno,"00%d",atoi(pt_tableno)+1);
		else if((atoi(pt_tableno)>=100)&&(atoi(pt_tableno)<=999))
			sprintf(pt_tableno,"0%d",atoi(pt_tableno)+1);
	}
	else if((tableno==1)||(tableno==2))
	{
		sprintf(pt_tableno,"%d",atoi(pt_tableno)+1);
	}
	else if(tableno==4)
	{
		char src[4]={0};
		strncpy(src,pt_tableno+6,2);
		strcpy(pt_tableno,src);
		if((atoi(pt_tableno)>=0)&&(atoi(pt_tableno)<=9))
			sprintf(pt_tableno,"0%d",atoi(pt_tableno)+1);
		else
			sprintf(pt_tableno,"%d",atoi(pt_tableno)+1);
	}
	printf("最新的编号:%s\n",pt_tableno);

	init_sql(res,query,row);	
	return pt_tableno;
}




