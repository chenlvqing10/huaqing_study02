/*================================================================
 *   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：selection_sort.c
 *   创 建 者：Chenlvqing
 *   创建日期：2020年03月02日
 *   描    述：
 *
 ================================================================*/

#include<stdio.h>
void swap(int* a,int* b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}
int main()
{
	int a[10];
	int min,index;
	printf("Please input a array data:\n");
	for(int i=0;i<10;i++)
	{
		scanf("%d",&a[i]);
	}

	for(int i=0;i<9;i++)
	{
		min=a[i];
		for(int j=i+1;j<10;j++)
		{
			if(a[j]<min)
			{
				min=a[j];
				index=j;//get the min value's array index
			}
		}
		if(index!=i)
		{
			swap(&a[i],&a[index]);//swap a[i] and the min value
		}
		printf("\n");
		/*print the sort procedure*/
		for(int k=0;k<10;k++)
		{
			printf("%d ",a[k]);
		}
		printf("\n");
	}
	return 0;
}
