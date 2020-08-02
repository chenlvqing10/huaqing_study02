/*-------车辆停车系统-------*/
#include "ParkingSystem.h"
Status CarParking_Init(CarParking parkStack)/*创建停车场顺序栈*/
{
	Status s;
	parkStack->top = -1;//初始化栈顶

	for (int i = 0; i < MaxParkingSize; i++)
	{
		parkStack->CarData[i] = (CarMessage)malloc(sizeof(CarNode));//为顺序栈内的每辆汽车分配内存空间

		if (parkStack->CarData[i] == NULL)//内存分配失败
		{
			printf("内存分配失败\n");
			s = fatal;
		}
		else//内存分配成功
		{
			s = success;
		}
	}

	return s;
}

Status WaitAear_Init(WaitAear* waitQueue)/*创建等待通道链式队列*/
{
	Status s;
	*waitQueue = (WaitAear)malloc(sizeof(WiatAearNode));//需要先分配队头队尾指针节点的内存空间
	(*waitQueue)->top = (LinkWaitArea)malloc(sizeof(LinkQueueNode));//创建一个新的头结点　　队头指针指向该节点
	(*waitQueue)->top->CarData = (CarMessage)malloc(sizeof(CarNode));//为车辆信息也分配内存空间
	if ((*waitQueue)->top == NULL)
	{
		printf("链式队列内存分配失败\n");
		s = fatal;
	}
	else
	{
		(*waitQueue)->top->next = NULL;//初始化链式队列
		(*waitQueue)->rear = (*waitQueue)->top;//空队列的时候队头和队尾都指向头结点
		s = success;
	}
	return s;
}

void ParkingSystem_menu()
{
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("-----------------------------------欢迎来到车辆停车管理系统----------------------------------------------------------------\n");
	printf("-----------------------------------1.有车辆将要进入停车场------------------------------------------------------------------\n");
	printf("-----------------------------------2.有车辆将要离开停车场------------------------------------------------------------------\n");
	printf("-----------------------------------3.查看停车场和等待通道内的车辆信息------------------------------------------------------\n");
	printf("-----------------------------------4.退出系统------------------------------------------------------------------------------\n");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
}
//进栈
CarParking Stack_Push(CarParking parkStack, CarMessage cardata)
{
	if(parkStack->top>MaxParkingSize-1)
	{
		printf("栈满了无法进栈");
		return NULL;
	}
	else
	{
		parkStack->top++;//栈顶大小+1
		strcpy(parkStack->CarData[parkStack->top]->CarNum, cardata->CarNum);//保存车辆进入停车场时候的车牌号
		parkStack->CarData[parkStack->top]->arrive.hour = cardata->arrive.hour;//保存车辆进入停车场时候的时间(小时)
		parkStack->CarData[parkStack->top]->arrive.minute = cardata->arrive.minute;//保存车辆进入停车场时候的时间(分钟)
		parkStack->CarData[parkStack->top]->leave.hour = cardata->leave.hour;//保存车辆进入停车场时候的时间(小时)
		parkStack->CarData[parkStack->top]->leave.minute = cardata->leave.minute;//保存车辆进入停车场时候的时间(分钟)
		printf("车牌号是%s的车辆在%d:%d进入停车场顺序栈或者临时停车场\n", parkStack->CarData[parkStack->top]->CarNum, parkStack->CarData[parkStack->top]->arrive.hour,
				parkStack->CarData[parkStack->top]->arrive.minute);
	}

	return parkStack;
}
//出栈
CarParking Stack_Pop(CarParking parkStack, float cost)
{
	if (parkStack->top == -1)
	{
		printf("顺序栈是空的\n");
		return NULL;
	}
	else//栈非空
	{
		if (cost >= 0)
			printf("车牌号是%s的车辆在%d:%d进入停车场 在%d:%d离开停车场顺序栈 已缴费%2f \n", parkStack->CarData[parkStack->top]->CarNum, parkStack->CarData[parkStack->top]->arrive.hour,
					parkStack->CarData[parkStack->top]->arrive.minute, parkStack->CarData[parkStack->top]->leave.hour, parkStack->CarData[parkStack->top]->leave.minute, cost);
		else if (cost == -99)
			printf("车牌号是%s的车辆在%d:%d进入停车场 在%d:%d离开停车场顺序栈 它将被移动到临时停车场 \n", parkStack->CarData[parkStack->top]->CarNum, parkStack->CarData[parkStack->top]->arrive.hour,
					parkStack->CarData[parkStack->top]->arrive.minute, parkStack->CarData[parkStack->top]->leave.hour, parkStack->CarData[parkStack->top]->leave.minute);
		else
			printf("车牌号是%s的车辆在%d:%d进入临时停车场 在%d:%d离开临时停车场 它将被移回到停车场 \n", parkStack->CarData[parkStack->top]->CarNum, parkStack->CarData[parkStack->top]->arrive.hour
					, parkStack->CarData[parkStack->top]->arrive.minute, parkStack->CarData[parkStack->top]->leave.hour, parkStack->CarData[parkStack->top]->leave.minute);

		parkStack->top--;
	}
	return parkStack;
}

//显示停车场顺序栈中的车辆信息
void DisplayPark(CarParking parkStack)
{
	if(parkStack==NULL)
	{
		
		printf("停车场或者临时停车场是空的\n");
	}
	else
	{
		int top = parkStack->top;//原来栈中的栈顶不能减少　定义一个中间变量来接收栈顶的数值
		if (top == -1)
		{
			printf("停车场或者临时停车场是空的\n");
		}
		else
		{
			while (top >= 0)
			{
				printf("->停车场顺序栈内 车位:%d 车牌号%s 到达的时间:%d::%d 离开的时间:%d::%d->\n", top + 1, parkStack->CarData[top]->CarNum,
						parkStack->CarData[top]->arrive.hour, parkStack->CarData[top]->arrive.minute,
						parkStack->CarData[top]->leave.hour, parkStack->CarData[top]->leave.minute);
				top--;
			}
		}
	}
	printf("\n");
}

void DisplayWaitArea(WaitAear waitQueue)//显示链式队列中的内容
{
	int car_num = 1;
	if (waitQueue->top == NULL)
	{
		printf("等待通道链式队列为空\n");
	}
	else//队列非空
	{
		LinkWaitArea head = waitQueue->top->next;//头结点不打印
		if (head == NULL)
		{
			printf("等待通道链式队列只有头结点\n");
		}
		else
		{
			while (head->next != NULL)
			{
				printf("->等待通道队列内  车位:%d 车牌号%s 到达的时间:%d::%d 离开的时间:%d::%d->\n", car_num, head->CarData->CarNum, head->CarData->arrive.hour, head->CarData->arrive.minute,
						head->CarData->leave.hour, head->CarData->leave.minute);
				car_num++;
				head = head->next;
			}
			printf("->等待通道队列内   车位:%d 车牌号%s 到达的时间:%d::%d 离开的时间:%d::%d->\n", car_num, head->CarData->CarNum, head->CarData->arrive.hour, head->CarData->arrive.minute,
				head->CarData->leave.hour, head->CarData->leave.minute);
		}
	}
	printf("\n");
}

Status EnterWaitArea(WaitAear waitQueue, CarMessage cardata)//将因为停车场满需要等待的车辆放入等待通道的链式队列中
{
	Status s;
	LinkWaitArea newnode = (LinkWaitArea)malloc(sizeof(LinkQueueNode));//创建一个新的头结点　　队头指针指向该
	newnode->CarData = (CarMessage)malloc(sizeof(CarNode));

	if (newnode == NULL)
	{
		printf("新节点内存空间分配失败\n");
		s = fatal;
	}
	else//连接新的节点
	{
		//为进入队列的车辆赋值
		strcpy(newnode->CarData->CarNum, cardata->CarNum);//保存车辆进入等待通道时候的车牌号
		newnode->CarData->arrive.hour = cardata->arrive.hour;//保存车辆进入等待通道时候的时间(小时)
		newnode->CarData->arrive.minute = cardata->arrive.minute;//保存车辆进入等待通道时候的时间(分钟)
		newnode->CarData->leave.hour = cardata->leave.hour;//保存车辆进入等待通道时候的时间(小时)
		newnode->CarData->leave.minute = cardata->leave.minute;//保存车辆进入等待通道时候的时间(分钟)

		printf(" 车牌号%s的车辆在%d:%d进入队列\n", newnode->CarData->CarNum, newnode->CarData->arrive.hour, newnode->CarData->arrive.minute);
		newnode->next = NULL;//新的节点的指针域指向NULL

		waitQueue->rear->next = newnode;//队尾的下一个节点指向新的节点
		waitQueue->rear = newnode;//移动队尾
		s = success;
	}
	return s;
}

Status QuitWaitArea(WaitAear waitQueue)//出队 时间信息需要准确
{
	//得到时间信息
	int leavequeue_hour = 0;
	int  leavequeue_minute = 0;
	time_t rawtime;
	struct tm* currenttime;
	time(&rawtime);
	currenttime = localtime(&rawtime);
	leavequeue_hour = currenttime->tm_hour;
	leavequeue_minute = currenttime->tm_min;

	Status s;
	if ((waitQueue->top == NULL) || (waitQueue->top->next == NULL))
	{
		printf("队列只有头结点或者为空\n");
		s = fail;
	}
	else//队列非空
	{
		LinkWaitArea head = waitQueue->top->next;//先进先出原则
		head->CarData->leave.hour = leavequeue_hour;
		head->CarData->leave.minute = leavequeue_minute;
		printf(" 车牌号%s的车辆在%d:%d进入队列 在%d:%d离开队列\n", head->CarData->CarNum, head->CarData->arrive.hour, head->CarData->arrive.minute,
				head->CarData->leave.hour, head->CarData->leave.minute);

		waitQueue->top->next = head->next;//头结点指向下一个节点

		if (head == waitQueue->rear)//如果是尾节点
		{
			waitQueue->rear = head;//尾节点指向头结点
		}
		free(head);//释放出队列的节点
		s = success;
	}

	return s;
}

Status CarArrival(CarParking parkStack, WaitAear waitQueue)//处理车辆将要进入停车场的时候的情况 
{
	Status s = success;
	//得到时间信息
	int  hour = 0;
	int  minute = 0;
	time_t rawtime;
	struct tm* currenttime;
	time(&rawtime);
	currenttime = localtime(&rawtime);
	hour = currenttime->tm_hour;
	minute = currenttime->tm_min;
	//printf("当前的小时:%d 当前的分钟:%d\n", hour, minute);
	//得到车牌号的信息
	char CarNum[10] = { 0 };
	printf("请输入车辆的车牌号:");
	scanf("%s", CarNum);
	printf("车牌号:%s\n", CarNum);

	//构造车辆结构体
	CarNode cardata;
	strcpy(cardata.CarNum, CarNum);
	cardata.arrive.hour = hour;
	cardata.arrive.minute = minute;
	cardata.leave.hour = 0;
	cardata.leave.minute = 0;

	//判断停车场是否已经满了
	if (parkStack->top >= MaxParkingSize - 1)//当栈顶达到max-1时候说明栈满了　即停车场满了
	{
		printf("栈满了,将车辆加入到等待通道链式队列中\n");
		EnterWaitArea(waitQueue, &cardata);
		DisplayWaitArea(waitQueue);
		DisplayPark(parkStack);
	}
	else
	{
		printf("栈未满,将车辆放入停车场顺序栈中\n");
		parkStack = Stack_Push(parkStack, &cardata);
		DisplayPark(parkStack);
		DisplayWaitArea(waitQueue);
	}

	return s;
}

void set_leaveTimeForStack(CarParking parkStack)//设置离开时间　到达时间也可以封装成函数
{

	//得到时间信息
	int  leave_hour = 0;
	int  leave_minute = 0;
	time_t rawtime;
	struct tm* currenttime;
	time(&rawtime);
	currenttime = localtime(&rawtime);
	leave_hour = currenttime->tm_hour;
	leave_minute = currenttime->tm_min;
	//printf("离开的小时:%d 离开的分钟:%d\n", leave_hour, leave_minute);

	parkStack->CarData[parkStack->top]->leave.hour = leave_hour;//保存车辆离开停车场时候的时间(小时)
	parkStack->CarData[parkStack->top]->leave.minute = leave_minute;//保存车辆离开停车场时候的时间(分钟)
}

void set_leaveTime_ForQueue(WaitAear waitQueue)
{

	//得到时间信息
	int  leave_hour = 0;
	int  leave_minute = 0;
	time_t rawtime;
	struct tm* currenttime;
	time(&rawtime);
	currenttime = localtime(&rawtime);
	leave_hour = currenttime->tm_hour;
	leave_minute = currenttime->tm_min;
	//printf("离开的小时:%d 离开的分钟:%d\n", leave_hour, leave_minute);

	waitQueue->top->next->CarData->leave.hour = leave_hour;
	waitQueue->top->next->CarData->leave.minute = leave_minute;
}

//得到车辆的缴费信息
float get_cost(CarParking parkStack)
{
	//printf("车辆%s 进入车场的时间:%d::%d   车辆离开车场的时间:%d::%d\n", parkStack->CarData[parkStack->top]->CarNum, parkStack->CarData[parkStack->top]->arrive.hour,
	//		parkStack->CarData[parkStack->top]->arrive.minute, parkStack->CarData[parkStack->top]->leave.hour, parkStack->CarData[parkStack->top]->leave.minute);

	int arrive_hour = parkStack->CarData[parkStack->top]->arrive.hour;
	int arrive_minute = parkStack->CarData[parkStack->top]->arrive.minute;
	int leave_hour = parkStack->CarData[parkStack->top]->leave.hour;
	int leave_minute = parkStack->CarData[parkStack->top]->leave.minute;

	int test_hour = 10, test_minute = 20;

	int all_minute = (leave_hour + test_hour - arrive_hour) * 60 + (leave_minute + test_minute - arrive_minute);//将其转换为总的分钟数  没有考虑天数

	printf("车辆%s 共停了%d分钟", parkStack->CarData[parkStack->top]->CarNum, all_minute);

	float cost = 0;
	if (all_minute <= 60)
		cost = 0;
	else
	{
		cost = (all_minute / 60) * 2;
		if (cost >= 30)
			cost = 30;
	}
	printf("需要支付的费用:%.2f\n", cost);

	return cost;
}

//处理车辆离开停车场
Status CarLeave(CarParking parkStack, WaitAear waitQueue)//处理车辆将要离开停车场的情况
{
	//变量的定义和初始化
	Status s;
	CarParkingNode Temppark;//新建临时停车场的节点
	CarParking     temppackStack=NULL;
	//建立临时停车场
	s = CarParking_Init(&Temppark);
	if (s == success)
		printf("创建临时停车场成功\n");
	else
		printf("创建临时停车场失败\n");

	float cost = 0;

	//判断停车场的情况
	if (parkStack->top == -1)
	{
		printf("停车场内没有车辆\n");
	}
	else
	{
		int carnum_leave,ret;
		char c;
		printf("停车场有%d辆车,请你输入哪辆车需要离开停车场:", parkStack->top + 1);

		while ((ret = scanf("%d", &carnum_leave)) <= 0)//如果输入非法字符比如GGG，那么停车场内的车都会被移动到 临时停车场内，需要清除键盘缓冲区数据
		{
			//printf("carnum_leave=%d,ret=%d", carnum_leave, ret);
			//int ret_f=fflush(stdin);//不能清除键盘缓冲区数据
			while ((c=getchar())!='\n')//清除键盘缓冲区数据，保证下次正常读取键盘输入
			{
				printf("c=%c\n",c);
			}
			printf("输入数字非法，请重新输入:\n");
		}

		while ((carnum_leave > parkStack->top + 1))
		{
			printf("停车场内没有这辆车,请重新输入:\n");
			scanf("%d", &carnum_leave);
		}


		if (parkStack->top + 1 == carnum_leave)//不需要用到临时表
		{
			set_leaveTimeForStack(parkStack);
			cost = get_cost(parkStack);//计算缴费费用
			//进行出栈操作
			parkStack = Stack_Pop(parkStack, cost);
			printf("车辆离开停车场后停车场内车辆的情况\n");
			DisplayPark(parkStack);
		}
		else
		{
			while (parkStack->top >= carnum_leave)
			{
				//set_leaveTime(parkStack);放入到临时栈中的时间信息中　到达时间需要保存原来栈中的数据,离开时间是无效的可以不设定
				//构造车辆结构体
				CarNode cardata;
				strcpy(cardata.CarNum, parkStack->CarData[parkStack->top]->CarNum);
				cardata.arrive.hour = parkStack->CarData[parkStack->top]->arrive.hour;
				cardata.arrive.minute = parkStack->CarData[parkStack->top]->arrive.minute;
				cardata.leave.hour = parkStack->CarData[parkStack->top]->leave.hour;
				cardata.leave.minute = parkStack->CarData[parkStack->top]->leave.minute;
				//从停车场出栈
				parkStack = Stack_Pop(parkStack, -99);//-99:临时出栈
				temppackStack = Stack_Push(&Temppark, &cardata);
			}
			/*
			printf("移动操作后停车场内车辆的情况\n");
			DisplayPark(parkStack);
			printf("移动操作后临时停车场内车辆的情况\n");
			DisplayPark(temppackStack);
			*/
			//从停车场内将要求离开停车场的车辆出栈
			set_leaveTimeForStack(parkStack);
			cost = get_cost(parkStack);//计算缴费费用
			parkStack = Stack_Pop(parkStack, cost);
			
			/*
			printf("车辆离开停车场后停车场车辆的情况\n");
			DisplayPark(parkStack);
			printf("车辆离开停车场后临时停车场车辆的情况\n");
			DisplayPark(temppackStack);
			*/

			//将临时停车场中的车辆出栈　　并将其按原来的顺序再次放入停车场栈中
			while (temppackStack->top != -1)
			{
				//构造车辆结构体
				set_leaveTimeForStack(temppackStack);
				CarNode cardata;
				strcpy(cardata.CarNum, temppackStack->CarData[temppackStack->top]->CarNum);
				cardata.arrive.hour = temppackStack->CarData[temppackStack->top]->arrive.hour;
				cardata.arrive.minute = temppackStack->CarData[temppackStack->top]->arrive.minute;
				cardata.leave.hour = temppackStack->CarData[temppackStack->top]->leave.hour;
				cardata.leave.minute = temppackStack->CarData[temppackStack->top]->leave.minute;
				temppackStack = Stack_Pop(temppackStack, -999);//-999:打印的信息不同
				cardata.leave.hour = 0;
				cardata.leave.minute = 0;

				parkStack = Stack_Push(parkStack, &cardata);
			}
		}
	}
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
			printf("离开车辆缴费完成后移动操作后停车场内车辆的情况\n");
			DisplayPark(parkStack);
			printf("离开车辆缴费完成后移动操作后临时停车场内车辆的情况\n");
			DisplayPark(temppackStack);
			printf("离开车辆缴费完成后移动操作后等待通道内内车辆的情况\n");
			DisplayWaitArea(waitQueue);
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
	printf("/*---------------------------------------------------------------------------------------------------*/\n");

	//车辆缴费结束驶离停车场后　查看等待通道队列是否有等待车辆，需要将所有的等待车辆从队列中移动停车场中　知道停车场顺序栈满了
	while ((parkStack->top < MaxParkingSize - 1) && ((waitQueue->top != NULL) && (waitQueue->top->next != NULL)))//当停车场未满的时候  等待通道不空的时候
	{
		//构造车辆结构体
		set_leaveTime_ForQueue(waitQueue);
		CarNode cardata;
		strcpy(cardata.CarNum, waitQueue->top->next->CarData->CarNum);
		cardata.arrive.hour = waitQueue->top->next->CarData->leave.hour;
		cardata.arrive.minute = waitQueue->top->next->CarData->leave.minute;
		cardata.leave.hour = 0;
		cardata.leave.minute = 0;
		//出等待通道的链式队列
		QuitWaitArea(waitQueue);
		//DisplayWaitArea(waitQueue);
		//进入停车场顺序栈
		parkStack = Stack_Push(parkStack, &cardata);
		//DisplayPark(parkStack);
	}
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
			printf("移动等待通道车辆后停车场内车辆的情况\n");
			DisplayPark(parkStack);
			printf("移动等待通道车辆后临时停车场内车辆的情况\n");
			DisplayPark(temppackStack);
			printf("移动等待通道车辆后等待通道内内车辆的情况\n");
			DisplayWaitArea(waitQueue);
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
	printf("/*---------------------------------------------------------------------------------------------------*/\n");
	return s;
}
//主函数
int main(int argc, char* argv[])
{
	/*变量的初始化*/
	Status status;
	CarParkingNode park;//申明停车场顺序栈  
	WaitAear       wait = NULL;//申明等待通道链式队列

	/*构造数据结构　停车场　临时停车场　等待队列*/
	status = CarParking_Init(&park);
	if (status == success)
	{
		printf("停车场创建成功\n");
	}
	else
	{
		printf("停车场不能创建成功\n");
	}

	status = WaitAear_Init(&wait);
	if (status == success)
	{
		printf("等待队列创建成功\n");
	}
	else
	{
		printf("等待队列不能创建成功\n");
	}


	/*停车管理*/
	char ch = 0;
	ParkingSystem_menu();//系统界面
	while ((ch = getchar()) != -99)//死循环　按4退出系统
	{
		switch (ch)
		{
			case '1':
				printf("有车进入了\n");
				CarArrival(&park, wait);
				break;
			case '2':
				printf("有车离开了\n");
				CarLeave(&park, wait);
				break;
			case '3':
				printf("显示信息\n");
				printf("停车场内的车辆信息:\n");
				DisplayPark(&park);
				printf("等待通道内的车辆信息:\n");
				DisplayWaitArea(wait);
				break;
			case '4':
				printf("退出系统\n");
				exit(EXIT_SUCCESS);
				break;
			case '\n'://排除回车的干扰
				break;
			default:
				printf("请输入1~4之间的数字\n");
				break;
		}
	}

	return 0;
}

