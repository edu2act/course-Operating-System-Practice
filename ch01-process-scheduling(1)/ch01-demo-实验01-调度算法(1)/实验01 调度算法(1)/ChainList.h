#ifndef _ChainList_h_
#define _ChainList_h_

#include "Data.h"

//功能：链表初始化
Status Init(LinkList *L);

//功能：赋值运算，将e2赋值给e1
void Assignment(ElemType *e1, ElemType e2);

//功能：获取第i个结点元素
Status GetElemt_L(LinkList L,int i,ElemType *e);

//功能：链表根据优先级插入元素
Status ListInsert_L(LinkList L,ElemType e);

//功能：链表删除头结点
Status ListDelete_L(LinkList L,ElemType *e);


#endif