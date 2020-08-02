#ifndef __SEQSTACK_CHAR__
#define __SEQSTACK_CHAR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//定义顺序栈的结构
typedef char     ElemType;//实际的数据了类型

typedef struct SeqStack
{
	ElemType  *elem;//栈中的元素　一维数组  //size=4
	int       top;//栈顶元素的下标          //size=4
	int		  StackSize;//栈中元素数组的长度 //size=4
}SeqStack,*Ptr;

typedef Ptr SeqStackPtr;

//栈的基本操作
typedef enum Status
{
    success,//成功=0
    fail,//失败=1
    fatal,//致命的错误＝2
    range_error//越界=3
}Status;

Status Stack_Create(SeqStackPtr s);
Status Stack_Push(SeqStackPtr s,ElemType elem);//进栈
Status Stack_Pop(SeqStackPtr s);//出栈
void   DisplayStack(SeqStackPtr s);//打印栈中的数据
char   Stack_Pop_char(SeqStackPtr s);//转换成字符出栈 并返回
void   RadixChange(SeqStackPtr s,char *data_before,char *data_after,int oldSystem,int newSystem);//进制的转换
void   BracketsMatch(char *bracket,SeqStackPtr s);//bracker:括号的序列　　s:顺序栈





#endif
