/*这是学生管理系统的头文件*/

/*引用mysql数据库的头文件*/
#include "/usr/include/mysql/mysql.h"

/*标准C的头文件*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
/*Linux的头文件*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <error.h>

char login_status='0';       //登录状态 0--未登录  1--登录成功

/*定义结构体变量 处理数据表中的字段*/

//用户信息结构体
typedef struct user_info
{
	char user_no[7];		//用户ID  1位用户类型+6位编号
	char username[12];		//用户名
	char passwd[10];		//用户密码
	int  usertype;			//用户类型 0---管理员用户  1---学生用户
}user_info_t;  

//管理员信息结构体
typedef struct admin_info
{
	char     admin_no[11];		//4位年份+2位入校月份+2位编号  11
	char	 admin_name[12];	//管理员姓名                   12
	char     gender[2];			//性别                        2
	int		 admin_age;			//管理员年龄                  4
	char	 college_no[8];		//4位学院编号  与学院编信息结构体关联 4
	char     user_no[10];		//用户ID  1位用户类型+6位编号          7
}admin_info_t;

//学生信息结构体
typedef struct stu_info
{
	char	  stu_no[8];			//4位年份+2位入校月份+2位编号
	char	  stu_name[12];			//学生姓名
	char	  gender[2];			//性别
	int		  stu_age;				//学生年龄
	int		  stu_grade;			//年级  2015 2016 2017
	int		  stu_class;			//班级  1--1班  2--2班 3--3班
	char      college_no[4];		//4位学院编号 与学院信息结构体关联
	char      user_no[7];		//用户ID  1位用户类型+6位编号
}stu_info_t;

//学生学期科目表
typedef struct stu_sub
{
	char	  stu_no[8];			//4位年份+2位入校月份+2位编号
	char	  stu_year[6];			//201501--2015年上半学期  201502--2015年下半学期
	char      stu_sub_no1[4];		//科目编号1
	char      stu_sub_no2[4];		//科目编号2
	char      stu_sub_no3[4];		//科目编号3
	char      stu_sub_no4[4];		//科目编号4
	char      stu_sub_no5[4];		//科目编号5
	char      stu_sub_no6[4];		//科目编号6
	char      stu_sub_no7[4];		//科目编号7
	char      stu_sub_no8[4];		//科目编号8
	char      stu_sub_no9[4];		//科目编号9
	char      stu_sub_no10[4];		//科目编号10
	char      stu_sub_no11[4];		//科目编号11
	char      stu_sub_no12[4];		//科目编号12
}stu_sub_t;

//学生学期成绩表
typedef struct stu_score
{
	char	 stu_no[8];				//4位年份+2位入校月份+2位编号
	char	 stu_year[6];			//201501--2015年上半学期  201502--2015年下半学期
	int      sub_no1_sc[4];			//科目编号1成绩
	int      sub_no2_sc[4];			//科目编号2成绩
	int      sub_no3_sc[4];			//科目编号3成绩
	int      sub_no4_sc[4];			//科目编号4成绩
	int      sub_no5_sc[4];			//科目编号5成绩
	int      sub_no6_sc[4];			//科目编号6成绩
	int      sub_no7_sc[4];			//科目编号7成绩
	int      sub_no8_sc[4];			//科目编号8成绩
	int      sub_no9_sc[4];			//科目编号9成绩
	int      sub_no10_sc[4];		//科目编号10成绩
	int      sub_no11_sc[4];		//科目编号11成绩
	int      sub_no12_sc[4];		//科目编号12成绩
}stu_score_t;

//学院信息表
typedef struct college_info
{
	char     college_no[4];			//学院编号
	char     college_name[20];		//学院名称
}college_info_t;

//专业信息表
typedef struct profs_info
{
	char	 profs_no[4];			//专业编号
	char	 profs_name[20];		//专业名称
	char	 college_no[4];			//学院编号
}profs_info_t;

//专业科目表
typedef struct sub_info
{
	char	 sub_no[4];				//科目编号
	char	 sub_name[20];			//科目名称
	char	 profs_no[4];			//专业编号
}sub_info_t;

//初始化数据库变量
void init_sql(MYSQL_RES *res,char *query,MYSQL_ROW row);
//自动生成各数据表的编号
char* get_tableno(MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char* pt_tableno,int tableno,char* name);

//用户管理模块
void user_manager(user_info_t *userinfo,MYSQL *mysql);//用户管理模块
void user_regist(user_info_t *userinfo,MYSQL *mysql,int usertype);//用户注册模块

//管理员模块
void admin_manager(user_info_t *usernifo,MYSQL *mysql);//管理员模块

//学院信息管理模块
bool check_college_empty(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
void college_manager(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);

//学生管理模块
void stu_manager(user_info_t *userinfo,MYSQL *mysql);
