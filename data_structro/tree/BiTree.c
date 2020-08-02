#include "BiTree.h"

/*初始化二叉树的每个节点　新建一个二叉树节点*/
void BiTreeInit(BiTreeNodePtr* BiTreeNode)
{
	*BiTreeNode = (BiTreeNodePtr)malloc(sizeof(BiTreeNode));//为节点分配内存单元
	(*BiTreeNode)->lchild=(*BiTreeNode)->rchild=NULL;
	(*BiTreeNode)->data=0;
}

void BiTreeCreate(BiTreeNodePtr* BiTreeNode,TElemType data)//创建二叉树
{
	int i;
	BiTreeNodePtr tempnode=*BiTreeNode;
	while(tempnode)
	{
		if(!tempnode->data)//树节点的数据为空
		{
			tempnode->data=data;
			breakl
		}
		else if(data <= tempnode->data)
		{
			if(!tempnode->lchild)//左孩子为空
			{
				BiTreeInit(&tempnode->lchild);//初始化左孩子
			}
			else//左孩子非空
			{
				tempnode = tempnode->lchild;//指向左孩子节点
				continue;//继续下一次循环
			}
		}
		else if(data > tempnode->data)
		{
            if(!tempnode->rchild)//右孩子为空
            {
                BiTreeInit(&tempnode->rchild);//初始化右孩子
            }
            else//左孩子非空
            {
                tempnode = tempnode->rchild;//指向右孩子节点
                continue;//继续下一次循环
            }

		}
	}
}


int main()
{
	BiTreeNodePtr root;
	char data[8]={'e','f','h','g','a','c','b','d'};
	BiTreeInit(&root);
	for(int i=0;i<8;i++)
	{
		BiTreeCreate(&root,data[i]);
	}
	return 0;
}
