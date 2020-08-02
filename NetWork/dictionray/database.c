#include "database.h"

void user_login_regist_menu()
{
	printf("/**************************用户登录和注册界面************************************************/\n");
	printf("/**************************按1:用户注册******************************************************/\n");
	printf("/**************************按2:用户登录******************************************************/\n");
	printf("/**************************按0:退出系统******************************************************/\n");
}

void user_operator_menu()
{
	printf("/**************************用户操作界面******************************************************/\n");
	printf("/**************************按3:单词查询******************************************************/\n");
	printf("/**************************按4:操作记录查询**************************************************/\n");
	printf("/**************************按0:退出系统******************************************************/\n");
}


void Open_Database(sqlite3* db)//打开数据库
{
	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{   
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else  ;
		//puts("------打开或创建数据库成功");
}

void Create_tables(sqlite3* db,const char* sql,char* errmsg)//创建数据库表
{
	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else
		//puts("------打开或创建数据库成功");

	if( sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		fprintf(stderr,"创建数据表失败:%s\n",errmsg);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	else ; 
		//puts("----创建或打开数据表成功！");
}

void Close_Database(sqlite3* db)//关闭数据库
{
	if( sqlite3_close(db) != SQLITE_OK){
		fprintf(stderr,"----关闭数据库失败：%s\n",sqlite3_errmsg(db));
		exit(1);
	}
	else 
		puts("-----关闭数据库成功！");
}

void sql_insert(sqlite3* db,char *sql,char* errmsg)
{
	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else
		//puts("------打开或创建数据库成功");

	if( sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{   
		fprintf(stderr,"插入失败%s\n",errmsg);
		sqlite3_close(db);
		exit(-1);
	}
	else 
		puts("----插入成功！");
	/* 
	   if( sqlite3_close(db) != SQLITE_OK){
	   fprintf(stderr,"----关闭数据库失败：%s\n",sqlite3_errmsg(db));
	   exit(1);
	   }
	   else puts("-----关闭数据库成功！");
	   */
}



/*用户注册*/
bool User_Regist(sqlite3* db,char* sql,userinfo_t* userinfo,char* errmsg)
{
	bool isregist=false;

	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else ;
		//puts("------打开或创建数据库成功");

	char ** dbResult = NULL;//查询结果集
	int nRow = -1;//查找出的总行数
	int nColumn = -1; //nColumn 存储列
	sql="SELECT * FROM userinfo;";

	//得到数据表中的查询结果放到二维指针dbResult中
	if(sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errmsg) != SQLITE_OK)
	{
		fprintf(stderr,"---查询失败%s\n",errmsg); 
		sqlite3_close(db);             
		exit(-1);                      
	}   
	else
		puts("---查询成功");

	//printf("行数nRow=%d  列数nColum=%d\n",nRow,nColumn);

	//打印表头
	for(int j = 0;j<nColumn;j++)//列数
		//printf("%-10s ",dbResult[j]);
	printf("\n");

	//打印搜索结果
	int index = nColumn;//index=
	bool isusername=false;
	bool ispwd_same=false;
	for(int i=0;i<nRow;i++)//行数
	{
		for(int j=0;j<nColumn;j++)//列数
		{
			//printf("%-10s ",dbResult[index]);//第一行记录
			if(index%2==0)//判断用户名
			{
				//printf("dbResult[index]=%s\n",dbResult[index]);
				//printf("userinfo->username=%s  userinfo->password=%s  userinfo->current_pwd=%s \n",userinfo->username,userinfo->password,userinfo->current_pwd);
				if(strcmp(userinfo->username,dbResult[index])==0)
				{
					isusername=true;
					break;
				}
			}
			index++;

		}
		//printf("\n");
		if(isusername==true)
			break;
	}

	if(strcmp(userinfo->password,userinfo->current_pwd)==0)
	{
		ispwd_same=true;
	}

	//printf("isusername=%d  ispwd_same=%d\n",isusername,ispwd_same);

	if(isusername==true)
	{
		printf("用户名一样，请按1重新输入\n");
	}

	if(ispwd_same==false)
	{
		printf("密码和确认密码不一致，请按1重新输入\n");
	}

	if((isusername==false)&&(ispwd_same==true))//进行数据库插入操作
	{
		char sql_ist[100]={0};
		sprintf(sql_ist,"INSERT INTO userinfo VALUES(\"%s\",\"%s\");",userinfo->username,userinfo->password);
		//printf("sql_insert=%s\n",sql_ist);
		sql_insert(db,sql_ist,errmsg);
		isregist=true;
	}
/*
	sqlite3_free_table(dbResult);
	if( sqlite3_close(db) != SQLITE_OK){
		fprintf(stderr,"----关闭数据库失败：%s\n",sqlite3_errmsg(db));
		exit(1);
	}
	else puts("-----关闭数据库成功！");
*/
	return isregist;
}

/*用户登录   返回值:用户登录状态　　　0-----用户名不存在    1---------密码错误   2--------登录成功*/
int User_login(sqlite3* db,char* sql,userinfo_t* userinfo,char* errmsg)
{
	bool islogin=false;
	int  loginstatus=-1;//用户登录状态
	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else ;
		//puts("------打开或创建数据库成功");

	char ** dbResult = NULL;//查询结果集
	int nRow = -1;//查找出的总行数
	int nColumn = -1; //nColumn 存储列
	sql="SELECT * FROM userinfo;";

	//得到数据表中的查询结果放到二维指针dbResult中
	if(sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errmsg) != SQLITE_OK)
	{
		fprintf(stderr,"---查询失败%s\n",errmsg); 
		sqlite3_close(db);             
		exit(-1);                      
	}   
	else
		puts("---查询成功");

	//printf("行数nRow=%d  列数nColum=%d\n",nRow,nColumn);

	//打印表头
	for(int j = 0;j<nColumn;j++)//列数
		//printf("%-10s ",dbResult[j]);
	printf("\n");


	int index1 = nColumn;//index=
	for(int i=0;i<nRow;i++)//行数
   {
       for(int j=0;j<nColumn;j++)//列数
       {   
           //printf("%-10s ",dbResult[index1]);//第一行记录
           index1++;
       }
       //printf("\n");
   }

	//打印搜索结果
	int index = nColumn;//index=
	bool isusername=false;
	//bool ispwd_same=false;
	for(int i=0;i<nRow;i++)//行记录
	{
		//printf("%-10s",dbResult[index]);//第一行记录
		if(strcmp(userinfo->username,dbResult[index])==0)
		{
			isusername=true;
		}

		if((strcmp(userinfo->username,dbResult[index++])==0)&&(strcmp(userinfo->password,dbResult[index])==0))
		{
			islogin=true;
			break;
		}
		index++;
		//printf("index=%d\n",index);	
	}


	//printf("islogin=%d\n",islogin);

	if((islogin==false)&&(isusername==true))
	{
		printf("密码输入错误,请重新输入\n");
		loginstatus=1;
	}
	else if(islogin==true)//用户登录成功
	{
		printf("用户登录成功\n");
		loginstatus=2;
	}
	else
	{
		printf("用户名不存在,请按1先注册\n");
		loginstatus=0;
	}

	/*
	sqlite3_free_table(dbResult);
	if( sqlite3_close(db) != SQLITE_OK){
		fprintf(stderr,"----关闭数据库失败：%s\n",sqlite3_errmsg(db));
		exit(1);
	}
	else puts("-----关闭数据库成功！");
	*/
	return loginstatus;
}
char* get_buffer(char *name,char *password,char* current_pwd,char c)
{
	char buffer[BUFSIZ]={0};
	char *ptr_buf=NULL;

	//printf("call the get_buffer\n");

	if((name!=NULL)||(password!=NULL))
	{
		printf("用户名:\n");
		scanf("%s",name);
		printf("name=%s\n",name);

		printf("密码:\n");
		scanf("%s",password);
		printf("password=%s\n",password);
	}

	if(current_pwd!=NULL)
	{
		printf("确认密码:\n");
		scanf("%s",current_pwd);
		printf("current_pwd=%s\n",current_pwd);
		sleep(1);
	}
	//客户端将数据发送给服务端
	if(current_pwd!=NULL)
	{
		sprintf(buffer,"%c %s %s %s",c,name,password,current_pwd);
		//printf("buffer=%s\n",buffer);
	}
	else
	{
		sprintf(buffer,"%c %s %s",c,name,password);
		//printf("buffer=%s\n",buffer);
	}
	ptr_buf=buffer;

	//printf("ptr_buf=%s\n",ptr_buf);

	return ptr_buf;
}

char* get_timemsg(char* ptr_tmsg)
{
	ptr_tmsg=NULL;
	char time_msg[30]={0};
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	sprintf(time_msg,"%d-%02d-%02d %02d:%02d:%02d\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
	//printf("time_msg=%s\n",time_msg);
	time_msg[strlen(time_msg)-1]='\0';
	ptr_tmsg=time_msg;

	return ptr_tmsg;
}

//将历史记录,存在历史记录表里
void set_history(sqlite3* db,char* sql,userinfo_t* userinfo,historyinfo_t* historyinfo,char* errmsg,char c,int status,char* ptr_tmsg,char* ptr_word,char* ptr_explain)
{
//	printf("time_msg=%s\n",ptr_tmsg);
	char hword[100]={0};
	char hexplain[100]={0};

	if((ptr_word!=NULL)&&(ptr_explain!=NULL))
	{
		strcpy(hword,ptr_word);
		strcpy(hexplain,ptr_explain);
	}

	strcpy(historyinfo->timeinfo,ptr_tmsg);
	
	
	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else ;
		//puts("------打开或创建数据库成功");
	
	char ** dbResult = NULL;//查询结果集
	int nRow = -1;//查找出的总行数
	int nColumn = -1; //nColumn 存储列

	//得到数据表中的查询结果放到二维指针dbResult中
	sql="SELECT historyno FROM historyinfo;";
	if(sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errmsg) != SQLITE_OK)
	{
		fprintf(stderr,"---查询失败%s\n",errmsg); 
		sqlite3_close(db);             
		exit(-1);                      
	}   
	else
		puts("---查询成功");

	//printf("nRow=%d   nColumn=%d\n",nRow,nColumn);

	/*自动得到历史记录条数*/
	if(nRow==0)//没有查询结果
		historyinfo->historyno=0;
	else
	{	
		//打印搜索结果
		int index = nColumn;//index=
		for(int i=0;i<nRow;i++)//行记录
		{
			//printf("no=%-10s\n",dbResult[index]);
			historyinfo->historyno=atoi(dbResult[index++]);
		}
	}
	
	//printf("historyno=%d\n",historyinfo->historyno);
	historyinfo->historyno=historyinfo->historyno+1;
	//printf("historyno=%d\n",historyinfo->historyno);

	if(c=='1')//用户注册记录
	{
		historyinfo->opertype=1;
		if(status==0)//用户注册失败记录
		{
			sprintf(historyinfo->oper,"%s  user regist failed username=%s  passwd=%s  current_pwd=%s",historyinfo->timeinfo,userinfo->username,userinfo->password,userinfo->current_pwd);
			//printf("historyinfo->timeinfo=%s   historyinfo->opertype=%d  historyinfo->oper=%s\n",historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
		}
		else if(status==1)//用户注册成功记录
		{
			sprintf(historyinfo->oper,"%s  user regist success username=%s  passwd=%s  current_pwd=%s",historyinfo->timeinfo,userinfo->username,userinfo->password,userinfo->current_pwd);
			//printf("historyinfo->timeinfo=%s   historyinfo->opertype=%d  historyinfo->oper=%s\n",historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
		}
	}
	else if(c=='2')//用户登录记录
	{
		historyinfo->opertype=2;
		if(status==0)//用户名不存在
		{
			sprintf(historyinfo->oper,"%s  user login failed(no username) username=%s  passwd=%s",historyinfo->timeinfo,userinfo->username,userinfo->password);
			//printf("historyinfo->timeinfo=%s   historyinfo->opertype=%d  historyinfo->oper=%s\n",historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
		}
		else if(status==1)//密码错误
		{
			sprintf(historyinfo->oper,"%s  user login failed(password is error) username=%s  passwd=%s",historyinfo->timeinfo,userinfo->username,userinfo->password);
			//printf("historyinfo->timeinfo=%s   historyinfo->opertype=%d  historyinfo->oper=%s\n",historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
		}
		else if(status==2)//登录成功
		{
			sprintf(historyinfo->oper,"%s  user login success username=%s  passwd=%s",historyinfo->timeinfo,userinfo->username,userinfo->password);
			//printf("historyinfo->timeinfo=%s   historyinfo->opertype=%d  historyinfo->oper=%s\n",historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
		}
	}
	else if(c=='3')//单词查询记录
	{
		historyinfo->opertype=3;
		sprintf(historyinfo->oper,"%s  word select word=%s  explain=%s",historyinfo->timeinfo,hword,hexplain);
		//printf("historyinfo->timeinfo=%s   historyinfo->opertype=%d  historyinfo->oper=%s\n",historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
	}

	//执行插入操作
	char sql_ist[BUFSIZ]={0};
	sprintf(sql_ist,"INSERT INTO historyinfo VALUES(%d,\"%s\",%d,\"%s\");",historyinfo->historyno,historyinfo->timeinfo,historyinfo->opertype,historyinfo->oper);
	//printf("sql_ist=%s\n",sql_ist);
	sql_insert(db,sql_ist,errmsg);

/*
	if( sqlite3_close(db) != SQLITE_OK){

		fprintf(stderr,"----关闭数据库失败：%s\n",sqlite3_errmsg(db));
		exit(1);
	}
	else puts("-----关闭数据库成功！");
	*/
}

int get_historyRow(sqlite3* db,char* sql,char* errmsg)
{
    if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
    {   
        fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }
    else ;
       // puts("------打开或创建数据库成功");
    
    char ** dbResult = NULL;//查询结果集
    int nRow = -1;//查找出的总行数
    int nColumn = -1; //nColumn 存储列
    sql="SELECT * FROM historyinfo;";
    
    //得到数据表中的查询结果放到二维指针dbResult中
    if(sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errmsg) != SQLITE_OK)
    {
        fprintf(stderr,"---查询失败%s\n",errmsg);
        sqlite3_close(db);
        exit(-1);
    }   
    else
        puts("---查询成功");

   // printf("行数nRow=%d  列数nColum=%d\n",nRow,nColumn);
	return nRow;
}


void select_historyinfo(sqlite3* db,char* sql,char* errmsg)
{
	if( sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		fprintf(stderr,"----打开数据库失败：%s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else ;
		//puts("------打开或创建数据库成功");

	char ** dbResult = NULL;//查询结果集
	int nRow = -1;//查找出的总行数
	int nColumn = -1; //nColumn 存储列
	sql="SELECT * FROM historyinfo;";

	//得到数据表中的查询结果放到二维指针dbResult中
	if(sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errmsg) != SQLITE_OK)
	{
		fprintf(stderr,"---查询失败%s\n",errmsg); 
		sqlite3_close(db);             
		exit(-1);                      
	}   
	else
		puts("---查询成功");

	//printf("行数nRow=%d  列数nColum=%d\n",nRow,nColumn);

	//打印表头
	for(int j = 0;j<nColumn;j++)//列数
		printf("%-15s ",dbResult[j]);
	printf("\n");

	//打印搜索结果
	int index = nColumn;//index=
	for(int i=0;i<nRow;i++)//行记录
	{
		for(int j=0;j<nColumn;j++)
		{
			printf("%-10s",dbResult[index++]);//第一行记录
		}
		printf("\n");	
	}
}
