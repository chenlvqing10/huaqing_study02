#include "linkstack.h"


//创建一个空的链栈
LinkStackPtr LinkStack_Create(LinkStackPtr LinkStack)//创建链栈  
{
	//为该节点分配内存空间
	LinkStack=(LinkStackPtr)malloc(sizeof(SNode));
	top=LinkStack;//将栈顶的节点指针指向该节点
	if(top==NULL)
	{
		printf("内存分配失败\n");
	}
	else
	{
		top->next=NULL;//创建头结点
		printf("创建空的链栈成功\n");
	}

	return top;
}

//入栈
Status LinkStack_Push(LinkStackPtr LinkStack,ElemType elem)//入栈
{
	Status status;
	top=LinkStack;

	LinkStackPtr newnode=(LinkStackPtr)malloc(sizeof(SNode));//新建一个节点
	if(newnode==NULL)
	{
		printf("内存分配失败\n");
		status=fatal;
	}
	else
	{
		newnode->elem=elem;//赋值数据域
		newnode->next=top->next;//先入栈的元素放在栈顶  头节点的后面　前插
		top->next=newnode;//将头结点的next指向新的节点　头指针不用移动
		status=success;
	}
	return status;


}

Status LinkStack_Pop(LinkStackPtr LinkStack)//出栈
{
	Status status;
	ElemType elem_pop;
	LinkStackPtr node;
	top=LinkStack;//头指针

	if(top==NULL)//栈为空
	{
		printf("空的链栈\n");
		status=fail;
	}
	else//栈非空
	{
		node=top->next;//从头结点之后的一个节点开始出栈
		elem_pop=node->elem;//将出栈节点的数据域赋值给elem_pop
		printf("出栈的元素:%d\n",elem_pop);
		top->next=node->next;
		free(node);//释放该节点的内存空间
		status=success;
	}

	return	status;
}


//显示链栈的数据
void DisplsyLinkStack(LinkStackPtr LinkStack)
{
	top=LinkStack;
	while(top->next!=NULL)
	{
		printf("->%d",top->elem);
		top=top->next;
	}
	printf("->%d->\n",top->elem);

}
int main(int argc,char* argv[])
{
	LinkStackPtr linkstack1=NULL;
	linkstack1=LinkStack_Create(linkstack1);//创建一个空的链栈

	//入栈
	LinkStack_Push(linkstack1,11);
	LinkStack_Push(linkstack1,22);
	LinkStack_Push(linkstack1,33);
	LinkStack_Push(linkstack1,44);
	LinkStack_Push(linkstack1,55);

	DisplsyLinkStack(linkstack1);

	//出栈
	LinkStack_Pop(linkstack1);
	LinkStack_Pop(linkstack1);
	LinkStack_Pop(linkstack1);

	DisplsyLinkStack(linkstack1);



	return 0;
}
