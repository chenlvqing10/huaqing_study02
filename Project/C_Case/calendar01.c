/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：calendar.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年02月28日
 *   描    述：根据menu选择1还是2，1：输入年份，打印年份所有月的日历，
 *             2:输入年月，打印该年该月日历
 *
 ================================================================*/


#include<stdio.h>

/*基姆拉尔森计算公式  按年月日计算星期*/
int CaculateWeekDay(int y,int m, int d)
{
	if(m==1||m==2)
	{
		m+=12;
		y--;
	}
	int iWeek=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;

	return iWeek;
}


//check the leap year
int is_leapyear(int year)
{
	if(((year%4==0)&&(year%100!=0))||((year%400==0)))
		return 1;
	else
		return 0;
}

//judge the mon is big or small
int setdaynum(int year,int mon)
{
	int num_day;//get day by year and  month
	if(is_leapyear(year)==1)
	{
		if(mon==2)
		{
			num_day=29;
		}
	}
	else
	{
		if(mon==2)
		{
			num_day=28;
		}
	}

	if((mon==1)||(mon==3)||(mon==5)||(mon==7)||(mon==8)||(mon==10)||(mon==12))//1 3 5 7 8 10 12
	{
		num_day=31;
	}
	else if(mon!=2)//other
	{
		num_day=30;
	}

	return num_day;
}
//print calendar
void print_calendar(int year,int mon_week,int month)
{
	printf("the date is:%d-%d\n",year,month);
	printf("SUN\tMON\tTHU\tWED\tTHU\tFRI\tSAR\n");

	//print" " by week
	if(mon_week<6)
	{
		for(int k=0;k<=mon_week;k++)
		{
			printf(" \t");
		}

	}

	//print day
	for(int j=1;j<=setdaynum(year,month);j++)
	{
		printf("%d\t",j);
		if((j+mon_week+1)%7==0)
		{
			printf("\n");
		}
	}

	printf("\n");
}

//check the current date data
int  check_date(int year,int mon)
{
	if((year>0)&&(mon>=1)&&(mon<=12))
		return 1;
	else
		return 0;
}


int main()
{
	//define the date var
	int year,month;
	int mon_week[12];
	int menu;

	printf("Please choose the menu:\n");
	printf("1.print a year's calendar\n");
	printf("2.print a month's calendar of one year:\n");
	scanf("%d",&menu);

	//print diffirent calendar by menu
	if(menu==1)
	{
		printf("Please input the year you want to know:");
		scanf("%d",&year);

		if(check_date(year,1)==0)
		{
			printf("the year is not corect\n");
			return -1;
		}

		for(int i=0;i<12;i++)
		{
			mon_week[i]=CaculateWeekDay(year,i+1,1);
			print_calendar(year,mon_week[i],i+1);
		}
	}
	else if(menu==2)
	{
		printf("Please input the year and month you want to know:XXXX XX:");
		scanf("%d %d",&year,&month);

		if(check_date(year,month)==0)
		{
			printf("the year or month is not corect\n");
			return -1;
		}

		print_calendar(year,CaculateWeekDay(year,month,1),month);
	}

	return 0;
}
