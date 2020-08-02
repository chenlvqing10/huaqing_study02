#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <strings.h>
#define  DATABASE "student.db"

int callback(void * para ,int f_num,char **f_value,char **f_name){
	printf("para:%s\n",(char*)para);

	int i=0,j=0;
	//打印表头
	for(j=0;j<f_num;j++)
		printf("%-15s",f_name[j]);
	puts("");
	//打印搜索结果
	for(i=0;i<f_num;i++){
		if(!strncasecmp((char*)para,f_value[2],3))
			printf("%-15s",f_value[i]);
	}
	puts("");
	return 0;
}

void sql_insert(sqlite3* db,const char *sql,char* errmsg)
{

	if( sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		fprintf(stderr,"%s\n",errmsg);
		sqlite3_close(db);
		exit(-1);
	}
	else puts("----插入成功！");
}

void sql_select(sqlite3* db,const char *sql,char* errmsg)
{
#if 0//使用回调函数
	if( sqlite3_exec(db,"SELECT * FROM stu",callback,"man",&errmsg) != SQLITE_OK){
		fprintf(stderr,"%s\n",errmsg);
		sqlite3_close(db);            
		return 1;                     
	}                                 
	else puts("----查询成功！");      

#else //不使用回调函数
	char ** resultp = NULL;
	int nrow = -1;
	int ncolumn = -1;
	if( sqlite3_get_table(db,sql,
			&resultp,&nrow,&ncolumn,&errmsg) != SQLITE_OK){
		    fprintf(stderr,"%s\n",errmsg); 
			sqlite3_close(db);             
			exit(-1);                      
	}   
	else puts("---查询成功");       
	//打印表头
	int j = 0;
	for(j = 0;j<ncolumn;j++)
		printf("%-10s ",resultp[j]);
	puts("");
	
	//打印搜索结果
	int i = 0;
	int index = ncolumn;
	for(i=0;i<nrow;i++){
		for(j=0;j<ncolumn;j++)
			printf("%-10s ",resultp[index++]);
		putchar(10);
	}
	sqlite3_free_table(resultp);
#endif

}

 void sql_update(sqlite3* db,const char *sql,char* errmsg)
 {
     if( sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
     {   
         fprintf(stderr,"%s\n",errmsg);
         sqlite3_close(db);
         exit(-1);  
     }
     else puts("----更新成功！");

 }

 void sql_delete(sqlite3* db,const char *sql,char* errmsg)
 {
     if( sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
     {   
         fprintf(stderr,"%s\n",errmsg);
         sqlite3_close(db);
         exit(-1);
     }
     else puts("---删除成功！");
	
 }


int main(int argc, char *argv[])
{
	sqlite3 * db = NULL;

	if( sqlite3_open(DATABASE,&db) != SQLITE_OK){
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(1);
	}
	else puts("------打开或创建数据库成功");

	char * errmsg = NULL;
	//char * create_table = "CREATE TABLE if not exists stu(id int primary key,name char,sex char,score int)";
	char * create_table = "CREATE TABLE if not exists stu(id int,name char,sex char,score int)";
	if( sqlite3_exec(db,create_table,NULL,NULL,&errmsg) != SQLITE_OK){
		fprintf(stderr,"%s\n",errmsg);
		sqlite3_close(db);
		return 1;
	}
	else puts("----创建或打开stu表成功！");

	/*实现增删改查*/
	char c;
	char* sql;
	printf("/***************1.插入操作  增*******************************************************/\n");
	printf("/***************2.查询操作  查*******************************************************/\n");
	printf("/***************3.更新操作  改*******************************************************/\n");
	printf("/***************4.删除操作  删*******************************************************/\n");
	printf("/***************5.退出系统  退出*******************************************************/\n");

	while((c=getchar() )!= '5')
	{
		switch(c)
		{
			case '1':
				printf("进行插入操作\n");
				sql="INSERT INTO stu VALUES(009,'aaacccc','man',22);";
				sql_insert(db,sql,errmsg);
				break;
			case '2':
				printf("进行查询操作\n");
				sql="SELECT * FROM stu";
				sql_select(db,sql,errmsg);
				break;
			case '3':
				printf("进行修改操作\n");
				sql="UPDATE stu set name='nihaoaaa' where id=9;";
				sql_update(db,sql,errmsg);
				break;
			case '4':
				printf("进行删除操作\n");
				sql="DELETE FROM stu where id=9;";
				sql_delete(db,sql,errmsg);
				break;
			case '5':
				printf("退出系统\n");
				break;
			default:
				break;
		}
	}



	



	if( sqlite3_close(db) != SQLITE_OK){
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(1);
	}
	else puts("-----关闭数据库成功！");
	return 0;
}


