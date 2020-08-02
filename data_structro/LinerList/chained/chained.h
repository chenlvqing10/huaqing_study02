#ifndef __CHAINED__
#define __CHAINED__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int ElemType;//假设处理的数据类型位整形　　根据处理的数据不同ElemType的类型是不同的
//创建节点
typedef struct Node
{
	ElemType elem;//数据域
	struct   Node *next;//指针域
}Node,*Ptr;
typedef  Ptr  SqlistPtr;//定义别名

typedef enum Status
{
    success,//成功=0
    fail,//失败=1
    fatal,//致命的错误＝2
    range_error//越界=3
}Status;

//typedef Ptr *SqlistPtr;//struct Node** SqlistPtr  Node的双重指针

//定义头指针和尾指针
SqlistPtr head=NULL;
SqlistPtr end=NULL;

//单链表的基本操作
SqlistPtr Initlist(SqlistPtr L);//创建一个空的头节点
SqlistPtr HeadCreateList(SqlistPtr L,ElemType data[],int len);//头插法创建一个单链表
SqlistPtr TailCreateList(SqlistPtr L,ElemType data[],int len);//尾插法创建一个单链表
int		  ListLength(SqlistPtr L);//得到单链表的长度
void      DisplayList(SqlistPtr L);//显示单链表的内容 不现实头结点的内容
void	  DisplayList_Head(SqlistPtr L);//递归显示单链表的内容　显示头结点的内容
Status    List_Retrieve(SqlistPtr L,int pos,ElemType *elem);//按位置查找单链表中的数据
Status	  List_Locate(SqlistPtr L,ElemType elem,int* pos);//按数值在单链表中查找是否存在该数
Status    List_InsertByPre(SqlistPtr L,int pos,ElemType elem);//在单链表的pos位置插入数据元素elem  前插法
Status    List_InsertByBack(SqlistPtr L,int pos,ElemType elem);//在单链表的pos位置插入数据元素elem  后插法
SqlistPtr List_Remove(SqlistPtr L,int pos);//移动节点到指定的位置
Status    List_Delete(SqlistPtr L,int pos);//删除单链表中某个位置的节点
SqlistPtr List_Reverse(SqlistPtr L);//将单链表倒置
SqlistPtr List_Reverse_recursion(SqlistPtr L);//递归实现单链表的倒置
SqlistPtr List_Destroy(SqlistPtr L);//销毁单链表
void	  List_QuickSort(SqlistPtr L);//快速排序单链表
SqlistPtr List_MergeList(SqlistPtr La,SqlistPtr Lb);//非递归方法实现两个有序链表的合并
SqlistPtr List_MergeList_recursion(SqlistPtr La,SqlistPtr Lb);//递归方法实现两个有序链表的合并


#endif
