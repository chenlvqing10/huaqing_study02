#include "seque_linear_list.h"

Status InitList(SqListPtr L)//构造一个空的线性表
{
	Status s = success;
	L->list_size = LIST_INIT_SIZE;//初始分配的内存空间
	L->length = 0;//线性表长度0
	L->elem = (ElemType*)malloc(sizeof(ElemType)*(L->list_size));//为线性表的数据元素分配内存空间

	if(L->elem ==NULL)//线性表中的数据元素指针指向空
		s = fatal;

	return s;
}

Status DestroyList(SqListPtr L)//销毁线性表
{
	Status s  = success;
	if(L->elem==NULL)
		s=fatal;
	else
	{
		free(L->elem);//释放内存空间
		L->elem=NULL;
		L->length=0;
	}

	return s;
}

Status ClearList(SqListPtr L)//清空线性表
{
	Status s  = success;
	if(L->elem==NULL)
		s=fatal;
	for(int i=0;i<L->length;i++)
	{
		L->elem=NULL;
		L->elem++;
	}
	L->length=0;

	return s;
}

Status ListEmpty(SqListPtr L)//判定现行表是否为空
{
	if(L->length==0)
		return success;
	else 
		return fail;
}

int ListLength(SqListPtr L)//返回线性表的长度
{
	return L->length;
}

Status List_Retrival(SqListPtr L,int pos,ElemType *elem)//按位置查找　　在线性表L中查找位置pod的元素数据 放到elem中
{
	Status s=range_error;

	if(L)//线性表非空
	{
		if(((pos-1)>=0)&&((pos-1)<=L->length))//位置合法　在顺序表的数据元素范围内
		{
			*elem=L->elem[pos-1];//将该位置的数值放到elem中
			s=success;
		}
	}
	else//线性表为空
		s=fatal;

	return s;
}

int List_Locate(SqListPtr L,ElemType elem)//按数值查找　　　在线性表L中查找数值和elem相同的元素的位置　　放到pos中
{
	int  pos=0;

	if(L)//线性表非空
	{
		for(int i=0;i<L->length;i++)//遍历线性表的所有数据元素
		{
			if(L->elem[i] == elem)//如果线性表中的元素和查找的数据元素相等
			{
				pos=i+1;//记录当前的位置
				break;//跳出循环
			}
		}
	}

	return pos;
}

ElemType* PriorElem(SqListPtr L,ElemType cur_e,ElemType *pre_e)//用pre_e返回线性表中cur_e的前驱
{
	//定位数据元素cur_e的位置
	int i=List_Locate(L,cur_e);

	if(i==0)//说明顺序表中不存在该数据元素
	{
		printf("该顺序表中不存在该数据元素\n");
		pre_e=NULL;
	}
	else if(i==1)
	{
		printf("首元素,无前驱\n");
		pre_e=NULL;
	}
	else
	{
		pre_e=&(L->elem[i-2]);//将数据元素前驱的数值赋值给pre_e
	}

	return pre_e; 
}

ElemType* NextElem(SqListPtr L,ElemType cur_e,ElemType *next_e)//用next_e返回线性表中cur_e的后继
{
	//定位数据元素cur_e的位置
	int i=List_Locate(L,cur_e);

	if(i==0)//说明顺序表中不存在该数据元素
	{
		printf("该顺序表中不存在该数据元素\n");
		next_e=NULL;
	}
	else if(i==L->length)
	{
		printf("末尾元素,无后继\n");
		next_e=NULL;
	}
	else
	{
		next_e=&(L->elem[i]);//将数据元素前驱的数值赋值给next_e
	}

	return next_e;

}

Status List_Insert(SqListPtr L,int pos,ElemType elem)//在线性表L中的pos位置之前插入元素数据elem
{
	Status s=range_error;
	if(((pos-1)>=0) &&((pos-1)<=L->length))//位置检查
	{
		if(L && L->length<L->list_size)//表非满　　存储空间没有满
		{
			//从最后一个位置开始往后移一位知道要插入的pos-1的位置,将pos的位置空闲出来
			for(int i=L->length-1;i>=pos-1;i--)
			{
				L->elem[i+1]=L->elem[i];//移动数据元素
			}

			//移动之后插入新的数据
			L->elem[pos-1]=elem;
			L->length++;//数据元素+1
			s=success;
		}
	}
	else
		s=fail;

	return s;
}

Status List_Replace(SqListPtr L,ElemType elem,ElemType newelem)//将在线性表L中的pos位置的数据元素替换成newelem
{
	Status s=range_error;
	int pos=List_Locate(L,elem);//查找位置
	
	if(pos==0)//说明顺序表中不存在该数据元素
	{
		printf("该顺序表中不存在该数据元素%d\n",elem);
	}
	else
	{
		L->elem[pos-1]=newelem;//替换相应位置的数据元素
		s=success;
	}
	
	return s;
}

Status List_Delete(SqListPtr L,int pos)//在线性表L中删除pos位置的元素数据
{
	Status s=range_error;
	if(((pos-1)>=0) &&((pos-1)<=L->length))//位置检查
	{
		if(L && L->length>0)//顺序表中有数据
		{
			//遍历 从pos+1位置开始向前移动一个单位数据,到最后一个数据元素为止
			for(int i=pos;i<L->length;i++)
			{
				L->elem[i-1]=L->elem[i];//移动数据元素  将pos+1的数据元素赋值给pos　即向前移动一个单位
			}

			//移动之后将顺序表中的长度-1
			L->length--;//数据元素-1
			s=success;
		}
	}
	else
		s=fail;

	return s;
}

Status List_Union(SqListPtr La,SqListPtr Lb)//合并两个顺序结构的线性表
{
	ElemType elem;
	Status status;
	int len_Lb=ListLength(Lb);//得到Lb的数据元素个数
	int pos=0;

	for(int i=1;i<=len_Lb;i++)//遍历顺序线性表Lb中的数据元素
	{
		status=List_Retrival(Lb,i,&elem);//按位置取出顺序线性表Lb中数据元素数值放到elem中
		//printf("i=%d  elem=%d\n",i,elem);
		
		if(status==success)//获取数据元素成功
		{
			pos=List_Locate(La,elem);//找到顺序线性表La中数据元素数值和顺序线性表Lb中数据元素数值相同的位置
			
			if(pos==0)//说明该数据在La中是不存在的
			{
				status=List_Insert(La,1,elem);//将该数据插入到La的第一个位置　　效率快
				if(status!=success)//如果插入失败则退出
					break;
			}
			else if(pos>0)//说明该数据在La中是存在的
			{
				status=List_Insert(La,pos,elem);//在当前位置插入相同的数据元素
				if(status!=success)//如果插入失败则退出
					break;
			}
		}
		else
		{
			printf("顺序线性表Lb中没有数据元素\n");
			status=fatal;//致命错误
			exit(EXIT_FAILURE);
		}
	}
	
	return status;
}

void DisplayList(SqListPtr L)
{
	for (int i=0;i<L->length;i++) 
	{
		printf("L->elem[%d]=%d\n",i,L->elem[i]);
	}
	printf("\n");
}


int main(int argc,char* argv[])
{
/*
	SqList list1,list2;//结构体
	Status s=InitList(&list1);//创建一个新的顺序表list1
	if(s==success)
	{
		printf("创建一个新的顺序表list1成功\n");
	}
	else
	{
		printf("list1产生了致命的错误\n");
	}

	Status s1=InitList(&list2);//创建一个新的顺序表list2
	if(s1==success)
	{
		printf("创建一个新的顺序表list2成功\n");
	}
	else
	{
		printf("list2产生了致命的错误\n");
	}


	//----判定线性表是否为空
	Status empty_status=ListEmpty(&list1);
	if(empty_status==success)
		printf("线性表list1是空的\n");
	else
		printf("线性表list1不为空\n");

	//给顺序表赋值
	for(int i=0;i<LIST_INCREAMENT;i++)//赋值20个数据元素
	{
		list1.elem[i]=i+1;
		list1.length++;
	}

	//显示数据
	printf("---------------------原来的顺序表list1---------------------------------\n");
	DisplayList(&list1);

	//线性表的长度
	int len_list=ListLength(&list1);
	printf("线性表list1的长度是%d\n",len_list);


/*-------------------------------------------------------------------------------------------------------------------------*/
	/*给线性表list2赋值*/
/*	for(int i=0;i<20;i++)//赋值20个数据元素
	{
		list2.elem[i]=10*i+5;
		list2.length++;
	}

	//显示数据
	printf("---------------------原来的顺序表list2---------------------------------\n");
	DisplayList(&list2);
/*
	//----按位置查找顺序表中的数据元素
	int pos=20;
	ElemType elem1;
	Status pos_status=List_Retrival(&list1,pos,&elem1);
	if(pos_status==success)
	{
		printf("顺序线性表中的数据元素是%d\n",elem1);
	}
	else if(pos_status==range_error)
	{
		printf("顺序线性表表中没有该数据元素,列表不够长\n");
	}
	else
	{
		printf("顺序线性表为空\n");
	}

	//----按数值在顺序表中查找与该数值相等的第一个位置
	ElemType elem2=25;
	int pos2=List_Locate(&list1,elem2);
	if(pos2==0)
		printf("顺序表中没有%d这个数据元素\n",elem2);
	else
		printf("数据元素%d在顺序表中的位置是第%d个元素\n",elem2,pos2);

	ElemType elem3=100;
	int pos3=List_Locate(&list1,elem3);
	if(pos3==0)
		printf("顺序表中没有%d这个数据元素\n",elem3);
	else
		printf("数据元素%d在顺序表中的位置是第%d个元素\n",elem3,pos3);

	//查找数据元素cur_e的前驱pre_e和后继next_e
	ElemType cure_e=25;
	ElemType* pre_e=NULL;
	ElemType* next_e=NULL;
	pre_e=PriorElem(&list1,cure_e,pre_e);
	next_e=NextElem(&list1,cure_e,next_e);
	if((pre_e==NULL)||(next_e==NULL))
	{
		if(pre_e==NULL)
		{
			printf("数据元素%d没有前驱  ",cure_e);
		}
		else if(pre_e!=NULL)
		{

			printf("数据元素%d有前驱%d ",cure_e,*pre_e);
		}

		if(next_e==NULL)
		{
			printf("数据元素%d没有后驱\n",cure_e);
		}
		else if(next_e!=NULL)
		{
			printf("数据元素%d有后驱%d\n",cure_e,*next_e);
		}
	}
	else if((pre_e!=NULL)&&(next_e!=NULL))
	{

		printf("数据元素%d的前驱是%d,后驱是%d\n",cure_e,*pre_e,*next_e);
	}

	//在线性表L中的pos位置之前插入元素数据elem
	int pos_insert=20;//插入的位置
	ElemType elem_insert=98;//插入的数值

	Status insert_status=List_Insert(&list1,pos_insert,elem_insert);
	if(insert_status==success)
	{
		printf("在顺序表%d的位置插入数据%d成功\n",pos_insert,elem_insert);
	}
	else
	{
		printf("顺序线性表中找不到该位置\n");
	}

	//显示数据
	printf("---------------------插入数据后的顺序表---------------------------------\n");
	DisplayList(&list1);

	//删除在线性表L中的pos位置的数据
	
	int pos_delete=25;//删除的位置

	Status delete_status=List_Delete(&list1,pos_delete);
	if(delete_status==success)
	{
		printf("在顺序表%d的位置删除数据成功\n",pos_delete);
	}
	else
	{
		printf("顺序线性表中找不到该位置\n");
	}

	//显示数据
	printf("---------------------删除数据后的顺序表---------------------------------\n");
	DisplayList(&list1);

	/*将elem的数据元素替换成newelem*/

	/*
	ElemType oldelem=26;
	ElemType newelem=999;

	Status replace_status=List_Replace(&list1,oldelem,newelem);
	if(replace_status==success)
	{
		printf("把顺序表的数据%d替换成了%d\n",oldelem,newelem);
	}
	else
	{
		printf("顺序线性表中找不到该位置\n");
	}

	//显示数据
	printf("---------------------替换数据后的顺序表---------------------------------\n");
	DisplayList(&list1);
	
*/
	/*合并两个顺序线性表*/
/*	Status union_status=List_Union(&list1,&list2);
	if(union_status==success)
	{
		printf("合并顺序结构的线性表成功\n");
		int len_all=ListLength(&list1);
		printf("合并之后的数据元素个数是%d\n",len_all);
	}
	else
	{
		printf("合并顺序结构的线性表失败\n");
	}
	//显示数据
	printf("---------------------合并线性表后的顺序表---------------------------------\n");
	DisplayList(&list1);

	/*合并两个有序表*/
	SqList lista,listb;//创建两个有序表
	printf("lista=%p",lista);
	Status status=InitList(&lista);
	printf("lista=%p",lista);
	if(status==success)
	{
		printf("创建有序表lista成功\n");
	}
	else
	{
		printf("创建有序表lista失败");
	}

	status=InitList(&listb);
	if(status==success)
	{
		printf("创建有序表listb成功\n");
	}
	else
	{
		printf("创建有序表listb失败");
	}

	//给两个有序表赋初值形成有数值的有序表
	for(int i=0;i<4;i++)
	{
		lista.elem[i]=5*i+2*i+1;
		lista.length++;
	}

	for(int i=0;i<4;i++)
	{
		listb.elem[i]=4*i*i+2;
		listb.length++;
	}

	printf("-------------------合并之前lista的数据元素-------------------------------\n");
	DisplayList(&lista);

	printf("-------------------合并之前listb的数据元素-------------------------------\n");
	DisplayList(&listb);

	
	/*合并两个有序表放到listc中*/
	SqList listc;
	status=InitList(&listc);
	if(status==success)
	{
		printf("创建有序表listb成功\n");
	}
	else
	{
		printf("创建有序表listb失败");
	}
	
	ElemType elem_a,elem_b;//将a表中的数据放到elem_a   将b表中的数据放到elem_b
	int i=1,j=1,k=1;//i指向lista   j指向listb      k指向listc
	int len_lista=ListLength(&lista);//lista的线性表长度
	int len_listb=ListLength(&listb);//listb的线性表长度
	printf("len_lista=%d   len_listb=%d\n",len_lista,len_listb);

	while( (i<=len_lista) && (j<=len_listb) )//两个线性表中其中一个表的数据没有处理完
	{
		List_Retrival(&lista,i,&elem_a);
		List_Retrival(&listb,j,&elem_b);

		if(elem_a<elem_b)//如果表a中的数据<表b中的数据
		{
			status=List_Insert(&listc,k,elem_a);//将小的那个数值插入表c中
			if(status==success)
			{
				printf("插入成功\n");
			}
			else
			{
				printf("插入失败\n");
			}
			i=i+1;//指向表a中的下一个元素
		}
		else
		{
            status=List_Insert(&listc,k,elem_b);//将小的那个数值插入表c中
            if(status==success)
            {
                printf("插入成功1\n");
            }
            else
            {
                printf("插入失败1\n");
            }
            j=j+1;//指向表b中的下一个元素
		}
		k=k+1;//指向表c中的下一个空间
	}//end while

	//如果表a未处理完
	while(i<=len_lista)
	{
		//将剩下的数据插入到表c中
		List_Retrival(&lista,i,&elem_a);//得到表a中的数据
        status=List_Insert(&listc,k,elem_a);//将数据插入在表c中
        if(status==success)
        {
			printf("插入a中剩下的数据成功\n");
        }
        else
        {
			printf("插入a中剩下的数据失败\n");
        }
		i=i+1;
		k=k+1;
	}

	//如果表b未处理完
	while(j<=len_listb)
	{
		//将剩下的数据插入到表c中
		List_Retrival(&listb,j,&elem_b);//得到表b中的数据
        status=List_Insert(&listc,k,elem_b);//将数据插入在表c中
        if(status==success)
        {
			printf("插入b中剩下的数据成功\n");
        }
        else
        {
			printf("插入b中剩下的数据失败\n");
        }
		j=j+1;
		k=k+1;
	}

	printf("-------------------合并之后listc的数据元素-------------------------------\n");
	DisplayList(&listc);

	return 0;
}



