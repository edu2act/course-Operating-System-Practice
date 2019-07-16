#include "List.h"



//*******           根目录链表            *******//
Status InitLinkList_R(LinkList_R *L)
{
	*L = (LinkList_R)malloc(sizeof(RNode));
	strcpy((*L)->data.UserName, "");
	(*L)->Next = NULL;
	return OK;
}

void RElemAssign_R(ElemType_R *e1, ElemType_R e2)
{
	strcpy(e1->UserName,e2.UserName);
	strcpy(e1->UserPWD,e2.UserPWD);
	e1->UserFileList = e2.UserFileList;
}

Status GetElemt_R(LinkList_R L,int i,ElemType_R *e)
{
	LinkList_R p = L->Next;	//指向第j个结点
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
	RElemAssign_R(e , p->data);	//通过寻址改变了 该地址内存中元素的值
		
	return OK;
}

Status ListInsert_R(LinkList_R L,ElemType_R e)	 
{
	LinkList_R p = L, s;
	while (p->Next)	
		p = p->Next;
	s = (LinkList_R)malloc(sizeof(RNode));
	RElemAssign_R(&(s->data), e);
	s->Next = p->Next;
	p->Next = s;
	return OK;
}
//链表中头部删除
Status ListDelete_R(LinkList_R L,int i,ElemType_R *e)
{
	LinkList_R p = L, q;
	int j = 0;
	while (p->Next && j < i-1)
	{
		p = p->Next; ++j;
	}
	if(!p->Next || j > i - 1)
		return ERROR;
	q = p->Next;
	p->Next = q->Next;
	RElemAssign_R(e, q->data);
	free(q);
	return OK;
}

//******         用户目录链表           ******//

Status InitLinkList_U(LinkList_U *L)
{
	*L = (LinkList_U)malloc(sizeof(UNode));
	strcpy((*L)->data.FileName, "");
	(*L)->data.FileAddress = NULL;
	(*L)->Next = NULL;
	return OK;
}

void RElemAssign_U(ElemType_U *e1, ElemType_U e2)
{
	strcpy(e1->FileName,e2.FileName);
	e1->FileAddress = e2.FileAddress;
}

Status GetElemt_U(LinkList_U L,int i,ElemType_U *e)
{
	LinkList_U p = L->Next;	//指向第j个结点
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
	RElemAssign_U(e , p->data);	//通过寻址改变了 该地址内存中元素的值
		
	return OK;
}
//链表中按照优先级：从大到小排序插入
Status ListInsert_U(LinkList_U L,ElemType_U e)	//这样修改应该不对 p = *L出错
{
	LinkList_U p = L, s;
	while (p->Next)	
		p = p->Next;
	s = (LinkList_U)malloc(sizeof(UNode));
	RElemAssign_U(&(s->data), e);
	s->Next = p->Next;
	p->Next = s;
	return OK;
}
//链表中头部删除
Status ListDelete_U(LinkList_U L,int i,ElemType_U *e)
{
	LinkList_U p = L, q;
	int j = 0;
	while (p->Next && j < i-1)
	{
		p = p->Next; ++j;
	}
	if(!p->Next || j > i - 1)
		return ERROR;
	q = p->Next;
	p->Next = q->Next;
	RElemAssign_U(e, q->data);
	free(q);
	return OK;
}

