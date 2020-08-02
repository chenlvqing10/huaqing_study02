#include<stdio.h>
int add(int num1,int num2)
{
	int sum;
	sum =num1 + num2;
	return sum;
}

int main()
{
    int num1,num2;
	printf("Please input the num1 and num2:\n");
	if(scanf("%d %d",&num1,&num2)=EOF)
	{
		printf("error");
	}
	else
	{
		int sum=add(num1,num2);
		printf("the sum of num1 and num2:%d\n",sum);
	}
	
    return 0;
}
