/*这是学生管理系统的头文件*/

/*可以改进的点*/
/*采取c-s模型 网络编程*/
/*功能添加:历史记录查询*/
/*业务逻辑改进:学生成绩类型--期中成绩 期末成绩等*/
/*qt界面实现*/


/*错误*/
//1.stack溢出  分配的栈内存太小   char query[500]  实际上sql语句有超过500的可能 
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
	char user_no[10];		//用户ID  1位用户类型+6位编号
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
	char	  stu_no[9];			//4位年份+2位入校月份+2位编号
	char	  stu_name[12];			//学生姓名
	char	  gender[4];			//性别
	int		  stu_age;				//学生年龄
	int		  stu_grade;			//年级  2015 2016 2017
	int		  stu_class;			//班级  1--1班  2--2班 3--3班
	char      college_no[5];		//4位学院编号 与学院信息结构体关联
	char      profs_no[5];          //4位专业编号 与专业信息结构体关联
	char      user_no[8];		    //用户ID  1位用户类型+6位编号
}__attribute__ ((__packed__)) stu_info_t;

//学生学期科目表
typedef struct stu_sub   //科目计数用的变量
{
	char	  stu_no[9];			//4位年份+2位入校月份+2位编号  设计的时候要多增加一位作为'\0'
	char	  stu_year_no[7];		//201501--2015年上半学期  201502--2015年下半学期
	char      stu_sub_no1[5];		//科目编号1
	char      stu_sub_no2[5];		//科目编号2
	char      stu_sub_no3[5];		//科目编号3
	char      stu_sub_no4[5];		//科目编号4
	char      stu_sub_no5[5];		//科目编号5
	char      stu_sub_no6[5];		//科目编号6
	char      stu_sub_no7[5];		//科目编号7
	char      stu_sub_no8[5];		//科目编号8
	char      stu_sub_no9[5];		//科目编号9
	char      stu_sub_no10[5];		//科目编号10
	char      stu_sub_no11[5];		//科目编号11
	char      stu_sub_no12[5];		//科目编号12
	char      college_no[5];        //4位学院编号 与学院信息结构体关联
    char      profs_no[5];          //4位专业编号 与专业信息结构体关联
}__attribute__ ((__packed__)) stu_sub_t;

//学生学期成绩表
typedef struct stu_score
{
	char	 stu_no[9];				//4位年份+2位入校月份+2位编号
	char	 stu_year_no[7];		//201501--2015年上半学期  201502--2015年下半学期
	int      sub_no1_sc;			//科目编号1成绩
	int      sub_no2_sc;			//科目编号2成绩
	int      sub_no3_sc;			//科目编号3成绩
	int      sub_no4_sc;			//科目编号4成绩
	int      sub_no5_sc;			//科目编号5成绩
	int      sub_no6_sc;			//科目编号6成绩
	int      sub_no7_sc;			//科目编号7成绩
	int      sub_no8_sc;			//科目编号8成绩
	int      sub_no9_sc;			//科目编号9成绩
	int      sub_no10_sc;		//科目编号10成绩
	int      sub_no11_sc;		//科目编号11成绩
	int      sub_no12_sc;		//科目编号12成绩
	char     college_no[5];        //4位学院编号 与学院信息结构体关联
    char     profs_no[5];          //4位专业编号 与专业信息结构体关联
}__attribute__ ((__packed__)) stu_score_t;


//学院信息表
typedef struct college_info
{
	char     college_no[5];			//学院编号
	char     college_name[20];		//学院名称
}college_info_t;

//专业信息表
typedef struct profs_info
{
	char	 profs_no[5];			//专业编号
	char	 profs_name[40];		//专业名称
	char	 college_no[4];			//学院编号
}profs_info_t;

//专业科目表
typedef struct sub_info
{
	char	 sub_no[5];				//科目编号
	char	 sub_name[30];			//科目名称
	char	 profs_no[4];			//专业编号
}sub_info_t;

typedef struct year_info
{
	char	 stu_year_no[7];        //学期编号
	char     stu_year_name[20];     //学期名称
}year_info_t;

//一些宏定义
#define   USERREGST           14
#define   USERLOGIN		      15
#define   USERINFOMANAGER     16

#define   USERTYPE_STUDENT	  1//学生账户类型---注册
#define   USERTYPE_ADMIN      2//管理员账户----注册
#define   USERTYPE_OTHER      3//用于用户登录---注册

#define   LOGINTYPE_STUDENT   1//学生登录用户
#define   LOGINTYPE_ADMIN     2//管理员登录用户
#define   LOGINTYPE_OTHER     3//用于用户登录----登录

#define   OPTYPE_ADMIN_STU_SELECT			1
#define   OPTYPE_ADMIN_STU_UPDATE			2
#define   OPTYPE_ADMIN_STU_DELETE			3
#define   OPTYPE_ADMIN_STU_INSERT			4
#define   OPTYPE_ADMIN_STU_SUBJECT			5
#define   OPTYPE_ADMIN_STU_SCORE			6
#define   OPTYPE_ADMIN_STU_SUBINFO_SELECT   7
#define   OPTYPE_STUDENT_STU_SELECT			8
#define   OPTYPE_STUDENT_STU_UPDATE			9
#define   OPTYPE_STUDENT_STU_SUBINFO		10
#define   OPTYPE_STUDENT_STU_INSERT		    11

#define    GET_USERNO_STUDENT    1          //学生用户编号
#define    GET_USERNO_ADMIN      2          //管理用户编号
#define    GET_COLLEGENO         3          //学院编号
#define    GET_ADMINNO           4			//管理员编号
#define    GET_COLLEGENOBYNAME   5          //根据学院名字获取管理员编号
#define    GET_STUNO             6			//学生编号
#define    GET_PROFSNO           7			//专业编号
#define    GET_SUBNO             8			//科目编号

#define    MAXSIZE_TABLE  100//数据表中行数

#define   SUPERUSERID   "2000000"

//初始化数据库变量
void init_sql(MYSQL_RES *res,char *query,MYSQL_ROW row);
//自动生成各数据表的编号
char* get_tableno(MYSQL* mysql,MYSQL_RES* res,MYSQL_ROW row,char* query,char* pt_tableno,int tableno,char* name);
//用户管理模块
void user_manager(user_info_t *userinfo,MYSQL *mysql,int optype,int usertype,int logintype);//用户管理模块  学生用户无管理权限
void user_login(user_info_t *userinfo,MYSQL *mysql);//用户登录模块   根据用户名进行用户类型的查询
void user_regist(user_info_t *userinfo,MYSQL *mysql,int usertype,int logintype);//用户注册模块　不同登录用户进行不同类型用户的注册操作
void userinfo_manager(user_info_t *userinfo,MYSQL *mysql,int usertype);//用户信息管理模块　　学生无此权限
//管理员模块
void admin_manager(user_info_t *usernifo,MYSQL *mysql);//管理员模块
void admininfo_manager(user_info_t *userinfo,admin_info_t *admininfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES* res,MYSQL_ROW row,char* query);
//学院信息管理模块
bool check_college_empty(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
void college_manager(college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
//学院专业管理模块
bool check_profs_empty(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
void  profs_manager(profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
//学院专业科目管理模块
bool check_subinfo_empty(sub_info_t *subinfo,profs_info_t *profsinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
void  sub_manager(sub_info_t *subinfo,profs_info_t *profsinfo,college_info_t *collegeinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
//学生管理模块
void stu_manager(user_info_t *userinfo,MYSQL *mysql);//学生用户管理
void stuinfo_manager(user_info_t *userinfo,stu_info_t *stuinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query,int optype,int logintype);//学生信息管理
//学期设置模块
bool check_yearinfo_empty(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);
void year_manager(year_info_t *yearinfo,MYSQL *mysql,MYSQL_RES *res,MYSQL_ROW row,char *query);





