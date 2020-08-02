/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：struct_01.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月20日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>
#include<string.h>
//结构体
typedef struct stu_info{
	int stuid;//学号
	char *name;//学生的姓名
	int age;//年龄
	char group;//分组
	float score;//成绩
}STU_INFO;//tyoedef to STU_INFO for the struct 

//结构体的初始化与访问
void print_stu_info(void)
{
	STU_INFO stu1;//先定义结构体类型的变量
	stu1.stuid=1001;
	stu1.name="aaaa",
		stu1.age=18;
	stu1.group='A';
	stu1.score=89;

	//定义结构体类型的变量 初始化  Linux内核
	STU_INFO stu2 = {
		.stuid=1002,
		.name = "bbbb",
		.age=20,
		.group='B',
		.score=90
	};

	STU_INFO stu3={1003,"cccc",25,'C',95};//定义结构体变量的同事进行初始化

	//打印结构体信息
	printf("stu1_info>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n",stu1.stuid,stu1.name,stu1.age,stu1.group,stu1.score);
	printf("stu2_info>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n",stu2.stuid,stu2.name,stu2.age,stu2.group,stu2.score);
	printf("stu3_info>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n",stu3.stuid,stu3.name,stu3.age,stu3.group,stu3.score);
}

//结构体数组的声明，初始化，访问
void print_stu_info_array(void)
{
	//在声明的同时进行初始化
	STU_INFO stu_info_arr[5]={

		[0] = {	
			.stuid=2001,
			.name = "eeee one",
			.age=19,
			.group='A',
			.score=80
		},

		[1] = {	
			.stuid=2002,
			.name = "eeee two",
			.age=19,
			.group='B',
			.score=70
		},

		[2] = {	
			.stuid=2003,
			.name = "eeee three",
			.age=22,
			.group='C',
			.score=88
		},

		[3] = {	
			.stuid=2004,
			.name = "eeee four",
			.age=23,
			.group='A',
			.score=98
		},

		[4] = {	
			.stuid=2005,
			.name = "eeee five",
			.age=25,
			.group='B',
			.score=95
		}

	};

	for(int i=0;i<5;i++)
	{
		printf("stu1_info_array>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
				,stu_info_arr[i].stuid,stu_info_arr[i].name,stu_info_arr[i].age,stu_info_arr[i].group,stu_info_arr[i].score);
	}
}

//结构体指针的声明，初始化，访问
void print_stu_info_ptr(void)
{
	STU_INFO *stu_info_ptr;
	STU_INFO stu_info_1={3001,"abcdefdf",20,'G',86};
	stu_info_ptr=&stu_info_1;

	printf("stu1_info_ptr>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
			,stu_info_ptr->stuid,stu_info_ptr->name,stu_info_ptr->age,stu_info_ptr->group,stu_info_ptr->score);
}


//结构体指针数组
void print_stu_info_ptr_array(void)
{
	STU_INFO *stu_info_ptr_arr[5];
	//定义一个结构体变量并初始化
	STU_INFO stu_info_arr1={4001,"aaaaaaa",20,'A',56};
	//将结构体指针数组的第0个指针指向该结构体变量的地址
	stu_info_ptr_arr[0]=&stu_info_arr1;

	printf("stu1_info_ptr_arr_[0]>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
			,stu_info_ptr_arr[0]->stuid,stu_info_ptr_arr[0]->name,stu_info_ptr_arr[0]->age,stu_info_ptr_arr[0]->group,stu_info_ptr_arr[0]->score);

	//定义结构体数组
	STU_INFO stu_info_arr[4]=
	{
		[0] = {	
			.stuid=5001,
			.name = "eeee one",
			.age=19,
			.group='A',
			.score=80
		},

		[1] = {	
			.stuid=6002,
			.name = "eeee two",
			.age=19,
			.group='B',
			.score=70
		},

		[2] = {	
			.stuid=7003,
			.name = "eeee three",
			.age=22,
			.group='C',
			.score=88
		},

		[3] = {	
			.stuid=8004,
			.name = "eeee four",
			.age=23,
			.group='A',
			.score=98
		}

	};
	for(int i=0;i<=3;i++)
	{
		stu_info_ptr_arr[i+1]=&stu_info_arr[i];

		printf("stu1_info_ptr_arr_[%d]>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
				,i+1,stu_info_ptr_arr[i+1]->stuid,stu_info_ptr_arr[i+1]->name,stu_info_ptr_arr[i+1]->age,stu_info_ptr_arr[i+1]->group,stu_info_ptr_arr[i+1]->score);
	}
}

//结构体数组指针
void print_stu_info_array_ptr(void)
{
	STU_INFO stu_info_array[5]={

		[0] = {	
			.stuid=2111,
			.name = "eeee one",
			.age=19,
			.group='A',
			.score=80
		},

		[1] = {	
			.stuid=2112,
			.name = "eeee two",
			.age=19,
			.group='B',
			.score=70
		},

		[2] = {	
			.stuid=2113,
			.name = "eeee three",
			.age=22,
			.group='C',
			.score=88
		},

		[3] = {	
			.stuid=2114,
			.name = "eeee four",
			.age=23,
			.group='A',
			.score=98
		},

		[4] = {	
			.stuid=2115,
			.name = "eeee five",
			.age=25,
			.group='B',
			.score=95
		}
	};//定义结构体数组

	STU_INFO *stu_info_array_ptr;
	stu_info_array_ptr=stu_info_array;//定义结构体数组指针 (指向一维数组)

	for(int i=0;i<=4;i++)
	{
		printf("stu1_info_arr_ptr_[%d]>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
				,i,stu_info_array_ptr->stuid,stu_info_array_ptr->name,stu_info_array_ptr->age,stu_info_array_ptr->group,stu_info_array_ptr->score);

		stu_info_array_ptr++;
	}
}

//二维结构体数组和二维结构体数组指针
void print_stu_info_array_ptr_two_dimen(void)
{
	//定义一个二维结构体数组并初始化
	STU_INFO stu_info_arr_two[2][3]={
		[0]={	
			[0] = {	
				.stuid=5550,
				.name = "eeee one",
				.age=19,
				.group='A',
				.score=80
			},

			[1] = {	
				.stuid=5551,
				.name = "eeee two",
				.age=19,
				.group='B',
				.score=70
			},

			[2] = {	
				.stuid=5553,
				.name = "eeee three",
				.age=22,
				.group='C',
				.score=88
			}
		},

		[1]={
			[0] = {	
				.stuid=5554,
				.name = "eeee four",
				.age=23,
				.group='A',
				.score=98
			},


			[1] = {	
				.stuid=5555,
				.name = "eeee five",
				.age=25,
				.group='B',
				.score=95
			},

			[2] = {	
				.stuid=5556,
				.name = "eeee five",
				.age=25,
				.group='B',
				.score=95
			}
		}

	};
	
	//打印二维结构体数组的成员
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("stu1_info_array_two[%d][%d]>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
			,i,j,stu_info_arr_two[i][j].stuid,stu_info_arr_two[i][j].name,stu_info_arr_two[i][j].age,stu_info_arr_two[i][j].group,stu_info_arr_two[i][j].score);
		}
	}

	//定义二维结构体数组指针
	STU_INFO (*stu_info_array_ptr_two)[3];//二维数组的列数
	stu_info_array_ptr_two=(STU_INFO(*)[3])stu_info_arr_two;//二维结构体数组指针指向该数组首地址

	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("stu1_info_array_ptr_two[%d][%d]>>>>  stuid:%d  name:%s  age:%d  group:%c  score:%.2f\n"
			,i,j,(stu_info_array_ptr_two[i]+j)->stuid,(stu_info_array_ptr_two[i]+j)->name,(stu_info_array_ptr_two[i]+j)->age,
			(stu_info_array_ptr_two[i]+j)->group,(stu_info_array_ptr_two[i]+j)->score);
		}
	}
}


int main(int argc,const char *argv[])
{
	print_stu_info();//结构体
	print_stu_info_array();//结构体数组
	print_stu_info_ptr();//结构图指针
	print_stu_info_ptr_array();//结构体指针数组
	print_stu_info_array_ptr();//结构体数组指针（指向一维数组）
	print_stu_info_array_ptr_two_dimen();//二维结构体数组  结构体数组指针(指向二维数组)
	return 0;
}
