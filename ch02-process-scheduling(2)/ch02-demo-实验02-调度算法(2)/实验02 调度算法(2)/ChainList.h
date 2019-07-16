#ifndef _ChainList_h_
#define _ChainList_h_

#include "Data.h"

Status Init(LinkList *L);

void Assignment(ElemType *e1, ElemType e2);

//链表中按照优先级：从大到小排序插入
Status ListInsert_L(LinkList L,ElemType e);
//链表中头部删除
Status ListDelete_L(LinkList L,ElemType *e);



#endif