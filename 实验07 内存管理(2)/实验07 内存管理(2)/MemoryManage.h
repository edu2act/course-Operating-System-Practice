#ifndef _MemoryManage_h_
#define _MemoryManage_h_

#include "List.h"

//*****         PCB链表操作        *****//
Status InsertProcess(LinkList Q,PCBType e);
Status DeleteProsess(LinkList Q,int i,PCBType *e);
//*****         分区表操作        *****//
Status InsertTable(SqList *L, int i, PartiType e);
Status DeleteTable(SqList *L, int i, PartiType *e);
int SelectPart(PCB* pPCB, SqList *pPartTable, AllocatStrategy AS);
int MallocMemory(PCB *pe, SqList *pPartTable,int i);
void SearchSpace(PCBList PCBdata, SqList *partTable, AllocatStrategy AS);
void FreeMemory(int pos, SqList *pPartTable);
void InitAllocation(PCBList PCBdata, PartTable *partTable, AllocatStrategy AS);
void PrintProQueue(LinkList L);
void PrintPartTable(PartTable L);




#endif