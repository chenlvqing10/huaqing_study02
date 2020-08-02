#ifndef __BITREE__
#define __BITREE__

//---------------------二叉树-------------------------------------

/*头文件*/
#include <stdio.h>
#include <stdlib.h>

/*宏定义*/
#define TElemType char

/*结构体，变量*/
typedef struct BiTreeNode{
    TElemType data;//数据域
    struct BiTreeNode *lchild,*rchild;//左右孩子指针
}BiTreeNode,*Ptr;
typedef Ptr BiTreeNodePtr;//二叉树结构体指针

/*函数*/
void BiTreeInit(BiTreeNodePtr* BiTreeNode);//初始化二叉树节点
void BiTreeCreate(BiTreeNodePtr* BiTreeNode,TElemType data);//创建二叉树


#endif

