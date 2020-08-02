#ifndef __SEQQUEUE__
#define __SEQQUEUE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//顺序队列的类型
 typedef int     ElemType;//实际的数据类型
 #define SEQQUEUE_INIT_SIZE 10//初始化顺序队列分配空间
 #define SEQQUEUEINCREMENT 10//每次增加顺序队列分配空间

//定义顺序队列的结构
typedef struct SeqQueue
{
	ElemType* elem;//数据放在一维数组中
	int       top;//队头
	int		  rear;//队尾
	int       QueueSize;//分配的内存空间
}SeqQueue,*Ptr;

typedef  Ptr SeqQueuePtr;//声明结构体指针

//操作的状态
 typedef enum Status
 {
     success,//成功=0
     fail,//失败=1
     fatal,//致命的错误＝2
     range_errori,//越界=3
	 empty,//空
	 noempty,//非空
	 full_true,//真的队列溢出
	 full_false,//假的队列溢出
	 nofull
 }Status;

//顺序队列的基本操作
Status SeqQueue_Creat(SeqQueuePtr Q);//创建一个顺序的空队列
void DisplaySeqQueue(SeqQueuePtr Q);//显示队列中的内容
Status SeqQueue_isEmpty(SeqQueuePtr Q);//判断队列是否是空的
SeqQueuePtr SeqQueue_Remove(SeqQueuePtr Q);//对于假的队列溢出进行移动队列的操作
Status SeqQueue_isFull(SeqQueuePtr Q);//判断队列是否是满的
Status EnterQueue(SeqQueuePtr Q,ElemType elem);//入队
Status QuitQueue(SeqQueuePtr Q);//出队

//循环队列的基本操作　循环队列的图形只具有想象的概念　　实际上用的结构体同顺序队列的一样 
//它用来处理假溢出的情况　　由于队列满的条件和队列空的条件都是top==rear 所以将其中一个内存单元空闲来区别队列满的情况和队列空的情况
Status CircleQueue_isEmpty(SeqQueuePtr Q);//判断循环队列是否为空
Status CircleQueue_isFull(SeqQueuePtr Q);//判断循环队列是否满了
Status EnterCircleQueue(SeqQueuePtr Q,ElemType elem);//循环队列的进队列操作
Status QuitCircleQueue(SeqQueuePtr Q);//循环队列的出队操作




#endif
