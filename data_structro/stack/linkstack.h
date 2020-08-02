#ifndef __LINKSTACK__
#define __LINKSTACK__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//定义链式存储结构的栈　　链栈
typedef int     ElemType;//实际的数据了类型

typedef struct SNode
{
	ElemType      elem;//栈中的元素
	struct SNode* next;//指针域,指向下一个节点
}SNode,*Ptr;

typedef Ptr LinkStackPtr;//定义链栈的结构体指针　节点指针

LinkStackPtr top;//定义一个节点指针

typedef enum Status
{
    success,//成功=0
    fail,//失败=1
    fatal,//致命的错误＝2
    range_error//越界=3
}Status;

//链栈的基本操作
LinkStackPtr LinkStack_Create(LinkStackPtr LinkStack);//构造一个空栈　将栈顶指针top所指头结点的指针域置为NULL，因为此时栈中还没有数据元素
Status       LinkStack_Push(LinkStackPtr LinkStack,ElemType elem);//入栈
Status       LinkStack_Pop(LinkStackPtr LinkStackPtr);//入栈
void DisplsyLinkStack(LinkStackPtr LinkStack);//显示链栈的数据 


#endif
