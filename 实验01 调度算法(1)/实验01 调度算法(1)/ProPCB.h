#ifndef _ProPCB_h_
#define _ProPCB_h_

#include "ChainList.h"

//功能：将e插入链表Q
Status GetProcess(LinkList Q,ElemType e);		//上就绪队列

//功能：根据不同的优先级规则，返回优先数
int GetPriority(ElemType *e, PriorityRule PR);  //根据不同的规则PR 设置优先数

//功能：将链表Q的头结点数据放到e指向的内存，并删除
Status OutProsess(LinkList Q,ElemType *e);	    //下就绪队列

//功能：CPU运行pcb指向的进程，并输出所有进行进程状态
Status CPURunPro(LinkList Q, PCB *pcb);	        //CPU运行PCB

//功能：打印所有PCB信息
void PrintProQueue(LinkList Q, PCB *pcb);		//打印运行后PCB信息

//功能：当一个进程结束，打印进程信息
void PrintProResult(PCB *pcb);

#endif