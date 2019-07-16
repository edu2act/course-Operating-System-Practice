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
	//�����ǽ��еĲ���Ҫ���У�д����ʱ���������û��ַ
{
	LinkList p = L->Next;	//ָ���j�����
	int j = 1;				//�ӵ�һ����ʼ������
	while ( p && j < i )	//p��Ϊ����j < i
	{
		p = p->Next;
		++j;
	}						//pΪ�գ�˵������ѭ��������Ҳû�е���i�����   j==i
	if (!p || j > i)		//��Ϊ�˴���i   û�����ж�   ��� i==0  �� ����  ��������
							//���� i == j == 1 ���������ѭ������  ����
	{
		return ERROR;
	}
	*e = p->data;			//ͨ��Ѱַ�ı��� �õ�ַ�ڴ���Ԫ�ص�ֵ
	return OK;
}

Status ListInsert_L(LinkList L,ElemType e)	//�����޸�Ӧ�ò��� p = *L����
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
//������ͷ��ɾ��
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

