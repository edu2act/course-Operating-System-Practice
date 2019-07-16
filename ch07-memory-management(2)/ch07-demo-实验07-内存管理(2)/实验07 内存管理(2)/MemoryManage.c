#include "MemoryManage.h"
extern int CF_i;

//*****         PCB链表操作        *****//
Status InsertProcess(LinkList Q,PCBType e)
{
	return ListInsert_L(Q, e);
}

Status DeleteProsess(LinkList Q,int i,PCBType *e)
{
	return ListDelete_L(Q ,i,e);
}

//*****         分区表操作        *****//
Status InsertTable(SqList *L, int i, PartiType e) 
{
	return ListInsert_Sq(L,i, e);
}

Status DeleteTable(SqList *L, int i, PartiType *e)
{
	return ListDelete_Sq(L, i, e);
}

//返回第几个内存块，从1开始，若返回0，则代表错误
int SelectPart(PCB* pPCB, SqList *pPartTable,AllocatStrategy AS)
{
	int i;
	int BestArr[20] = {0}, k = 0, min = 500, min_i = -1;

	if(AS == FirstPriority)
	{
		for (i = 0; i < pPartTable->length; ++i)
			if(!strcmp(pPartTable->elem[i].Name, "") && pPartTable->elem[i].PartitionSize >= pPCB->MemorySize)
				return i + 1;
	}else if(AS == BestAdapt)
	{
		////////////     以下补充   /////////////
		for (i = 0; i < pPartTable->length; ++i)
		{
			if(!strcmp(pPartTable->elem[i].Name, "") 
				&& pPartTable->elem[i].PartitionSize >= pPCB->MemorySize
				&& pPartTable->elem[i].PartitionSize < min)
			{
				min = pPartTable->elem[i].PartitionSize;
				min_i = i;
			}
		}
		return min_i + 1;
	}else if(AS == CycleFirst)
	{
		////////////     以下补充   /////////////
		if(CF_i > pPartTable->length || CF_i < 1)
			CF_i = 1;
		for (i = CF_i - 1, k = 0; k < pPartTable->length; ++k, i = (i + 1) % pPartTable->length)
		{
			if(!strcmp(pPartTable->elem[i].Name, "")
				&& pPartTable->elem[i].PartitionSize >= pPCB->MemorySize)
			{
				CF_i = i + 1;
				return i + 1;
			}
		}
	}else
	{
		printf("算法选择有误！\n");
	}
	return ERROR;
}

int MallocMemory(PCB *pe, SqList *pPartTable,int i)
{
	PartiType se = {0, 0, {0}};
	////////////     以下补充    /////////////
	pe->DistbutSt = Allocated;
	pe->StartAddress = pPartTable->elem[i].PartStartAddr;
	strcpy(pPartTable->elem[i].Name, pe->Name);
	if(pPartTable->elem[i].PartitionSize > pe->MemorySize)
	{
		se.PartitionSize = pPartTable->elem[i].PartitionSize - pe->MemorySize;
		se.PartStartAddr = pPartTable->elem[i].PartStartAddr + pe->MemorySize;
		strcpy(se.Name, "");
		pPartTable->elem[i].PartitionSize = pe->MemorySize;                //不可丢
		InsertTable(pPartTable, i + 2, se);
	}

	return OK;
}

void InitAllocation(PCBList PCBdata, PartTable *pPartTable,AllocatStrategy AS)
{
	LNode *p;
	int pos;
	p = PCBdata->Next;
	while (p)
	{
		if(p->data.DistbutSt == Unallocated)
		{
			pos = SelectPart(&(p->data), pPartTable, AS);//从1开始
			if(pos)
			{
				MallocMemory( &(p->data), pPartTable, pos - 1);
			}
		}
		p = p->Next;
	}
}

void FreeMemory(int pos, SqList *pPartTable)
{
	PartiType se = {0, 0, {0}};
	////////////     以下补充     /////////////
	strcpy(pPartTable->elem[pos].Name, "");
	if(pos != 0)
	{
		if(!strcmp(pPartTable->elem[pos-1].Name, ""))
		{
			pPartTable->elem[pos-1].PartitionSize += pPartTable->elem[pos].PartitionSize;
			DeleteTable(pPartTable, pos + 1, &se);
		}
	}

	if(pos != pPartTable->length - 1)
	{
		if(!strcmp(pPartTable->elem[pos + 1].Name, ""))
		{
			//strcpy(pPartTable->elem[pos].Name, "");
			pPartTable->elem[pos].PartitionSize += pPartTable->elem[pos+1].PartitionSize;
			DeleteTable(pPartTable, pos + 2, &se);
		}
	}
}

void SearchSpace(PCBList PCBdata, SqList *partTable, AllocatStrategy AS)
{
	int pos;
	LNode *p;
	p = PCBdata->Next;
	while (p)
	{
		if(p->data.DistbutSt == Unallocated)
		{
			pos = SelectPart(&(p->data), partTable, AS);//从1开始
			if(pos)
			{
				MallocMemory(&(p->data), partTable, pos - 1);
			}
		}
		p = p->Next;
	}

}

void PrintProQueue(LinkList L)
{
	int i = 0;
	L = L->Next;
	printf(" ----------------------------------------\n");
	printf("|进程名 | 起始位置 | 申请大小 | 是否分配 |\n");
	while(L)
	{
		printf("|  %s   |  %4d    |  %4d    |  %4s    |\n",
			L->data.Name, L->data.StartAddress, L->data.MemorySize, L->data.DistbutSt == Allocated?  "是" : "否");
		L = L->Next;
	}
	printf(" ----------------------------------------\n");
}

void PrintPartTable(PartTable L)
{
	int i = 0, j = 0;
	printf(" ----------------------------------------\n");
	printf("|分区号 | 起始位置 | 分区大小 | 是否分配 |\n");
	for (i = 0; i < L.length; ++i)
		printf("|  %2d   |  %4d    |  %4d    |  %4s    |\n",
			i + 1 , L.elem[i].PartStartAddr, L.elem[i].PartitionSize , strcmp(L.elem[i].Name, "") ? L.elem[i].Name :"否");
	printf(" ----------------------------------------\n");
}