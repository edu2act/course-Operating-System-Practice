#include "List.h"


//*******           链表            *******//
Status InitLinkList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	strcpy((*L)->data.Name, "");
	(*L)->Next = NULL;
	return OK;
}

void PCBAssign(PCBType *e1, PCBType e2)
{
	strcpy(e1->Name,e2.Name);
	e1->MemorySize = e2.MemorySize;
	e1->pPagetable = e2.pPagetable;
}

Status GetElemt_L(LinkList L,int i,PCBType *e)
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
//链表中按照优先级：从大到小排序插入
Status ListInsert_L(LinkList L,PCBType e)	//这样修改应该不对 p = *L出错
{
	LinkList p = L, s;
	while (p->Next)	
		p = p->Next;
	s = (LinkList)malloc(sizeof(LNode));
	PCBAssign(&s->data, e);
	s->Next = p->Next;
	p->Next = s;
	return OK;
}

Status ListDelete_L(LinkList L,int i,PCBType *e)
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
	PCBAssign(e, q->data);
	free(q);
	return OK;
}

//******         分区使用说明表           ******//
void PartiAssign_f(PartiType *e1, PartiType e2)
{
	e1->PartStartAddr = e2.PartStartAddr;
	strcpy(e1->Name, e2.Name);
}

Status InitList_f(SqList_f *L)
{
	//构造一个空的线性表L
	L->elem = (PartiType *)malloc((LIST_INIT_SIZE)*sizeof(PartiType));
	if(!L->elem) return ERROR;        //存储分配失败
	L->length = 0;                 //空表长度为0
	L->listsize = LIST_INIT_SIZE;  //初始存储的容量
	return OK;
}

//在顺序线性表L中第i个位置之前插入新的元素e
Status ListInsert_f(SqList_f *L,int i,PartiType e)
{
	//在顺序线性表L中第i个位置之前插入新的元素e
	//i的合法值为1 <= i <= ListLength_Sq(L)+1
	PartiType *q, *p, *newbase;

	if(i < 1 || i > L->length + 1 ) return ERROR;     //i值不合法
	if(L->length >= L->listsize){               //当前存储空间已满，增加分配
		newbase = (PartiType *)realloc(L->elem
			,(L->listsize + LISTINCREMENT)*sizeof(PartiType));
		if(!newbase) return ERROR;				//存储分配失败
		L->elem = newbase;						//新基址
		L->listsize += LISTINCREMENT;			//增加存储容量
	} 
	q = &(L->elem[i - 1]);			         	//q为插入位置
	for(p = &(L->elem[L->length-1]);p >= q; --p)
		PartiAssign_f((p+1),*p); 					//插入位置及之后的元素右移
	PartiAssign_f(q ,e);							//插入e
	L->length++;
	return OK;
}

//在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_f(SqList_f *L,int i,PartiType *e)
{
	//在顺序线性表L中删除第i个元素，并用e返回其值
	//i的合法值为1 <= i <= ListLength_Sq(L)
	PartiType *p,*q;
	if((i < 1) || (i > L->length))	
		return ERROR;							 //i值不合法
	p = &(L->elem[i-1]);						 //p为被删除元素的位置
	PartiAssign_f(e, *p);							 //将被删除元素的值赋给e （待定）
	q = L->elem + L->length-1;					 //移动到表尾元素的位置
	for (++p;p<=q;++p)
		PartiAssign_f((p-1), *p);					 //被删除元素之后的元素左移
	L->length--;
	return OK;
}


//******         页表           ******//

void PartiAssign_y(BlockNumType *e1, BlockNumType e2)
{
	(*e1).BlockNum = e2.BlockNum;
    (*e1).DistbutSt = e2.DistbutSt;
}

Status InitList_y(SqList_y **L)
{
	//构造一个空的线性表L
    (*L) = (PageTable *)malloc(sizeof(PageTable));//不可缺少
	(*L)->elem = (BlockNumType *)malloc((LIST_INIT_SIZE)*sizeof(BlockNumType));
	if(!(*L)->elem) return ERROR;        //存储分配失败
	(*L)->length = 0;                 //空表长度为0
	(*L)->listsize = LIST_INIT_SIZE;  //初始存储的容量
	return OK;
}

//在顺序线性表L中第i个位置之前插入新的元素e
Status ListInsert_y(SqList_y *L,int i,BlockNumType e)
{
	//在顺序线性表L中第i个位置之前插入新的元素e
	//i的合法值为1 <= i <= ListLength_Sq(L)+1
	BlockNumType *q, *p, *newbase;

	if(i < 1 || i > L->length + 1 ) return ERROR;     //i值不合法
	if(L->length >= L->listsize){               //当前存储空间已满，增加分配
		newbase = (BlockNumType *)realloc(L->elem
			,(L->listsize + LISTINCREMENT)*sizeof(BlockNumType));
		if(!newbase) return ERROR;				//存储分配失败
		L->elem = newbase;						//新基址
		L->listsize += LISTINCREMENT;			//增加存储容量
	} 
	q = &(L->elem[i - 1]);			         	//q为插入位置
	for(p = &(L->elem[L->length-1]);p >= q; --p)
		PartiAssign_y((p+1),*p); 					//插入位置及之后的元素右移
	PartiAssign_y(q ,e);							//插入e
	L->length++;
	return OK;
}

//在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_y(SqList_y *L,int i,BlockNumType *e)
{
	//在顺序线性表L中删除第i个元素，并用e返回其值
	//i的合法值为1 <= i <= ListLength_Sq(L)
	BlockNumType *p,*q;
	if((i < 1) || (i > L->length))	
		return ERROR;							 //i值不合法
	p = &(L->elem[i-1]);						 //p为被删除元素的位置
	PartiAssign_y(e, *p);							 //将被删除元素的值赋给e （待定）
	q = L->elem + L->length-1;					 //移动到表尾元素的位置
	for (++p;p<=q;++p)
		PartiAssign_y((p-1), *p);				 //被删除元素之后的元素左移
	L->length--;
	return OK;
}