#include "LinkQueue.h"

LinkQueuePtr LinkQueue_Creat(LinkQueuePtr Q)//创建一个空的链式队列
{
	Q=(LinkQueuePtr)malloc(sizeof(QNode));//创建一个新的节点
	if(Q==NULL)
	{
		printf("节点内存空间分配失败\n");
	}
	else//初始化头结点
	{
		Q->next=NULL;
		printf("节点新建成功\n");
	}

	return Q;
}

Status EnterLinkQueue(LinkQueuePtr Q,ElemType elem)//入队
{
	//初始化指针
	Status s;

	LinkQueuePtr newnode=(LinkQueuePtr)malloc(sizeof(QNode));//创建一个新的节点
	if(newnode==NULL)
	{
		printf("新节点内存空间分配失败\n");
		s=fatal;
	}
	else//初始化头结点
	{
		newnode->elem=elem;//数据域赋值
		printf("%d进队列\n",newnode->elem);
		newnode->next=NULL;//新的节点的指针域指向NULL

		rear->next=newnode;//队尾的下一个节点指向新的节点
		rear=newnode;//移动队尾
		s=success;
	}

	//打印队头和队尾
	//printf("top->elem=%d top->next->elem=%d rear->elem=%d\n",top->elem,top->next->elem,rear->elem);

	return s;
}

void DisplayLinkQueue(LinkQueuePtr Q)//显示链式队列中的内容
{
	LinkQueuePtr head=top;
	while(head->next!=NULL)
	{
		printf("-->%d",head->elem);
		head=head->next;
	}
	if((top==NULL)||(top->next==NULL))	
	{
		printf("队列只有头结点或者为空\n");
	}
	else//队列非空
	{
		printf("-->%d\n",head->elem);//打印最后一个元素i
	}
}

Status QuitLinkQueue(LinkQueuePtr Q)//出队
{
	Status s;
	if((top==NULL)||(top->next==NULL))	
	{
		printf("队列只有头结点或者为空\n");
		s=fail;
	}
	else//队列非空
	{
		LinkQueuePtr head=top->next;//先进先出原则
		printf("%d出队列\n",head->elem);
		top->next=head->next;//头结点指向下一个节点

		if(head==rear)//如果是尾节点
		{
			rear=head;//尾节点指向头结点
		}
		free(head);//释放出队列的节点
		s=success;
	}

	return s;
}
int main(int argc,char* argv[])
{
	LinkQueuePtr queue1=NULL;
	queue1=LinkQueue_Creat(queue1);
	//初始化top rear指针
	top=queue1;
	rear=queue1;
	//入队列
	EnterLinkQueue(queue1,11);
	EnterLinkQueue(queue1,22);
	EnterLinkQueue(queue1,33);
	EnterLinkQueue(queue1,44);

	//显示队列的数据
	DisplayLinkQueue(queue1);

	//出队列
	QuitLinkQueue(queue1);
	QuitLinkQueue(queue1);
	QuitLinkQueue(queue1);
	QuitLinkQueue(queue1);
	DisplayLinkQueue(queue1);
}
