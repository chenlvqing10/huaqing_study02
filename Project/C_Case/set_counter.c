/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：set_counter.c
*   创 建 者：Chenlvqing
*   创建日期：2020年02月27日
*   描    述：
*
================================================================*/
#include<stdio.h>
#include<math.h>

float add(float x,float y)
{
	return x+y;
}

float sub(float x,float y)
{
	return x-y;
}

float mul(float x,float y)
{
	return x*y;
}

float div(float x,float y)
{
	return x/y;
}
int main()
{
	float x,y;
	char op;
	float v_counter;
	printf("Please input x,op,y:\n");
	scanf("%f %c %f",&x,&op,&y);
	printf("x=%f op=%c y=%f\n",x,op,y);
	
	switch(op)
	{
		case '+':
			printf("the op is +\n");
			v_counter=add(x,y);
			break;
		case '-':
			printf("the op is -\n");
			v_counter=sub(x,y);
			break;
		case '*':
			printf("the op is *\n");
			v_counter=mul(x,y);
			break;
		case '/':
			printf("the op is /\n ");
			if(y==0)
			{
				printf("the divisor can not 0\n");
				return -1;
			}
			v_counter=div(x,y);
			break;
		default:
			printf("unkown character\n");
			return -1;
	}

	printf("the counter value is:%.3f",v_counter);

	return 0;
}
