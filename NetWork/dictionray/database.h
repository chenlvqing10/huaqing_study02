#ifndef __DATABASE__
#define __DATABASE__

#include "wrap.h"
#include <sqlite3.h>/*数据库头文件*/
#include <stdbool.h>/*布尔值头文件*/
#include <time.h>/*时间的头文件*/
typedef struct userinfo//用户信息结构体
{
	char username[20];//用户名
	char password[10];//密码
	char current_pwd[10];//确认密码
} userinfo_t;

typedef struct historyinfo
{
	int  historyno;//历史记录数
	char timeinfo[50];//历史记录时间戳
	int  opertype;//操作类型
	char oper[200];//历史操作信息:  用户注册信息　用户登录细信息　　查询单词记录
}historyinfo_t;

 #define  DATABASE "wordselect.db"//定义数据库

void user_login_regist_menu();
void user_operator_menu();


/*数据库函数*/
void Open_Database(sqlite3* db);
void Create_tables(sqlite3* db,const char* sql,char* errmsg);
void Close_Database(sqlite3* db);
bool User_Regist(sqlite3* db,char* sql,userinfo_t* userinfo,char* errmsg);
int  User_login(sqlite3* db,char* sql,userinfo_t* userinfo,char* errmsg);
void sql_insert(sqlite3* db,char *sql,char* errmsg);
void set_history(sqlite3* db,char* sql,userinfo_t* userinfo,historyinfo_t* historyinfo,char* errmsg,char c,int status,char* ptr_tmsg,char* word,char* explain);
char* get_timemsg(char* ptr_tmsg);
int get_historyRow(sqlite3* db,char* sql,char* errmsg);//获取查询记录行数
void select_historyinfo(sqlite3* db,char* sql,char* errmsg);

char* get_buffer(char *name,char *password,char *current_pwd,char c);

#endif
