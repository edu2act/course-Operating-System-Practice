#ifndef _ProPCB_h_
#define _ProPCB_h_

#include "ChainList.h"

Status GetProcess(LinkList Q,ElemType e);				//上就绪队列
Status CPURunPro(LinkList Q,PCB *pcb,PriorityRule PR);	//CPU运行PCB
Status OutProsess(LinkList Q,ElemType *e);				//下就绪队列
double GetPriority(ElemType *e, PriorityRule PR);			//根据不同的规则PR 设置优先数
Status AddWaitTime(LinkList Q);							//未上CPU的进程的增加等待时间
void PrintProQueue(LinkList Q, PCB *pcb);				//打印运行后PCB信息
void PrintProResult(PCB *pcb);

#endif