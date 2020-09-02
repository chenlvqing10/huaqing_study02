#include "head.h"

//将自动生成编号的函数进行封装  根据数据表的不同，而进行不同的编号生成
//tableno=1  用户表 学生用户   tableno=2 用户表 管理员用户  tableno=3  学院信息表  tableno=4 管理员编号　　tableno=5  学生编号 
char* get_tableno(MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char* pt_tableno,int tableno,char* name)
{  
	int maxid  = 0;//得到最大的编号

	if(tableno==GET_USERNO_STUDENT)
	{
		sprintf(query,"select user_info.user_no from user_info where usertype=1;");//学生用户编号
	}
	else if(tableno==GET_USERNO_ADMIN)
	{
		sprintf(query,"select user_info.user_no from user_info where usertype=2;");//管理员用户编号
	}
	else if(tableno==GET_COLLEGENO)
	{
		sprintf(query,"select college_info.college_no from college_info;");//学院编号
	}
	else if(tableno==GET_ADMINNO)
	{
		sprintf(query,"select admin_info.admin_no from admin_info;");//管理员编号
	}
	else if(tableno==GET_COLLEGENOBYNAME)
	{
		if(name!=NULL)
		{
			mysql_query(mysql, "set names \'utf8\'");
			sprintf(query,"select college_no from college_info where college_name=\"%s\";",name);//根据学院名字获得学院编号
		}
		else
		{
			printf("学院名字为空\n");
			return NULL;
		}
	}
	else if(tableno==GET_STUNO)//学生编号
	{
		sprintf(query,"select stu_no from stu_info;");
	}
	else if(tableno==GET_PROFSNO)//专业编号
	{
		sprintf(query,"select profs_info.profs_no from profs_info;");
	}
	else if(tableno==GET_SUBNO)
	{
		sprintf(query,"select sub_info.sub_no from sub_info;");
	}


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
		printf("取得数据成功!!!\n");
		strcpy(pt_tableno,row[0]);
		printf("pt_tableno=%s\n",pt_tableno);//得到最后的编号
		maxid =(atoi(pt_tableno) > maxid)?atoi(pt_tableno):maxid;
	}
	
	printf("maxid = %d\n",maxid);
	sprintf(pt_tableno,"%d",maxid);
	printf("pt_tableno=%s\n",pt_tableno);//得到最后的编号

	if((tableno == GET_COLLEGENO) || (tableno == GET_COLLEGENOBYNAME) || (tableno == GET_PROFSNO) || (tableno == GET_SUBNO))//学院编号/专业编号/科目编号  需要进行一定的形式转换
	{
		if(strcmp(pt_tableno,"") == 0)//空字符串
		{
			strcpy(pt_tableno,"0001");
		}
		else
		{
			if((atoi(pt_tableno)>=0)&&(atoi(pt_tableno)<=8))//0001--0009
				sprintf(pt_tableno,"000%d",atoi(pt_tableno)+1);
			else if((atoi(pt_tableno)>=9)&&(atoi(pt_tableno)<=98))//0010---0099
				sprintf(pt_tableno,"00%d",atoi(pt_tableno)+1);
			else if((atoi(pt_tableno)>=99)&&(atoi(pt_tableno)<=998))//0100--0999
				sprintf(pt_tableno,"0%d",atoi(pt_tableno)+1);
		}
	}
	else if((tableno==GET_USERNO_STUDENT)||(tableno==GET_USERNO_ADMIN))//处理用户编号
	{
		if(strcmp(pt_tableno,"")==0)//空字符串
		{
			if(tableno == GET_USERNO_STUDENT)
			{
				strcpy(pt_tableno,"1000001");
			}
			else
			{
				strcpy(pt_tableno,"2000001");
			}
			printf("pt_tableno=%s\n",pt_tableno);//得到最后的编号
		}
		else
		{
			sprintf(pt_tableno,"%d",atoi(pt_tableno)+1);
		}
	}
	else if((tableno==GET_ADMINNO) || (tableno==GET_STUNO))//管理员编号和学生编号　年份+月份+取最后两位
	{
		if(strcmp(pt_tableno,"")==0)//空字符串
		{
			strcpy(pt_tableno,"01");
		}
		else
		{
			char src[4]={0};
			strncpy(src,pt_tableno+6,2);//取出最后两位放入src
			strcpy(pt_tableno,src);//赋值给pt_tableno

			if((atoi(pt_tableno)>=0)&&(atoi(pt_tableno)<=8))
				sprintf(pt_tableno,"0%d",atoi(pt_tableno)+1);
			else
				sprintf(pt_tableno,"%d",atoi(pt_tableno)+1);
		}
	}

	printf("最新的编号:%s\n",pt_tableno);
	init_sql(res,query,row);	
	return pt_tableno;
}




