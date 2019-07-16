#include "ProPCB.h"

extern int CPUUsedTime;

Status GetProcess(LinkList Q,ElemType e)
{
	return ListInsert_L(Q, e);
}

int GetPriority(ElemType *e, PriorityRule PR)
{
	if(PR == FCFS)
		return Infinity - e->ArrivalTime;
	else if(PR == SPF)
		return Infinity - (e->NeedRunningTime - e->TimeUsedCPU);  
	else if(PR == SS)
		return e->GivenPriority;
	else
		printf("GetPriority Function ERROR!\n");
	return ERROR;
}

Status OutProsess(LinkList Q,ElemType *e)
{
	return ListDelete_L(Q ,e);
}
//上一次CPU运行时间增加1个时间片
Status CPURunPro(LinkList Q,PCB *pcb)
{
	if(pcb->StartTime == -1)
		pcb->StartTime = CPUUsedTime;
	pcb->ProcessState = Running;
	//PrintProQueue(Q, pcb);
	pcb->TimeUsedCPU += TimeSlice;
	

	return OK;
}


void PrintProQueue(LinkList Q, PCB *pcb)
{
	LinkList p = Q->Next;

	printf("进程名  优先数  到达时间  运行时间  已用CPU时间  完成时间  进程状态\n");
	if(pcb)
		printf(" %4s     %2d      %4d      %4d     %3d(+1)       %3d        %4s  \n",
			pcb->Name,pcb->GivenPriority,pcb->ArrivalTime,pcb->NeedRunningTime,
			pcb->TimeUsedCPU, pcb->FinishTime,pcb->ProcessState == Ready ? "就绪" : "运行");
	while (p)
	{
		printf(" %4s     %2d      %4d      %4d     %3d           %3d        %4s  \n",
			p->data.Name,p->data.GivenPriority,p->data.ArrivalTime,p->data.NeedRunningTime,
			p->data.TimeUsedCPU,p->data.FinishTime, p->data.ProcessState == Ready ? "就绪" : "运行");
		p = p->Next;
	}
	printf("-------------------------------------------------------------------------------\n");
}


void PrintProResult(PCB *pcb)
{
	printf("进程名  到达时间 开始时间 运行时间 完成时间 周转时间 带权周转时间 进程状态\n");
	if(pcb)
		printf(" %2s     %4d      %4d        %3d      %3d     %4d       %5.2lf       %4s  \n",
			pcb->Name,pcb->ArrivalTime,pcb->StartTime,pcb->NeedRunningTime,pcb->FinishTime,
			pcb->FinishTime-pcb->ArrivalTime,((pcb->FinishTime - pcb->ArrivalTime)*1.0)/pcb->NeedRunningTime,"完成");
	
	printf("-------------------------------------------------------------------------------\n");
}
