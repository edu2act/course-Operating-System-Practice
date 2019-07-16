#include "ProPCB.h"


int CPUUsedTime = 0;

void InputData(LinkList * pPCBdata)
{
	ElemType e = {{0},-1,-1,-1,-1,-1,-1,0,Ready};
	e.ArrivalTime = 0;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"A");
	e.WaitingTime = 0;
	e.Priority = GetPriority(&e,FCFS);
	e.NeedRunningTime = 4;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 1;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"B");
	e.WaitingTime = 0;
	e.Priority = GetPriority(&e,FCFS);
	e.NeedRunningTime = 1;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 2;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"C");
	e.WaitingTime = 0;
	e.Priority = GetPriority(&e,FCFS);
	e.NeedRunningTime = 3;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 3;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"D");
	e.WaitingTime = 0;
	e.Priority = GetPriority(&e,FCFS);
	e.NeedRunningTime = 3;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 4;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"E");
	e.WaitingTime = 0;
	e.Priority = GetPriority(&e,FCFS);
	e.NeedRunningTime = 4;
	GetProcess(*pPCBdata,e);
}

int main(void)
{
	LinkList PCBQueue = NULL, PCBdata = NULL;	//PCBdata里面存放原始数据
	ElemType e = {{0},-1,-1,-1,-1,-1,-1,0,Ready};
	ElemType *pcb = NULL;
	LNode *p;
	PriorityRule PR;
	Init(&PCBdata);
	InputData(&PCBdata);
	PrintProQueue(PCBdata, pcb);

	//以上是数据准备阶段
	Init(&PCBQueue);			//初始化就绪队列
	p = PCBdata->Next;			//定义从初始队列中拿数据的指针p
	
	PR = HRRatio;			    //选择调度算法
	while (p || PCBQueue->Next)
	{
		if(p && p->data.ArrivalTime == CPUUsedTime)
		{
			p->data.Priority = GetPriority(&(p->data), PR); 
			GetProcess(PCBQueue, p->data);
			p = p->Next;
		}
		OutProsess(PCBQueue, &e);	//队头元素出来
		CPURunPro(PCBQueue,&e, PR);	//上CPU
		++CPUUsedTime;				//CPU时间增加

		AddWaitTime(PCBQueue);		//给当前未上CPU的增加等待时间
        e.Priority = GetPriority(&e, PR);
        //PrintProQueue(PCBQueue, &e);
		if(e.TimeUsedCPU < e.NeedRunningTime)	//上完CPU的进程是否完毕
		{
			e.ProcessState = Ready;
            e.Priority = GetPriority(&e, PR);
			GetProcess(PCBQueue,e);
		}else
		{
			e.FinishTime = CPUUsedTime;
			PrintProResult(&e);
		}
	}

	return 0;
}