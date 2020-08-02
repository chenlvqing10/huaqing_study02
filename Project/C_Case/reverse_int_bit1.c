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
     
	a=((a&0xAAAAAAAA)>>1) | ((a&0x55555555)<<1);//将奇偶位交换(1Bit)
	printf("the Hex number is:0x%08X\n",a); 
	a=((a&0xCCCCCCCC)>>2) | ((a&0x33333333)<<2);//将奇偶位交换(2Bit)
	printf("the Hex number is:0x%08X\n",a);
	a=((a&0xF0F0F0F0)>>4) | ((a&0x0F0F0F0F)<<4);//将奇偶位交换(4Bit)
	printf("the Hex number is:0x%08X\n",a);
	a=((a&0xFF00FF00)>>8)  | ((a&0x00FF00FF)<<8);//将奇偶位交换(8Bit)
	printf("the Hex number is:0x%08X\n",a);  
	a=((a&0xFFFF0000)>>16)  | ((a&0x0000FFFF)<<16);//将奇偶位交换(16Bit)
    printf("the Hex number is:0x%08X\n",a);  

	printf("the Hex number is after:0x%08X",a);

	return 0;
}

