/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：get_clock.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年02月28日
 *   描    述：实现时钟
 *
 ================================================================*/
#include<stdio.h>
#include<time.h>
#include<unistd.h>

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
	int num_day;
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

//check the current date data
int  check_date(int year,int mon,int day,int hour,int min,int sec)
{
	if((year>0)&&(mon>=1)&&(mon<=12)&&(day>=1)&&(day<=setdaynum(year,mon))
			&&(hour>=0)&&(hour<=23)&&(min>=0)&&(min<=59)&&(sec>=0)&&(sec<=59))
		return 1;
	else
		return 0;
}
int main()
{
	//define th var
	int year,mon,day,hour,min,sec;
	//get the system time by time.h
	/*time_t time( time_t * ) time_t就是long，函数返回从1970年1月1日（MFC是1899年12月31日）0时0分0秒，到现在的的秒数*/
	/*	time_t s_time;
		struct tm *p;
		time(&s_time);
		p=gmtime(&s_time);

		year=p->tm_year+1900;
		mon=1+p->tm_mon;
		day=p->tm_mday;
		hour=8+p->tm_hour;
		min=p->tm_min;
		sec=p->tm_sec;
		*/
	printf("Please input the date:\n");
	printf("year  month  day  hour  min  sec\n");
	scanf("%d %d %d %d %d %d",&year,&mon,&day,&hour,&min,&sec);
	printf("year=%d mon=%d day=%d hour=%d min=%d sec=%d\n",year,mon,day,hour,min,sec);
	if(check_date(year,mon,day,hour,min,sec)==0)
	{
		printf("the date is not corect\n");
		return -1;
	}
	//make a clock
	while(1)
	{
		sleep(1);
		sec++;
		if(sec==60)
		{
			min++;
			sec=0;//second reset to 0
			if(min==60)
			{
				hour++;
				min=0;//min reset to 0
				if(hour==24)
				{
					day++;
					hour=0;//hour reset to 0
					if(day==setdaynum(year,mon)+1)
					{
						mon++;
						day=1;//day reset to 1
						if(mon==13)
						{
							year++;
							mon=1;//mon reset to 1
						}
					}
				}
			}
		}

		//printf("%4d-%02d-%02d %02d:%02d:%02d\n",year,mon,day,hour,min,sec);
		printf("%4d-%02d-%02d %02d:%02d:%02d\r",year,mon,day,hour,min,sec);
		fflush(stdout);
	}
	return 0;
}

