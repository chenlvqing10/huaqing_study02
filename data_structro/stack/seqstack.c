#include "seqstack.h"

Status Stack_Create(SeqStackPtr s)//创建一个空栈
{
	printf("创建一个空栈\n");

	Status status;
	s->elem=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));//为栈中的数据元素分配存储空间　指针类型

	if(s->elem==NULL)
		status=fatal;//分配空间失败
	else
	{
		printf("初始化栈\n");
		s->top=-1;//初始化栈顶
		s->StackSize=STACK_INIT_SIZE;//初始化栈的大小
		status=success;
	}

	return status;
}

//进栈
Status Stack_Push(SeqStackPtr s,ElemType elem)
{
	printf("call Push\n");
	Status status;
	if(s->top>=(s->StackSize-1))//如果栈顶大小已经大于栈的空间大小top从0开始  99
	{
		printf("空间不足\n");
		s->elem=(ElemType*)realloc(s->elem,(s->StackSize+STACKINCREMENT)*sizeof(ElemType));//为栈中的数据元素分配增加的存储空间　指针类型
		if(s->elem==NULL)
			status=fatal;//分配空间失败
		else
		{
			s->StackSize=s->StackSize+STACKINCREMENT;//增加栈的大小
			s->top++;//栈顶大小+1
			s->elem[s->top] = elem;//为数组赋值
			status = success;
		}
	}
	else//内存空间足够
	{
		printf("内存空间足够\n");
		s->top++;//栈顶大小+1
		s->elem[s->top]=elem;//为数组赋值
		status=success;
	}

	return status;
}

//出栈
Status Stack_Pop(SeqStackPtr s)
{
	Status status;
	ElemType elem_pop;
	if(s->top==-1)
	{
		printf("顺序栈是空的\n");
		status=fail;
	}
	else//栈非空
	{
		elem_pop=s->elem[s->top];
		s->top--;
		printf("出栈的数据是%d\n",elem_pop);
		status=success;
	}
	return status;
}

//转换成字符进行出栈　并返回
char Stack_Pop_char(SeqStackPtr s)
{
	char elem_pop;

	if(s->top==-1)
	{
		printf("顺序栈是空的\n");
	}
	else//栈非空
	{
		if(s->elem[s->top]>=10)//进行字符转换
			elem_pop=s->elem[s->top]-10 + 'A';
		else
			elem_pop=s->elem[s->top] + '0';
		s->top--;
		printf("出栈的数据是%c\n",elem_pop);
	}
	return elem_pop;
}

//显示栈中的数据
void DisplayStack(SeqStackPtr s)
{
	int top=s->top;//原来栈中的栈顶不能减少　定义一个中间变量来接收栈顶的数值
	if(top==-1)
	{
		printf("顺序栈是空的\n");
	}
	else
	{
		while(top>=0)
		{
			printf("->%d->",s->elem[top]);
			//printf("->%c->",s->elem[top]);
			top--;
		}
		printf("\n");
	}
}

void  RadixChange(SeqStackPtr s,char *data_before,char *data_after,int oldSystem,int newSystem)//进制的转换
{
	int len_data_before=strlen(data_before);//字符串的长度
	int k=len_data_before-1;//用于处理位数需要-1
	int temp;//临时变量用户保存转换后的十进制数值
	int  data_system_10=0;

	for(int i=k;i>=0;i--)
	{
		//printf("data_before[i]=%d\n",data_before[i]);
		if((data_before[i]>='0')&&(data_before[i]<='9'))//ascii码的数值在0~9之间
		{
			temp=data_before[i]-48;
		}
		else if((data_before[i]>='A')&&(data_before[i]<='Z'))//ascii码的数值在A~Z之间
		{
			printf("111111\n");
			temp=data_before[i]-65 + 10;
		}

		//数字*进制^(位数-1) 转换位十进制数
		printf("temp=%d temp*pow(oldSystem,i)=%f\n",temp,temp*pow(oldSystem,k-i));
		
		data_system_10=data_system_10+temp*pow(oldSystem,k-i);
		
		printf("data_system_10=%d\n",data_system_10);
	}

	printf("data_system_10=%d\n",data_system_10);

	//十进制转换位任意进制
	while(data_system_10/newSystem)//对十进制取整　当取整为0时表示十进制数处理完毕
	{

		Stack_Push(s,data_system_10%newSystem);//把余数放到空栈中
		data_system_10=data_system_10/newSystem;//取整之后的数
	}

	Stack_Push(s,data_system_10%newSystem);//把最后一个余数放到空栈中
	DisplayStack(s);

	//顺序取出栈中的数据放到字符串中
	k=s->top;//得到数组的下标

	for(int i=k;i>=0;i--)
	{

		data_after[k-i]=Stack_Pop_char(s);
		printf("data=%c\n",data_after[k-i]);
	}
	for(int i=15;i>=0;i--)
		printf("data_after[%d]=%c\n",i,data_after[i]);
	printf("data_after=%s\n",data_after);
}
int main(int argc,char* argv[])
{
	SeqStack stack1;
	Status status=Stack_Create(&stack1);

	if(status==success)
	{
		printf("创建空栈成功\n");
	}
	else
		printf("创建空栈失败\n");

	//进栈
	Stack_Push(&stack1,11);
	Stack_Push(&stack1,22);
	Stack_Push(&stack1,33);
	Stack_Push(&stack1,44);
	Stack_Push(&stack1,55);
	Stack_Push(&stack1,66);
	Stack_Push(&stack1,77);

	//显示栈中的内容
	DisplayStack(&stack1);

	//出栈
	Stack_Pop(&stack1);
	DisplayStack(&stack1);


	//------进制的转换
	SeqStack stack2;
	status=Stack_Create(&stack2);
	if(status==success)
	{
		printf("创建空栈stack2成功\n");
	}
	else
		printf("创建空栈stack2失败\n");

	char data_before[100]="3FF5FF";//输入的数据
	char data_after[100]={0};//需要初始化
	int  oldSystem=16;//二进制
	int  newSystem=2;//十六进制

	RadixChange(&stack2,data_before,data_after,oldSystem,newSystem);

	return 0;
}
