#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE  100//线性表存储空间的初始分配量
#define LIST_INCREAMENT 50//线性表存储空间分配增量

typedef int ElemType;//假设处理的数据类型位整形　　根据处理的数据不同ElemType的类型是不同的

/*定义顺序线性表的结构体　　　连续的地址空间*/
typedef struct SqList
{
	ElemType *elem;//线性表结构体存储空间的基地址　　用于存储数据元素
	int      length;//存储线性表的长度　　即元素的个数
	int      list_size;//线性表分配的空间大小
}SqList,*Ptr;//　结构体类型　　结构体指针类型

typedef Ptr SqListPtr;//为结构体指针取别名

typedef enum Status
{
	success,//成功=0
	fail,//失败=1
	fatal,//致命的错误＝2
	range_error//越界=3
}Status;

/*线性表的操作函数*/
Status InitList(SqListPtr L);           //构造一个空的线性表
Status DestroyList(SqListPtr L);        //销毁线性表
Status ClearList(SqListPtr L);			//清空线性表
Status ListEmpty(SqListPtr L);        //判定现行表是否为空
int    ListLength(SqListPtr L);         //返回线性表的长度
Status List_Retrival(SqListPtr L,int pos,ElemType *elem);//按位置查找　　在线性表L中查找位置pod的元素数据 放到elem中
int List_Locate(SqListPtr L,ElemType elem);//按数值查找　　　在线性表L中查找数值和elem相同的元素的位置　　放到pos中并返回
ElemType* PriorElem(SqListPtr L,ElemType cur_e,ElemType *pre_e);//用pre_e返回线性表中cur_e的前驱
ElemType* NextElem(SqListPtr L,ElemType cur_e,ElemType *next_e);//用next_e返回线性表中cur_e的后继
Status List_Insert(SqListPtr L,int pos,ElemType elem);//在线性表L中的pos位置之前插入元素数据elem
Status List_Replace(SqListPtr L,ElemType elem,ElemType newelem);//将在线性表L中的pos位置的数据元素替换成newelem
Status List_Delete(SqListPtr L,int pos);//在线性表L中删除pos位置的元素数据
void DisplayList(SqListPtr L);//显示顺序表中的数值

Status List_Union(SqListPtr La,SqListPtr Lb);//合并两个顺序结构的线性表


