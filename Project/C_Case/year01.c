/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：year01.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月01日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>
#include<string.h>
int main()
{
	//define a string array ptr
	const char *year_t[10]={"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
	const char *year_d[12]={"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};
	char *year_td[60];
	int i=0,j=0;
	for(int k=0;k<60;k++)
	{
		//printf("天干地支=%s%s\n",year_t[i],year_d[j]);
		year_td[k]=strcat((char*)year_t[i],year_d[j]);
		i++;
		j++;
		if(i==10)
		{
			i=0;
		}
		if(j==12)
		{
			j=0;
		}
		
		printf("天干地支=%s\n",year_td[k]);
	}

	return 0;
}
