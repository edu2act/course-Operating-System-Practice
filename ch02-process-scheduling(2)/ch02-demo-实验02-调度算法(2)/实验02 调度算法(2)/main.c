#include "ProPCB.h"

/********************************************
 *		实验02: 抢占式静态优先权及短进程优先		*
 *		① 优先权属于静态优先权					*
 *		② 进入CPU运行一个时间片				*
 *		③ 考虑事先给定优先权和短进程优先两种情况	*
 *		④ 考虑到达时间不同					*
 *******************************************/

int CPUUsedTime = 0;

void InputData(LinkList * pPCBdata, PriorityRule PR)
{
	ElemType e = {{0},-1,-1,-1,-1,-1,-1,0,Ready};
	e.ArrivalTime = 0;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"A");
	e.Priority = GetPriority(&e, PR);
	e.GivenPriority = 8;
	e.NeedRunningTime = 4;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 1;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"B");
	e.Priority = GetPriority(&e, PR);
	e.GivenPriority = 3;
	e.NeedRunningTime = 3;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 2;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"C");
	e.Priority = GetPriority(&e, PR);
	e.GivenPriority = 2;
	e.NeedRunningTime = 5;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 3;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"D");
	e.Priority = GetPriority(&e, PR);
	e.GivenPriority = 9;
	e.NeedRunningTime = 2;
	GetProcess(*pPCBdata,e);

	e.ArrivalTime = 4;
	e.ProcessState = Ready;
	e.TimeUsedCPU = 0;
	strcpy(e.Name,"E");
	e.Priority = GetPriority(&e, PR);
	e.GivenPriority = 7;
	e.NeedRunningTime = 4;
	GetProcess(*pPCBdata,e);
}

int main(void)
{
	LinkList PCBQueue, PCBdata;	//PCBdata里面存放原始数据
    LNode *p;
	PriorityRule PR;
	ElemType e = {{0},-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,0 , Ready};
	ElemType *pcb = NULL;

	Init(&PCBdata);
	InputData(&PCBdata, FCFS);	
	PrintProQueue(PCBdata, pcb);

	//以上是数据准备阶段
	Init(&PCBQueue);			
	p = PCBdata->Next;			//定义从初始队列中拿数据的指针p
	
	PR = SPF;					// SPF, SS	//短进程优先，静态优先权
	while (p || PCBQueue->Next)
	{
		if(p && p->data.ArrivalTime == CPUUsedTime)
		{
			p->data.Priority = GetPriority(&(p->data), PR);//重新确定优先权，因为初始态
			GetProcess(PCBQueue, p->data);
			p = p->Next;
		}
		if(!OutProsess(PCBQueue, &e) && p)	//队头元素出来
		{
			++CPUUsedTime;
			break;
		}
		CPURunPro(PCBQueue, &e);		//上CPU
		++CPUUsedTime;						//CPU时间增加

		if(e.TimeUsedCPU < e.NeedRunningTime)	//上完CPU的进程是否完毕
		{
			e.ProcessState = Ready;
            e.Priority = GetPriority(&e, PR);  //取得最新优先权
			GetProcess(PCBQueue, e);
		}else
		{
			e.FinishTime = CPUUsedTime;
			PrintProResult(&e);
		}
	}

	return 0;
}