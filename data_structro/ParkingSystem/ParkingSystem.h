#ifndef __PARKINGSYSTEM__
#define __PARKINGSYSTEM__

/*-------车辆停车系统--------------------------*/


//头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//宏定义
#define MaxParkingSize 3    //停车场的最大车位数量


//结构体的定义
/*------1.时间信息--------*/
typedef struct Time//时间结构体
{
	int hour;//小时
	int minute;//分钟
}Time;


/*-------2.车辆信息--------------------*/
typedef struct CarNode//创建车辆信息的结构体
{
	char CarNum[10];//车牌号
	Time arrive;//车辆到达的时间
	Time leave;//车辆离开的时间
}CarNode, * CarNodePtr;
typedef CarNodePtr CarMessage;//车辆信息的结构体指针


/*----------停车场,临时停车场的栈----------*/
typedef struct SeqStackNode
{
	CarMessage CarData[MaxParkingSize];//停车场顺序栈上的车辆信息　　这些车辆的车辆信息保存在开辟的连续内存空间上
	int top;//栈顶
}SeqStackNode, * SeqStackNodePtr;
typedef SeqStackNode CarParkingNode;
typedef SeqStackNodePtr CarParking;//停车场顺序栈的结构体指针


/*-------------等待通道的链式队列------------------------------*/
typedef struct LinkQueueNode
{
	CarMessage CarData;//保存等待通道链式队列的车辆信息　　这些车辆是用链式结构串起来的
	struct LinkQueueNode* next;//指针域
}LinkQueueNode, * LinkQueueNodePtr;
typedef LinkQueueNodePtr LinkWaitArea;//队列节点指针

typedef struct WiatAearNode//定义等待链式队列的队头队尾指针
{
	LinkWaitArea top;//队头指针
	LinkWaitArea rear;//队尾指针
}WiatAearNode, * WiatAearNodePtr;

typedef WiatAearNodePtr WaitAear;//保存了队列节点的队头指针的结构体的指针
/**/
//操作的状态                      
typedef enum Status
{
	success,           //成功=0
	fail,              //失败=1
	fatal,             //致命的错误＝2
	range_error,      //越界=3
	empty,             //空
	noempty,           //非空
	full,              //满
	nofull			   //非满
}Status;

//基本操作
Status CarParking_Init(CarParking parkStack);/*创建停车场顺序栈*/
Status WaitAear_Init(WaitAear* waitQueue);/*创建等待通道链式队列*/
void   ParkingSystem_menu();//显示系统的菜单
Status CarArrival(CarParking parkStack, WaitAear waitQueue);//处理车辆将要进入停车场的时候的情况
Status CarLeave(CarParking parkStack,WaitAear waitQueue);//处理车辆将要离开停车场的情况

CarParking Stack_Push(CarParking parkStack, CarMessage cardata);//将车辆移动到停车场或者临时停车场
CarParking Stack_Pop(CarParking parkStack, float cost);//将车移出停车场或者临时停车场
void DisplayPark(CarParking parkStack);//显示停车场或者临时停车场的车辆信息
void DisplayWaitArea(WaitAear waitQueue);//显示链式队列中的内容
Status EnterWaitArea(WaitAear waitQueue, CarMessage cardata);//将因为停车场满需要等待的车辆放入等待通道的链式队列中
Status QuitWaitArea(WaitAear waitQueue);//出队 时间信息需要准确

void set_leaveTimeForStack(CarParking parkStack);//设置离开时间　到达时间也可以封装成函数
void set_leaveTime_ForQueue(WaitAear waitQueue);//设置等待通道离开时间　　到达时间也可以封装成函数
float get_cost(CarParking parkStack);//得到车辆的缴费信息


#endif

