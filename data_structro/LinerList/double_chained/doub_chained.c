#include "doub_chained.h"
DoubSqlistPtr InitHeadNode(DoubSqlistPtr L,int type,ElemType elem)//创建一个空的头节点或者首元节点 type=1:创建带头节点的双向链表 type=2:创建不带头结点的双向链表
{
	L=(struct Node*)malloc(sizeof(struct Node));//分配内存空间

	if(L==NULL)
	{
		printf("申请空间失败\n");
		return NULL;
	}

	if(type==1)
	{
		//创建头结点
		L->prior=NULL;
		L->next=NULL;
	}
	else if(type==2)
	{
		//创建首元节点
		L->prior=NULL;
		L->elem=elem;
		L->next=NULL;
	}
	else
	{
		printf("输入的类型不正确\n");
		return NULL;
	}
	return L;
}


DoubSqlistPtr CreatDoubList(DoubSqlistPtr L,int type)//type=1:创建带头节点的双向链表 type=2:创建不带头结点的双向链表
{
	if(type==1)
	{
		L=InitHeadNode(L,type,0);//创建头结点
	}
	else if(type==2)//输入数据创建首元节点
	{
		ElemType elem=0;
		printf("输入首元节点的数据域的数值:");
		scanf("%d",&elem);
		L=InitHeadNode(L,type,elem);
	}

	head=L;//节点头指针指向双向链表





	ElemType elem=-1;
	while(1)
	{
		printf("请为双向链表输入数据，输入-1结束循环:");
		int ret=scanf("%d",&elem);
		if(elem==-1)
			break;//-1退出循环
		if(ret!=1) 
			continue;//出错重新输入

		DoubSqlistPtr newNode=(struct Node*)malloc(sizeof(struct Node));//创建一个新的节点
		newNode->elem=elem;//数据域赋值
		newNode->prior=NULL;//初始化指针域
		newNode->next=NULL;

		printf("before head->elem=%d\n",head->elem);

		//将新节点链接到链表上
		head->next=newNode;//最后一个节点的直接后继指向新节点
		newNode->prior=head;//新节点的直接前驱指向最后一个节点　???
		head=head->next;//使head始终指向最后一个节点
		printf("after head->elem=%d\n",head->elem);
	}

	return L;
}

//打印双向链表的数据
void display(DoubSqlistPtr L)
{
	DoubSqlistPtr temp=L;//定义临时间节点指向链表的头结点或者首元节点

	if(temp==NULL)
	{
		printf("双向链表为空 display\n");
		//exit(EXIT_SUCCESS);
	}

	while(temp) 
	{
		//如果该节点无后继节点，说明此节点是链表的最后一个节点
		if (temp->next==NULL) 
		{
			printf("%d\n",temp->elem);
		}
		else
		{
			printf("%d <-> ",temp->elem);//打印头结点
		}
		temp=temp->next;
	}
}

//得到双向链表的长度
int DoubListLength(DoubSqlistPtr L)
{
	int len=0;
	if(L==NULL)
	{
		printf("双向链表为空\n");
		return 0;
	}
	else
	{
		while(L->next!=NULL)
		{
			len++;
			L=L->next;
		}
		len++;//最后一个节点的长度加回去
	}
	return len;
}

Status DoubList_Retrive(DoubSqlistPtr L,int pos,ElemType *elem)//按位置查找数值
{
	Status s=range_error;
	head=L;//头指针

	int len_L=DoubListLength(L);//得到链表的长度
	int i=1;//从头结点或者首元节点开始
	if(head==NULL)
	{
		printf("双向链表为空\n");
		s=fail;
	}
	else
	{
		if((pos<=0)||(pos>len_L))//位置非法
		{
			printf("位置越界,请输入正确的位置\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			while(i<pos)
			{
				head=head->next;
				i++;
			}
			if(i==pos)
			{
				*elem=head->elem;
				s=success;
			}
		}
	}
	return s;
}


Status DoubList_Locate(DoubSqlistPtr L,ElemType elem,int *pos)//按照数值查找位置  
{
	Status s=range_error;                       
	head=L;//头指针
	int i=1;//从头结点或者首元节点开始
	if(head==NULL)
	{
		printf("双向链表为空\n");
		s=fail;
	}
	else
	{
		while((elem!=head->elem)&&(head->next!=NULL))//相等　&&  没有移动到末尾
		{
			i++;
			head=head->next;
		}
		if(head->elem==elem)//存在数据元素相等  如果在末尾节点的时候数据元素匹配,数据域有数值，否则无数值
		{
			*pos=i;//得到位置
			s=success;
		}
	}
	return s;
}

DoubSqlistPtr DoubList_ReMove(DoubSqlistPtr L,int pos)//将头节点移动到指定的位置
{
	int i=1;
	head=L;
	if(head==NULL)
	{   
		printf("双向链表为空\n");
		return NULL;
	}
	else
	{
		while(i<pos)//从头结点开始移动
		{
			i++;
			head=head->next;
		}
	}
	return head;
}
DoubSqlistPtr DoubList_Insert(DoubSqlistPtr L,int pos,ElemType elem)//插入的位置　　插入的数据元素数值 
{
	head=L;//头指针

	int len_L=DoubListLength(L);//得到链表的长度
	printf("链表的长度:%d\n",len_L);

	if(head==NULL)
	{   
		printf("双向链表为空\n");
	}
	else
	{   
		if((pos<=0)||(pos>len_L))//位置非法
		{   
			printf("位置越界,请输入正确的位置\n");
			exit(EXIT_FAILURE);
		}
		else if(pos==1)//头部插入
		{
			printf("进入头结点的插入操作\n");

			DoubSqlistPtr newNode=(struct Node*)malloc(sizeof(struct Node));//创建一个新的节点
			newNode->elem=elem;//数据域赋值
			newNode->prior=NULL;//初始化指针域
			newNode->next=NULL;

			newNode->next=head;//新节点的直接后继指向头结点
			head->prior=newNode;//头结点的直接前驱指向新节点
			head=newNode;//head指向新的头节点
			//printf("head->elem=%d head->next->elem=%d\n",head->elem,head->next->elem);
			L=head;
			//printf("L->elem=%d\n",L->elem);
		}
		else
		{
			DoubSqlistPtr newNode=(struct Node*)malloc(sizeof(struct Node));//创建一个新的节点
			newNode->elem=elem;//数据域赋值
			newNode->prior=NULL;//初始化指针域
			newNode->next=NULL;

			int insert_type=0;//选择插入方法 1->前插  2->后插
			printf("请输入前插还是后插,1---前插　2------后插:::");
			scanf("%d",&insert_type);

			//将节点指针移动到相应的位置
			if(insert_type==1)//前插
			{   
				//printf("将head指针移动到执行位置\n");
				head=DoubList_ReMove(head,pos-1);//节点指针指向指定位置的前一个位置
				//printf("验证是否移动成功head->elem=%d\n",head->elem);
			}
			else if(insert_type==2)//后插
			{   
				//printf("将head指针移动到执行位置\n");
				head=DoubList_ReMove(head,pos);//节点指针指向指定位置
				//printf("验证是否移动成功head->elem=%d\n",head->elem);
			}

			if(pos==len_L)//到末尾　末尾插入
			{
				if(insert_type==1)//前插
				{
					//移动节点指针
					head->next->prior=newNode;//操作新节点的直接后继节点　　直接后继节点的直接前驱指向新节点
					newNode->next=head->next;//新节点的直接后继指向新节点的直接后继节点
					head->next=newNode;//操作新节点的直接前驱节点　　　直接前驱节点的直接后继指向新的节点
					newNode->prior=head;//新节点的直接前驱指向新节点的直接前驱节点
				}
				else if(insert_type==2)//后插
				{
					head->next=newNode;
					newNode->prior=head;
				}
			}
			else
			{
				//移动节点指针
				head->next->prior=newNode;//操作新节点的直接后继节点　　直接后继节点的直接前驱指向新节点
				newNode->next=head->next;//新节点的直接后继指向新节点的直接后继节点
				head->next=newNode;//操作新节点的直接前驱节点　　　直接前驱节点的直接后继指向新的节点
				newNode->prior=head;//新节点的直接前驱指向新节点的直接前驱节点
			}
		}

	}

	return L;
}

DoubSqlistPtr DoubList_Delete(DoubSqlistPtr L,int pos)//删除双向链表中某个位置的节点   
{
	head=L;//头指针

	int len_L=DoubListLength(L);//得到链表的长度
	printf("链表的长度:%d\n",len_L);

	if(head==NULL)//链表为空
	{   
		printf("双向链表为空\n");
	}
	else//链表非空
	{   
		if((pos<=0)||(pos>len_L))//位置非法
		{   
			printf("位置越界,请输入正确的位置\n");
			exit(EXIT_FAILURE);
		}
		else if(pos==1)//头部删除
		{
			DoubSqlistPtr temp=head->next;
			if(temp==NULL)//删除到剩下最后一个节点
			{
				printf("删除最后一个链表节点\n");
				L=temp;
			}
			else
			{
				printf("删除第一个元素\n");
				head->next->prior=NULL;
				free(head);
				head=NULL;
				L=temp;
			}
		}
		else if(pos==len_L)//到末尾　末尾插入
		{
			head=DoubList_ReMove(head,pos);//节点指针指向指定位置
			head->prior->next=NULL;
			free(head);
			head=NULL;
		}	
		else
		{
			head=DoubList_ReMove(head,pos);//节点指针指向指定位置
			head->prior->next=head->next;//将指定位置的节点的直接前驱节点的直接后继指向指定位置节点的直接后继节点
			head->next->prior=head->prior;//将指定位置节点的直接后继节点的直接前驱指向指定位置节点的直接前驱
			free(head);
			head=NULL;
		}

	}

	//display(L);
	return L;

}

DoubSqlistPtr DoubList_Destroy(DoubSqlistPtr L)//销毁双向链表
{

	 //head=L;//头指针
     int len_L=DoubListLength(L);//得到链表的长度
	 int i=len_L;//节点数
	 printf("链表的节点总数:%d\n",i);
	 while(i>=1)
	 {
		L=DoubList_Delete(L,1);//循环删除第一个节点
		i--;
	 printf("链表的节点总数:%d\n",i);
	 }
	 display(L);
return L;
}
int main(int argc,char* argv[])
{
	/*-----------创建双向链表-------------------*/
	printf("-------------------------------------------创建双向链表list1-------------------------------\n");
	DoubSqlistPtr list1=NULL;
	list1=CreatDoubList(list1,1);
	if(list1==NULL)
	{
		printf("创建双向链表失败\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("创建双向链表成功\n");
		display(list1);
	}

	printf("-------------------------------------------创建双向链表list2-------------------------------\n");
	DoubSqlistPtr list2=NULL;
	list2=CreatDoubList(list2,2);
	if(list2==NULL)
	{
		printf("创建双向链表失败\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("创建双向链表成功\n");
		display(list2);
	}

	/*----------得到链表长度*/
	/*	int len_list1=DoubListLength(list1);
		printf("list1的长度:%d\n",len_list1);

		int len_list2=DoubListLength(list2);
		printf("list2的长度:%d\n",len_list2);
		*/
	/*链表的查找*/
	/*	int pos_list1=5;
		ElemType elem_list1;
		Status status=DoubList_Retrive(list1,pos_list1,&elem_list1);
		if(status==success)
		{
		printf("链表list1中得到第%d个位置的元素%d\n",pos_list1,elem_list1);
		}

		int pos_list2=-1;
		ElemType elem_list2=55;
		status=DoubList_Locate(list2,elem_list2,&pos_list2);
		if(status==success)
		printf("在链表list2中与数值%d相同的数的节点是第%d个节点\n",elem_list2,pos_list2);
		else
		printf("链表list2中不能找到与%d相同的数,链表越界\n",elem_list2);
		*/

	/*双向链表链表的插入操作*/
	int pos=-2;
	while(1)
	{
		printf("请选择插入的位置 -1退出循环\npos=");
		scanf("%d",&pos);
		if(pos==-1) break;

		ElemType elem_insert=-2;
		printf("请选择要插入的数据\nelem=");
		scanf("%d",&elem_insert);

		list1=DoubList_Insert(list1,pos,elem_insert);
		printf("插入后显示结果\n");
		display(list1);
	}
	/*双向链表链表的插入操作*/
	int pos_d=-2;
	while(1)
	{
		printf("请选择删除的位置 -1退出循环\npos_d=");
		scanf("%d",&pos_d);
		if(pos_d==-1) break;

		list1=DoubList_Delete(list1,pos_d);

		printf("删除后打印结果\n");
		display(list1);
	}

	printf("销毁链表\n");
	list1=DoubList_Destroy(list1);
	if(list1==NULL)
		printf("销毁list1成功\n");
	return 0;
}
