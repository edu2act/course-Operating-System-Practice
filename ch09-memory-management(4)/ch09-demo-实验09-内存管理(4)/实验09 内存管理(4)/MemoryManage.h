#ifndef _MemoryManage_h_
#define _MemoryManage_h_

#include "List.h"

//*****         PCB 链 表 操 作        *****//
Status InsertProcess(LinkList Q,PCBType e);
Status DeleteProsess(LinkList Q,int i,PCBType *e);
//*****         分 区 表 操 作         *****//
//插入分区表元素
Status InsertTable_f(SqList_f *L, int i, PartiType e);	
//删除分区表元素
Status DeleteTable_f(SqList_f *L, int i, PartiType *e);


//******          页 表 操 作         ******//
//插入页表元素
Status InsertTable_y(SqList_y *L, int i, BlockNumType e);
//删除页表元素
Status DeleteTable_y(SqList_y *L, int i, BlockNumType *e);
Status LoadPages(PageTable *L, int size);
Status MallocMemory(PCB *pe, SqList_f *pPartTable, int *arr,int *pagenumArr);
//Status MallocMemory(PCB *pe, SqList_f *pPartTable, int *arr);
Status SelectPart(PCB* pPCB, SqList_f *pPartTable,int *arr);
//void SearchSpace(PCBList PCBdata, SqList_f *partTable);
void FreeMemory(int *arr, int len, SqList_f *pPartTable);
void InitAllocation(PCBList PCBdata, PartTable *partTable);
void PrintProQueue(LinkList L);
void PrintPartTable(PartTable L);




#endif