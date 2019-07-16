#include "ChainList.h"

extern int CPUUsedTime;

//功能：链表初始化
Status Init(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->data.NeedRunningTime = -1;
    (*L)->Next = NULL;
    return OK;
}

//功能：赋值运算，将e2赋值给e1
void Assignment(ElemType *e1, ElemType e2)
{
    e1->ArrivalTime = e2.ArrivalTime;
    strcpy(e1->Name,e2.Name);
    e1->Priority = e2.Priority;
    e1->ProcessState = e2.ProcessState;
    e1->FinishTime = e2.FinishTime;
    e1->StartTime = e2.StartTime;
    e1->NeedRunningTime = e2.NeedRunningTime;
    e1->TimeUsedCPU = e2.TimeUsedCPU;
}



//链表中按照优先级：从大到小排序插入
Status ListInsert_L(LinkList L,ElemType e)	//这样修改应该不对 p = *L出错
{
    LinkList p = L->Next, pre = L, s;
    while (p && e.Priority <= p->data.Priority)	
    {
        pre = p;
        p = p->Next;
    }
    s = (LinkList)malloc(sizeof(LNode));
    Assignment(&s->data, e);
    s->Next = pre->Next;
    pre->Next = s;
    return OK;
}
//链表中头部删除
Status ListDelete_L(LinkList L,ElemType *e)
{
    LinkList p = L, q;
    q = p->Next;
    if(!q)
        return ERROR;
    p->Next = q->Next;
    Assignment(e, q->data);
    free(q);
    return OK;
}


