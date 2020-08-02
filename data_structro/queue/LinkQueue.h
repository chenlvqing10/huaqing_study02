#ifndef __LINKQUEUE__
#define __LINKQUEUE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链式队列的类型
 typedef int     ElemType;//实际的数据类型

//定义链式队列的结构
typedef struct QNode
{
	ElemType elem;//数据域
	struct QNode* next;//指针域
}QNode,*Ptr;

typedef  Ptr LinkQueuePtr;//声明结构体指针

//操作的状态
 typedef enum Status
 {
     success,//成功=0
     fail,//失败=1
     fatal,//致命的错误＝2
     range_errori,//越界=3
	 empty,//空
	 noempty,//非空
	 full,//队列溢出
	 nofull//队列非满
 }Status;

LinkQueuePtr top,rear;

//顺序队列的基本操作
LinkQueuePtr LinkQueue_Creat(LinkQueuePtr Q);//创建一个空的链式队列
void DisplayLinkQueue(LinkQueuePtr Q);//显示链式队列中的内容
Status EnterLinkQueue(LinkQueuePtr Q,ElemType elem);//入队
Status QuitLinkQueue(LinkQueuePtr Q);//出队



#endif
