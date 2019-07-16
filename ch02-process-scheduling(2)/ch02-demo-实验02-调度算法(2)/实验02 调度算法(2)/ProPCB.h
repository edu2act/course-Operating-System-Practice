#ifndef _ProPCB_h_
#define _ProPCB_h_

#include "ChainList.h"

Status GetProcess(LinkList Q,ElemType e);

int GetPriority(ElemType *e, PriorityRule PR);

Status OutProsess(LinkList Q,ElemType *e);

Status CPURunPro(LinkList Q,PCB *pcb );

void PrintProQueue(LinkList Q, PCB *pcb);

void PrintProResult(PCB *pcb);

#endif