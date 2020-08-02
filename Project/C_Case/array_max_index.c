/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *   
 *   文件名称：array_max_index.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月25日
 *   描    述：
 *
 ================================================================*/
#include<stdio.h>

void findMaxIndex(int a[],int len_arr,int *index_max)
{
	len_arr=len_arr-1;
	*index_max=len_arr;
	while(len_arr--)
	{
		if(a[len_arr]>a[*index_max])
			*index_max = len_arr;
	}

}


int main(int argc,const char *argv[])
{
	int a[]={1,2,3,98,76,75};
	int len_arr=sizeof(a)/sizeof(a[0]);
	int index_max;
	printf("len_arr=%d\n",len_arr);
	findMaxIndex(a,len_arr,&index_max);
	printf("the max index is %d\n",index_max);
	printf("the max value is %d",a[index_max]);

	return 0;
}
