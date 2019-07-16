#include "ChainList.h"
extern int CPUUsedTime;
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


Status GetElemt_L(LinkList L,int i,ElemType *e)
	//当我们进行的操作要进行，写操作时，传递引用或地址
{
	LinkList p = L->Next;	//指向第j个结点
	int j = 1;				//从第一个开始往后找
	while ( p && j < i )	//p不为空且j < i
	{
		p = p->Next;
		++j;
	}						//p为空，说明链表循环结束，也没有到第i个结点   j==i
	if (!p || j > i)		//因为此处对i   没有做判断   如果 i==0  或 负数  条件成立
							//对于 i == j == 1 的情况则不用循环正好  返回
	{
		return ERROR;
	}
	*e = p->data;			//通过寻址改变了 该地址内存中元素的值
	return OK;
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

