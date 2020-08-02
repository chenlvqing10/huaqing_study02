#include "chained.h"

SqlistPtr Initlist(SqlistPtr L)//创建一个空的头节点
{
	L=(struct Node*)malloc(sizeof(struct Node));//分配内存空间
	//L->elem=5555;
	L->next=NULL;//初始化指针域为空　　数据越可以赋值为节点长度，初始化的时候不需要赋值
	//printf("data=%d  next=%p\n",L->elem,L->next);

	return L;
}

SqlistPtr HeadCreateList(SqlistPtr L,ElemType data[],int len)//头插法创建一个单链表
{
	SqlistPtr list=Initlist(L);//定义一个中间变量的节点，指向空的头节点
	SqlistPtr p;

	//printf("len=%d\n",len);

	for(int i=len-1;i>=0;i--)//头插法　从最后一个开始插入
	{
		p=(struct Node*)malloc(sizeof(struct Node));//分配内存空间  建立一个新的节点
		if(p)
		{
			p->elem=data[i];//数据域赋值
			//printf("data=%d\n",p->elem);
			p->next=list->next;//新节点的指针一直指向头结点的next指针域
			list->next=p;//头结点的指针域一直指向新的节点的头部
		}
		else
		{
			break;
		}
	}

	return (SqlistPtr)list;
}

SqlistPtr TailCreateList(SqlistPtr L,ElemType data[],int len)//尾插法创建一个单链表
{
	Status s=success;
	SqlistPtr list=Initlist(L);//定义一个中间变量的节点，指向空的头节点
	SqlistPtr p;//新的节点
	SqlistPtr r;//定义一个节点r　指向的始终是该链表的最后一个node结构
	r=list;//r首先指向头结点

	for(int i=0;i<=len-1;i++)//尾插法  从第一个数据元素开始插入
	{
		p=(struct Node*)malloc(sizeof(struct Node));//分配内存空间  建立一个新的节点
		if(p)
		{
			p->elem=data[i];//数据域赋值
			r->next=p;//将p插入到链表的最后一个node结构的后面
			p->next=NULL;//此时p已经是链表的最后一个了，给p的next赋值
			r=p;//让r等于链表的最后一个node结构，即p节点
		}
		else
		{
			s=fail;
			break;
		}
	}

	return (SqlistPtr)list;

}

int  ListLength(SqlistPtr L)//得到单链表的长度    
{
	int len=0;
	while(L)
	{
		len++;
		L=L->next;
	}

	return len;
}

void DisplayList(SqlistPtr L)//递归显示单链表的内容　不显示头结点的内容
{
	//printf("data in the list=%d\n",L->elem);
	if((L==NULL)||(L->next==NULL))//只有头结点
	{
		printf("空的单链表或者已经到单链表的尾部\n");
	}
	else
	{
		L=L->next;
		printf("data in the list=%d\n",L->elem);
		DisplayList(L);
	}
}
void DisplayList_Head(SqlistPtr L)//递归显示单链表的内容　显示头结点的内容
{
	if((L==NULL)||(L->next==NULL))//只有头结点
	{
		printf("空的单链表或者已经到单链表的尾部\n");
	}
	else
	{
		printf("data in the list=%d\n",L->elem);
		L=L->next;
		DisplayList(L);
	}
}

SqlistPtr List_Remove(SqlistPtr L,int pos)//移动节点到指定的位置
{
	SqlistPtr p=L;//节点指针p指向单链表的头结点
	int i=0;//从头结点开始计数
	if(pos>0)//pos==0　表示是头结点　　不需要移动位置
	{
		while(i<pos)
		{
			i++;
			p=p->next;//指向下一个节点
		}
	
		printf("i=%d pos=%d\n",i,pos);
	}

	return p;
}

Status List_Retrieve(SqlistPtr L,int pos,ElemType *elem)//按位置查找单链表中的数据
{
	Status s=range_error;//越界
	SqlistPtr p=L->next;//节点指针p指向第一个数据元素
	int i=1;//位置计数器   第几个节点
	while(p && i<pos)//单链表中存在数据元素　&&  未达到要求的位置
	{
		i++;//移动到下一个节点的位置
		p=p->next;//移动到下一个节点
	}//while循环结束　达到了致指定的节点位置

	if(p && (i==pos) )//该节点存在　达到指定的节点位置
	{
		*elem = p->elem;//将该节点位置的数据放到elem指针中
		s=success;
	}

	return s;
}

Status List_Locate(SqlistPtr L,ElemType elem,int* pos)//按数值在单链表中查找是否存在该数
{
	Status s=range_error;
	SqlistPtr p=L->next;//跳过头结点
	int i=1;//节点位置计数器
	while(p && (p->elem != elem))//单链表中该节点存在数据元素　&&  该节点数据域的数值不等于指定查找的数据数值
	{
		i++;//节点位置向下一个移动
		p=p->next;//节点向后移动一个
	}//当单链表中不存在数据　或者找到了该数据之后跳出循环


	if(p)//跳出循环后该节点存在数据　不是指向NULL，说明未到单链表末尾节点
	{
		*pos=i;//保存节点位置
		s=success;
	}
	return s;
}

Status List_InsertByPre(SqlistPtr L,int pos,ElemType elem)//在单链表的pos位置之前插入数据元素elem  前插法  头结点作为0号节点
{
	Status s=range_error;
	SqlistPtr p;//声明一个新的节点指针,定位到指定的位置
	if(L==NULL)//单链表为空
	{
		printf("单链表为空请先创建单链表\n");
		exit(EXIT_FAILURE);
	}
	else//单链表非空
	{
		int len_L=ListLength(L);//得到单链表的长度
		if(pos>len_L-1)
		{
			printf("单链表中没有该位置\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			if(pos==0)//头结点之前插入  这个有问题???????
			{
				p=L;//节点指针移动到指定位置的前一个
				printf("insert 在单链表L中的第%d个节点找到数据元素%d\n",pos,p->elem);
				//在头结点进行前插入的操作
				SqlistPtr newnode=(struct Node*)malloc(sizeof(struct Node));//分配内存空间  建立一个新的节点
				if(newnode)//新节点创建成功
				{
					newnode->elem=elem;//将插入的数据赋值给新节点
					//移动指针
					newnode->next=p;//新的节点的指针域指向头结点
					p=newnode;//头指针指向新的节点
					s=success;
					//L=p;
					//DisplayList(p);
					//DisplayList(L);
				}
				else
					s=fail;//表示插入失败
			}
			else
			{
				p=List_Remove(L,pos-1);//节点指针移动到指定位置的前一个
				printf("insert 在单链表L中的第%d个节点找到数数据元素%d\n",pos-1,p->elem);
				//进行前插入的操作
				SqlistPtr newnode=(struct Node*)malloc(sizeof(struct Node));//分配内存空间  建立一个新的节点
				if(newnode)//新节点创建成功
				{
					newnode->elem=elem;//将插入的数据赋值给新节点
					//移动指针
					newnode->next=p->next;
					p->next=newnode;
					s=success;
				}
				else
					s=fail;//表示插入失败
			}
		}
	}//end p!=NULL

	return s;
}

Status List_InsertByBack(SqlistPtr L,int pos,ElemType elem)//在单链表的pos位置之后插入数据元素elem  后插法  头结点作为0号节点
{
	Status s=range_error;
	SqlistPtr p;//声明一个新的节点指针,定位到指定的位置
	if(L==NULL)//单链表为空
	{
		printf("单链表为空请先创建单链表\n");
		exit(EXIT_FAILURE);
	}
	else//单链表非空
	{
		int len_L=ListLength(L);//得到单链表的长度
		if(pos>len_L-1)
		{
			printf("单链表中没有该位置\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			p=List_Remove(L,pos);//节点指针移动到指定位置
			printf("insert 在单链表L中的第%d个节点找到数数据元素%d\n",pos,p->elem);
			//进行前插入的操作
			SqlistPtr newnode=(struct Node*)malloc(sizeof(struct Node));//分配内存空间  建立一个新的节点
			if(newnode)//新节点创建成功
			{
				newnode->elem=elem;//将插入的数据赋值给新节点
				//移动指针
				newnode->next=p->next;
				p->next=newnode;
				s=success;
			}
			else
				s=fail;//表示插入失败
		}
	}//end p!=NULL

	return s;
}

Status List_Delete(SqlistPtr L,int pos)//删除单链表中某个位置的节点
{
	Status s=range_error;
	SqlistPtr p;//声明一个新的节点指针,定位到指定的位置

	if(L==NULL)//单链表为空
	{
		printf("单链表为空请先创建单链表\n");
		exit(EXIT_FAILURE);
	}
	else//单链表非空
	{
		int len_L=ListLength(L);//得到单链表的长度
		printf("链表的长度:%d\n",len_L);
		if(pos==0)//如果是删除头结点
		{

		}
		else if(pos>len_L-1)//位置越界　len_L-1表示末尾节点
		{
			printf("delete单链表中没有该位置\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			p=List_Remove(L,pos-1);//节点指针移动到指定位置的前一个
				printf("delete 在单链表L中的第%d个节点找到数数据元素%d\n",pos-1,p->elem);
				SqlistPtr temp=NULL;
				temp=p->next;//定义一个临时的中间节点指向删除指定位置的节点
				p->next=temp->next;//将节点指针指向删除指定位置节点的下一个节点
				free(temp);//释放指定节点
				temp=NULL;
				s=success;
		}
	}//end p!=NULL

	return s;
}

SqlistPtr List_Reverse(SqlistPtr L)//将单链表倒置
{
	SqlistPtr pRev=NULL;//定义一个倒置指针,用于将节点倒置
	if(L==NULL)
	{
		printf("单链表为空,请先创建单链表\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		SqlistPtr pCur=L;//定义一个当前的节点指针,一直指向单链表的当前节点
		int i=0;
		while(pCur!=NULL)//到达尾部节点的时候跳出循环
		{
			SqlistPtr pTemp=pCur;	//1.新建一个临时的节点指针,指向当前节点，用于操作第n块节点
			pCur=pCur->next;        //2.将pcur指针移动到下一个节点，用于下一次循环处理，始终是第n+1块节点
			pTemp->next=pRev;	    //3.将当前指针断开,并将其的指针域指向第n块指针，让单链表倒置
			pRev=pTemp;				//将倒置节点移动至第n块指针，如此处理下一次循环时，连接的循序就是从后往前连
			i++;
			if(i==1)
				printf("pRev->elem=%d\n",pRev->elem);
			else
				printf("pRev->elem=%d  pRev->next->elem=%d\n",pRev->elem,pRev->next->elem);
		}
	}
	return pRev;
}

SqlistPtr List_Reverse_recursion(SqlistPtr Head)//递归实现单链表的倒置
{

	SqlistPtr newHead;
	if((Head==NULL)||(Head->next==NULL))//递归到末尾节点前一个节点
	{
		return Head;//返回节点指针　递归后指针从末尾节点的前一个节点开始逐一回溯
	}

	//递归　节点指针逐一往后移动一个单位节点　知道末尾节点之前的一个节点
	newHead=List_Reverse_recursion(Head->next);

	/*回溯：将当前表头结点链接到逆序链表的尾部*/
	Head->next->next=Head;//head->next->next始终指向null即单链表的尾部 将尾部与head连接　即尾部节点和尾部前一个节点实现连接

	Head->next=NULL;//连接后将尾部节点的前一个节点变成单链表的尾部

	return newHead;
}

//销毁单链表
SqlistPtr List_Destroy(SqlistPtr L)
{
	SqlistPtr pTemp;
	while(L!=NULL)
	{
		pTemp=L;
		L=L->next;
		List_Delete(pTemp,0);
		free(pTemp);
		pTemp=NULL;
	}

	return pTemp;
}

Status List_Delete_all(SqlistPtr L)//删除单链表中某个位置的节点
{
	Status s=range_error;
	SqlistPtr p;//声明一个新的节点指针,定位到指定的位置
	int pos=0;//删除的位置
	if(L==NULL)//单链表为空
	{
		printf("单链表为空请先创建单链表\n");
		exit(EXIT_FAILURE);
	}
	else//单链表非空
	{
		int len_L=ListLength(L);//得到单链表的长度
		printf("链表的长度:%d\n",len_L);
		if(len_L>1)//从第二个节点开始删除
		{
			for(pos=1;pos<len_L;pos++)
			{
				//printf("pos=%d\n",pos);
				p=List_Remove(L,pos-1);//节点指针移动到指定位置的前一个
				printf("delete 在单链表L中的第%d个节点找到数数据元素%d p->next->elem=%d\n",pos-1,p->elem,p->next->elem);
				SqlistPtr temp=NULL;
				temp=p->next;//定义一个临时的中间节点指向删除指定位置的节点
				p->next=temp->next;//将节点指针指向删除指定位置节点的下一个节点
				free(temp);//释放指定节点
				temp=NULL;
				s=success;
			}
			
			free(L);//释放指定节点
			L=NULL;
		}
		else//只要删除头结点
		{
			free(L);//释放指定节点
			L=NULL;
		}
		
	}//end p!=NULL

	return s;
}


int main(int argc,char* argv[])
{
	ElemType data1[10]={22,7,8,13,58,66,78,98,108,158};
	int len_data1=sizeof(data1)/sizeof(data1[1]);
	SqlistPtr list1=NULL;
	list1=HeadCreateList(list1,data1,len_data1);//头插法创建一个单链表
	DisplayList(list1);//显示list1的数据域

	int len_list1=ListLength(list1);
	printf("list1的数据元素长度:%d\n",len_list1);
	List_Delete_all(list1);
	printf("删除\n");
/*
	ElemType data2[10]={33,10,18,23,48,56,69,150,250,1500};
	int len_data2=sizeof(data2)/sizeof(data2[1]);
	SqlistPtr list2=NULL;
	list2=TailCreateList(list2,data2,len_data2);//头插法创建一个单链表
	DisplayList(list2);//显示list1的数据域
/*
	int len_list2=ListLength(list2);
	printf("list2的数据元素长度:%d\n",len_list2);

	/*---------------单链表的查找--------------------*/
/*	int pos_list1=10;
	ElemType elem_list1;
	Status s=List_Retrieve(list1,pos_list1,&elem_list1);
	if(s==success)
	{
		printf("在单链表list1中的第%d个节点找到数数据元素%d\n",pos_list1,elem_list1);
	}
	else if(s==range_error)
	{
		printf("在单链表list1中没有找到,位置%d已经越界了\n",pos_list1);
	}


	int pos_list2=11;
	ElemType elem_list2;
	s=List_Retrieve(list2,pos_list2,&elem_list2);
	if(s==success)
	{
		printf("在单链表list2中的第%d个节点找到数数据元素%d\n",pos_list2,elem_list2);
	}
	else if(s==range_error)
	{
		printf("在单链表list2中没有找到,位置%d已经越界了\n",pos_list2);
	}


	elem_list1=556;
	s=List_Locate(list1,elem_list1,&pos_list1);
	if(s==success)
	{
		printf("在单链表list1中找到了数据%d 它位于第%d个节点\n",elem_list1,pos_list1);
	}
	else if(s==range_error)
	{
		printf("在单链表list1中没有找到数据%d\n",elem_list1);
	}

	elem_list2=69;
	s=List_Locate(list2,elem_list2,&pos_list2);
	if(s==success)
	{
		printf("在单链表list2中找到了数据%d 它位于第%d个节点\n",elem_list2,pos_list2);
	}
	else if(s==range_error)
	{
		printf("在单链表list2中没有找到数据%d\n",elem_list2);
	}

	/*---------------前插法------------------------------------------*/
/*	int pos_insertbypre=2;//在头号节点之前插入数值666
	ElemType elem_insertbypre=666;
	s=List_InsertByPre(list1,pos_insertbypre,elem_insertbypre);
	DisplayList(list1);

	/*---------------后插法------------------------------------------*/
/*	int pos_insertbback=10;//在5号节点之后插入数值8888
	ElemType elem_insertbyback=8888;
	s=List_InsertByBack(list2,pos_insertbback,elem_insertbyback);
	DisplayList(list2);

	/*-------------------删除指定位置的节点----------------------------------------*/
/*	int pos_delete=5;
	s=List_Delete(list1,pos_delete);
	DisplayList(list1);

	/*---------------------使用普通循环的方法将单链表倒叙------------------------------------------*/
/*	list1=List_Reverse(list1);
	DisplayList_Head(list1);
	
	/*使用递归的方法将单链表倒叙*/
/*	list2=List_Reverse_recursion(list2);
	DisplayList_Head(list2);
	

	/*销毁单链表*/
/*	list1=List_Destroy(list1);
	list2=List_Destroy(list2);
	printf("--------------------销毁单链表之后打印----------------------------------\n");
	DisplayList(list1);
	DisplayList(list2);
*/

	return 0;
}
