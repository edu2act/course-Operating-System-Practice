#include "ProPCB.h"


Status GetProcess(LinkList Q,ElemType e)
{
	return ListInsert_L(Q, e);
}

Status OutProsess(LinkList Q,int i,ElemType *e)
{
	return ListDelete_L(Q ,i,e);
}

Status AllocateResource(LinkList PCBdata , int pos , int *Request)
{
	int i = 1;
	LNode *p = PCBdata->Next;
	
	while (p && i < pos)
	{
		p = p->Next;
		++i;
	}
	if(!p || i > pos)
		return ERROR;
	for (i = 0; i < RESOURCE_NUM; ++i)
	{
		p->data.resList.AllocationNum[i] += Request[i];
		p->data.resList.NeedNum[i] -= Request[i];
	}
	return OK;
}

void GetMatrixData(LinkList PCBdata,int *Max,int *Allocation,int *Need,int *Available)
{
	LNode *p;
	int i, j, c = RESOURCE_NUM;
	Available[0] = Available[1] = Available[2] = 0;
	for(p = PCBdata->Next, i = 0; p; p = p->Next, ++i)
	{
		for(j = 0; j < RESOURCE_NUM; ++j)
		{
			Max[i * c + j] = p->data.resList.MaxNum[j];
			Allocation[i * c + j] = p->data.resList.AllocationNum[j];
			Need[i * c + j] = p->data.resList.NeedNum[j];
		}
		Available[0] += Allocation[i * c + 0];
		Available[1] += Allocation[i * c + 1];
		Available[2] += Allocation[i * c + 2];
	}
	Available[0] =  MAX_RESOURCE_A_NUM - Available[0];
	Available[1] =  MAX_RESOURCE_B_NUM - Available[1];
	Available[2] =  MAX_RESOURCE_C_NUM - Available[2];
}

void PrintProQueue(LinkList L,int *available)
{
	int i = 0;
	L = L->Next;
	printf(" -------------------------------------------------------------\n");
	printf("|进程名 |     Max    |  Allocation |    Need    |  Available  |\n");
	printf("|       |  A   B   C |  A   B   C  | A   B   C  |  A   B   C  |\n");
	while(L)
	{
		printf("|  %s   |  %d   %d   %d |  %d   %d   %d  | %d   %d   %d  |  %d   %d   %d  |\n",
			L->data.Name, L->data.resList.MaxNum[0], L->data.resList.MaxNum[1], L->data.resList.MaxNum[2],
			L->data.resList.AllocationNum[0],L->data.resList.AllocationNum[1],L->data.resList.AllocationNum[2],
			L->data.resList.NeedNum[0],L->data.resList.NeedNum[1],L->data.resList.NeedNum[2],
			available[0], available[1], available[2]);
		L = L->Next;
	}
	printf(" -------------------------------------------------------------\n");

}

Status SecurityCheck(int *Allocation,int *Need, int *Available)
{
	int  i, j;
	int Work[RESOURCE_NUM] = {0};
	int finish[PCB_Num] = {false};

	for (i = 0; i < RESOURCE_NUM; ++i)
		Work[i] = Available[i];

	for (i = 0; i < PCB_Num; ++i)
	{
		j = 0;
		if(finish[i] == false)
			for (; j < RESOURCE_NUM; ++j)
			{
				if(Need[i * RESOURCE_NUM + j] > Work[j])
					break;
			}
		if(j >= 3)
		{
			for (j = 0; j < RESOURCE_NUM; ++j)
				Work[j] += Allocation[i * RESOURCE_NUM + j];
			finish[i] = true;
			i = -1;
		}
	}
	for (i = 0; i < PCB_Num; ++i)
	{
		if(!finish[i])
			return ERROR;
	}

	return OK;
}

Status BankerAlgorithm(int* Allocation, int *Request,int pos,int *Need, int *Available)
{
	int j;

	if(Request[0] > Need[pos * RESOURCE_NUM + 0] || Request[1] > Need[pos * RESOURCE_NUM + 1] || Request[2] > Need[pos * RESOURCE_NUM + 2])
	{
		printf("申请资源出错!\n");
		return 0;
	}
	if(Request[0] > Available[0] || Request[1] > Available[1] || Request[2] > Available[2])
	{
		printf("资源不足!\n");
		return 0;
	}
	//假定分配
	for (j = 0; j < RESOURCE_NUM; j++)
	{
		Need[pos * RESOURCE_NUM + j] -= Request[j];
		Allocation[pos * RESOURCE_NUM + j] += Request[j]; 
		Available[j] -= Request[j]; 
	}
	if(!SecurityCheck(Allocation ,Need , Available))
	{
		printf("不安全，不可分配！\n");
		for (j = 0; j < RESOURCE_NUM; j++)		//恢复资源
		{
			Need[pos * RESOURCE_NUM + j] += Request[j];
			Available[pos * RESOURCE_NUM + j] -= Request[j]; 
		}
		return ERROR;
	}

	return OK;
}

Status ReleaseAlgorithm(int *Allocation, int *Request, int pos)
{
	if(Request[0] > Allocation[pos *RESOURCE_NUM + 0] ||Request[1] > Allocation[pos *RESOURCE_NUM + 1] ||Request[2] > Allocation[pos *RESOURCE_NUM + 2] )
	{
		printf("申请释放资源数有误!\n");
		return ERROR;
	}

	return OK;
}

Status ReleaseResource(LinkList PCBdata ,int pos, int *Request)
{
	 int i = 1;
	 LNode * p = PCBdata->Next;
	 while (p && i < pos)
	 {
		 ++i;
		 p = p->Next;
	 }
	 if(!p || i > pos)
	 {
		 return ERROR;
	 }
	 for (i = 0; i < RESOURCE_NUM; i++)
	 {
		 p->data.resList.AllocationNum[i] -= Request[i];
		 p->data.resList.NeedNum[i] += Request[i];
	 }

	return OK;
}