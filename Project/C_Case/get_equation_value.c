/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：get_equation_value.c
*   创 建 者：Chenlvqing
*   创建日期：2020年02月27日
*   描    述：求一元二次方程的根   ax^2+bx+c = 0
*
================================================================*/
#include<stdio.h>
#include<math.h>

int main()
{
	float a,b,c;//define a,b,c
	float v_formula;//define the quadratic formula
	float v_equation_1,v_equation_2;//define the equation value

	//input a,b,c from keyb
	printf("Please input a,b,c:");
	scanf("%f %f %f",&a,&b,&c);
    printf("a=%f,b=%f,c=%f\n",a,b,c);

	v_formula=b*b-4*a*c;
	printf("the fornula value is:%f\n",v_formula);

	//jude the formula
    if(v_formula>0)
	{
		v_equation_1=((-b)+sqrt(v_formula))/(2*a);
		v_equation_2=((-b)-sqrt(v_formula))/(2*a);
		printf("the value of equation is:v_equation_1=%f v_equation_2=%f\n",v_equation_1,v_equation_2); 
	}
	else if(v_formula==0)
	{
		v_equation_1=(-b)/(2*a);
		printf("the value of equation is:v_equation_1=v_equation_2=%f\n",v_equation_1);
	}
	else if(v_formula<0)
	{
		printf("the equation has no value\n");
		return -1;
	}
    
	return 0;
}
