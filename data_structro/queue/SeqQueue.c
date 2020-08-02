#include "SeqQueue.h"


Status SeqQueue_Creat(SeqQueuePtr Q)
{
	Status s;
	Q->elem=(ElemType*)malloc(SEQQUEUE_INIT_SIZE*sizeof(ElemType));//为数据元素分配内存空间
	if(Q->elem==NULL)
	{
		printf("内存空间分配失败\n");
		s=fatal;
	}
	else//初始化队列
	{
		Q->top=Q->rear=0;
		Q->QueueSize=SEQQUEUE_INIT_SIZE;//分配的内存空间
		s=success;
	}

	return s;
}

//元素个数的公式　(rear-front+maxsize)%maxsize

//显示队列中的数据元素
void DisplaySeqQueue(SeqQueuePtr Q)
{
	int top=Q->top;//队头
	int rear=Q->rear;//队尾

	printf("top=%d rear=%d QueueSize=%d\n",top,rear,Q->QueueSize);//打印队头队尾的数值
	for(int i=top;i<rear;i++)
	{
		printf("-->Q->elem[%d]=%d",i,Q->elem[i]);
	}
	printf("\n");
}
//判断顺序队列是否是空的
Status SeqQueue_isEmpty(SeqQueuePtr Q)
{
	Status s;
	if(Q->top==Q->rear)
		s=empty;//队列是空的
	else
		s=noempty;

	return s;
}

SeqQueuePtr SeqQueue_Remove(SeqQueuePtr Q)//对于假的队列溢出进行移动队列的操作
{
	int i=0;//假溢出时　将队尾中的数据移动到队头

	printf("top=%d rear=%d\n",Q->top,Q->rear);
	while(Q->top<Q->rear)
	{
		printf("Q->elem=%d i=%d Q->top=%d\n",Q->elem[i],i,Q->top);
		Q->elem[i]=Q->elem[Q->top];//将队列中的数据元素逐一移动队列头
		//printf("Q->elem=%d i=%d Q->top=%d\n",Q->elem[i],i,Q->top);
		i++;
		Q->top++;//移动到队头
	}
	printf("i=%d\n",i);
	//移动结束后top和rear移动队列的外面 重新将指针初始化
	Q->top=0;
	Q->rear=i;
	DisplaySeqQueue(Q);
	return Q;
}

//判断是否是假的溢出
Status SeqQueue_isFull(SeqQueuePtr Q)
{
	Status s;
	if(Q->rear>=Q->QueueSize)//当队尾达到了最大的分配空间长度
	{
		if(Q->top==0)
		{
			printf("因为大量数据入队导致的队列满了,需要增加内存的分配空间\n");
			s=full_true;
		}
		else
		{
			printf("假的队列溢出,需要进行移动队列的操作\n");
			s=full_false;
		}
	}
	else
	{
		s=success;
	}

	return s;
}


//进队列
Status EnterQueue(SeqQueuePtr Q,ElemType elem)
{
	//判断队列是否溢出
	Status s=SeqQueue_isFull(Q);
	if(s==full_true)//真的溢出
	{
		printf("真的溢出\n");
		//重新分配新的内存空间
		Q->elem=(ElemType*)realloc(Q->elem,(Q->QueueSize+SEQQUEUEINCREMENT)*sizeof(ElemType));//为队列中中的数据元素分配增加的存储空间　指针类型
		if(Q->elem==NULL)
		{
			printf("增加时分配内存失败\n");
			s=fatal;
		}
		else
		{
			Q->QueueSize=Q->QueueSize+SEQQUEUEINCREMENT;//分配的内存空间长度增加
			//进队
			Q->elem[Q->rear] = elem;
			printf("%d进入队列\n",Q->elem[Q->rear]);
			Q->rear++;
			s=success;
		}
	}
	else if(s==full_false)//假的溢出
	{
		printf("假的溢出\n");
		Q=SeqQueue_Remove(Q);//移动队列使其释放内存空间
		//进队
		Q->elem[Q->rear] = elem;
		printf("%d进入队列\n",Q->elem[Q->rear]);
		Q->rear++;
		s=success;
	}
	else//非满
	{
		printf("队列未溢出\n");
		//进队
		Q->elem[Q->rear] = elem;
		printf("%d进入队列\n",Q->elem[Q->rear]);
		Q->rear++;
		s=success;
	}
	return s;
}

//出队列
Status QuitQueue(SeqQueuePtr Q)
{
	Status s=SeqQueue_isEmpty(Q);

	if(s==empty)//空队列
	{
		printf("空队列,不能出队列\n");
		s=fail;
	}
	else if(s==noempty)//非空队列
	{
		//判断是否是满的
		s=SeqQueue_isFull(Q);
		if(s==full_false)//假的溢出
		{
			printf("假的溢出\n");
			Q=SeqQueue_Remove(Q);//移动队列使其释放内存空间
		}

		//出队列
		printf("%d 退出队列\n",Q->elem[Q->top]);
		Q->top++;//队头向上移动
		s=success;
	}

	return s;
}

Status CircleQueue_isEmpty(SeqQueuePtr Q)//判断循环队列是否为空
{
	Status s;
	if(Q->top==Q->rear)
	{
		s=empty;
	}
	else
		s=noempty;

	return s;
}

Status CircleQueue_isFull(SeqQueuePtr Q)//判断循环队列是否满了
{
	Status s;
	if( (Q->rear+1) % Q->QueueSize == Q->top )//队列满了　处理假溢出　　如果已有数据出了队列　　空出来的内存空间仍然有效
	{
		s=full_true;
	}
	else
		s=nofull;

	return s;
}


Status EnterCircleQueue(SeqQueuePtr Q,ElemType elem)//循环队列的进队列操作
{
	//先判断循环队列是否满了
	Status s=CircleQueue_isFull(Q);
	if(s==full_true)//队列是真的满了
	{
		printf("循环队列满了\n");

		//重新分配新的内存空间
		Q->elem=(ElemType*)realloc(Q->elem,(Q->QueueSize+SEQQUEUEINCREMENT)*sizeof(ElemType));//为队列中中的数据元素分配增加的存储空间　指针类型
		if(Q->elem==NULL)
		{
			printf("增加时分配内存失败\n");
			s=fatal;
		}
		else
		{
			Q->QueueSize=Q->QueueSize+SEQQUEUEINCREMENT;//分配的内存空间长度增加
			//进队
			Q->elem[Q->rear] = elem;//将队列满后的数值加入到空闲的内存单元中
			printf("%d进入队列\n",Q->elem[Q->rear]);
			Q->top=0;//　如果分配了重新初始化
			Q->rear=Q->QueueSize-SEQQUEUEINCREMENT;
			s=success;
		}
	}
	else//队列非满
	{
		printf("循环队列没有溢出\n");
		//进队
		Q->elem[Q->rear] = elem;
		printf("%d进入循环队列\n",Q->elem[Q->rear]);
		Q->rear=(Q->rear+1) % Q->QueueSize;//保证了Q->rear 一直在0~~~QueueSize-1内循环
		s=success;
	}
	return s;
}

Status QuitCircleQueue(SeqQueuePtr Q)//循环队列的出队操作
{
	//判断循环队列是否是空的
	Status s=CircleQueue_isEmpty(Q);
	if(s==empty)
	{
		printf("循环队列是空的,不能进行出队列的操作\n");
		s=fail;
	}
	else if(s==noempty)
	{
		printf("循环队列不是空的\n");
		//出队
		printf("%d将要出循环队列\n",Q->elem[Q->top]);
		Q->elem[Q->top]=-99;//出队列后将数值设置为-99
		Q->top=(Q->top+1) % Q->QueueSize;
		s=success;
	}

		return s;
}


int main(int argc,char* argv[])
{
	Status status;
/*
	SeqQueue queue1;
	status = SeqQueue_Creat(&queue1);//创建一个空的顺序队列

	if(status==success)
		printf("创建空的顺序队列成功\n");
	else
		printf("创建空的顺序队列失败\n");


	//入队列
	EnterQueue(&queue1,11);
	EnterQueue(&queue1,22);
	EnterQueue(&queue1,33);
	EnterQueue(&queue1,44);
	EnterQueue(&queue1,55);
	EnterQueue(&queue1,66);
	DisplaySeqQueue(&queue1);

	//出列
	QuitQueue(&queue1);
	QuitQueue(&queue1);
	QuitQueue(&queue1);
	QuitQueue(&queue1);
	DisplaySeqQueue(&queue1);

	//入队列
	EnterQueue(&queue1,77);
	EnterQueue(&queue1,88);
	EnterQueue(&queue1,99);
	EnterQueue(&queue1,100);
	DisplaySeqQueue(&queue1);

	//出列
	QuitQueue(&queue1);
	QuitQueue(&queue1);
	QuitQueue(&queue1);
	QuitQueue(&queue1);
	DisplaySeqQueue(&queue1);

	//入队列
	EnterQueue(&queue1,111);
	DisplaySeqQueue(&queue1);
*/
	//循环队列的验证
	SeqQueue queue2;
	status = SeqQueue_Creat(&queue2);//创建一个空的顺序队列

	if(status==success)
		printf("创建空的顺序队列queue2成功\n");
	else
		printf("创建空的顺序队列queue2失败\n");

	//入循环队列
	EnterCircleQueue(&queue2,111);
	EnterCircleQueue(&queue2,222);
	EnterCircleQueue(&queue2,333);
	EnterCircleQueue(&queue2,444);
	EnterCircleQueue(&queue2,555);
	EnterCircleQueue(&queue2,666);
	EnterCircleQueue(&queue2,777);
	DisplaySeqQueue(&queue2);

	//出循环队列
	QuitCircleQueue(&queue2);
	QuitCircleQueue(&queue2);
	QuitCircleQueue(&queue2);
	DisplaySeqQueue(&queue2);

	//入循环队列
	EnterCircleQueue(&queue2,888);
	EnterCircleQueue(&queue2,999);
	EnterCircleQueue(&queue2,211);
	EnterCircleQueue(&queue2,222);
	EnterCircleQueue(&queue2,223);
	DisplaySeqQueue(&queue2);
	EnterCircleQueue(&queue2,224);
	DisplaySeqQueue(&queue2);

	//入循环队列
	EnterCircleQueue(&queue2,1111);
	EnterCircleQueue(&queue2,2222);
	EnterCircleQueue(&queue2,3333);
	EnterCircleQueue(&queue2,4444);
	EnterCircleQueue(&queue2,5555);
	EnterCircleQueue(&queue2,6666);
	EnterCircleQueue(&queue2,7777);
	EnterCircleQueue(&queue2,8888);
	DisplaySeqQueue(&queue2);
	EnterCircleQueue(&queue2,9999);
	DisplaySeqQueue(&queue2);
	EnterCircleQueue(&queue2,100000);
	DisplaySeqQueue(&queue2);
	
	
	return 0;
}
