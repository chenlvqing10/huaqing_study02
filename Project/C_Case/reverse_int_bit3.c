/*================================================================J
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*
*   文件名称：test1.c
*   创 建 者：Chenlvqing
*   创建日期：2020年02月26日
*   描    述：
*
================================================================*/

#define getbit(x,y)			((x)>>(y)&1)//get the y‘s bit is 0 or 1 from x
#define setbit_1(x,y)		(x|=(1<<y))//set y's bit to 1 for x
#define setbit_0(x,y)		(x&=~(1<<y))//set y's bit to 0 fro x
#define setbit_reverse(x,y) (x^(1<<y))//set the y's bit to  the reverse bit for x 

#include<stdio.h>
int main()
{
	int a;
	printf("Please input a hexadecimal num:");
	scanf("%x",&a);
    printf("the Hex number is before:0x%08X\n",a);

	for(int i=0;i<=sizeof(a)*8/2-1;i++)
	{
		if(getbit(a,sizeof(a)*8-1-i)!=getbit(a,i))
		{
			if(getbit(a,i)==1)
			{
				setbit_0(a,i);
				printf("%d a=0x%08X\n",i,a);
				setbit_1(a,sizeof(a)*8-1-i);
				printf("%d a=0x%08X\n", i, a);
			}
			else
			{
				setbit_0(a,sizeof(a)*8-1-i);
				printf("%d a=0x%08X\n", i, a);
				setbit_1(a,i);
				printf("%d a=0x%08X\n", i, a);
			}
		}
	}

	printf("the Hex number is after:0x%08X",a);

	return 0;
}

