#ifndef __DOUBLE_CHAINED__
#define __DOUBLE_CHAINED__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;//假设处理的数据类型位整形　　根据处理的数据不同ElemType的类型是不同的

//定义双向链表
typedef struct Node
{
	ElemType     elem;//数据域
	struct Node* prior;//指向直接前趋
	struct Node* next;//指向直接后继
}Node,*Ptr;

typedef  Ptr  DoubSqlistPtr;//定义别名 双向链表节点指针

typedef enum Status
{
    success,//成功=0
    fail,//失败=1
    fatal,//致命的错误＝2
    range_error//越界=3
}Status;


//定义头指针和尾指针
DoubSqlistPtr head=NULL;
DoubSqlistPtr end=NULL;

//双向链表的操作
DoubSqlistPtr InitHeadNode(DoubSqlistPtr L,int type,ElemType elem);//创建一个空的头节点或者首元节点 type=1:创建带头节点的双向链表 type=2:创建不带头结点的双向链表
DoubSqlistPtr CreatDoubList(DoubSqlistPtr L,int type);
void          display(DoubSqlistPtr L);//打印双向循环链表
int			  DoubListLength(DoubSqlistPtr L);//得到双向链表的长度
Status        DoubList_Retrive(DoubSqlistPtr L,int pos,ElemType *elem);//按位置查找数值
Status        DoubList_Locate(DoubSqlistPtr L,ElemType elem,int *pos);//按照数值查找位置
DoubSqlistPtr DoubList_Insert(DoubSqlistPtr L,int pos,ElemType elem);//插入的位置　　插入的数据元素数值
DoubSqlistPtr DoubList_Delete(DoubSqlistPtr L,int pos);//删除双向链表中某个位置的节点
DoubSqlistPtr DoubList_Destroy(DoubSqlistPtr L);//销毁双向链表



#endif
