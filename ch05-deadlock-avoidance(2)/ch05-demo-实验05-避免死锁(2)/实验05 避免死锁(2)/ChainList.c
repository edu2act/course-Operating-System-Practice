#include "ChainList.h"

Status Init(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	strcpy((*L)->data.Name, "");
	(*L)->Next = NULL;
	return OK;
}

void Assignment(ElemType *e1, ElemType e2)
{
	int i = 0;
	strcpy(e1->Name,e2.Name);
	for(i = 0; i < RESOURCE_NUM; ++i)
	{
		e1->resList.AllocationNum[i] = e2.resList.AllocationNum[i];
		e1->resList.MaxNum[i] = e2.resList.MaxNum[i];
		e1->resList.NeedNum[i] = e2.resList.NeedNum[i];
	}
}



Status ListInsert_L(LinkList L,ElemType e)	//这样修改应该不对 p = *L出错
{
	LinkList p = L, s;
	while (p->Next)	
		p = p->Next;
	s = (LinkList)malloc(sizeof(LNode));
	Assignment(&s->data, e);
	s->Next = p->Next;
	p->Next = s;
	return OK;
}
//链表中头部删除
Status ListDelete_L(LinkList L,int i,ElemType *e)
{
	LinkList p = L, q;
	int j = 0;
	while (p->Next && j < i-1)
	{
		p = p->Next; ++j;
	}
	if(!p->Next || j > i - 1)
		return ERROR;
	q = p->Next;
	p->Next = q->Next;
	Assignment(e, q->data);
	free(q);
	return OK;
}

