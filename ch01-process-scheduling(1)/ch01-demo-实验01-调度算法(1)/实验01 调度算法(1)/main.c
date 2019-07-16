#include "ProPCB.h"

/****************************
*  实验01: 非抢占式静态优先权	*
*  ① 优先权始终保持不变		*
*  ② 一旦进入CPU便运行到结束	*
*  ③ FCFS只考虑到达时间进CPU	*
*  ④ SPF认为到达时间相同		*
****************************/

int CPUUsedTime = 0;

void InputData(LinkList * pPCBdata, PriorityRule PR)
{
    ElemType e = {{0},-1,-1,-1,-1,-1,0,Ready};
    e.ArrivalTime = 0;
    e.ProcessState = Ready;
    e.TimeUsedCPU = 0;
    strcpy(e.Name,"A");
    e.NeedRunningTime = 1;
    e.Priority = GetPriority(&e, PR);
    if(PR == SPF)   e.ArrivalTime = 0;
    GetProcess(*pPCBdata,e);

    e.ArrivalTime = 1;
    e.ProcessState = Ready;
    e.TimeUsedCPU = 0;
    strcpy(e.Name,"B");
    e.NeedRunningTime = 100;
    e.Priority = GetPriority(&e, PR);
    if(PR == SPF)   e.ArrivalTime = 0;
    GetProcess(*pPCBdata,e);

    e.ArrivalTime = 2;
    e.ProcessState = Ready;
    e.TimeUsedCPU = 0;
    strcpy(e.Name,"C");
    e.NeedRunningTime = 1;
    e.Priority = GetPriority(&e, PR);
    if(PR == SPF)   e.ArrivalTime = 0;
    GetProcess(*pPCBdata,e);

    e.ArrivalTime = 3;
    e.ProcessState = Ready;
    e.TimeUsedCPU = 0;
    strcpy(e.Name,"D");
    e.NeedRunningTime = 100;
    e.Priority = GetPriority(&e, PR);
    if(PR == SPF)   e.ArrivalTime = 0;
    GetProcess(*pPCBdata,e);

}

//void InputData1(LinkList * pPCBdata, PriorityRule PR)
//{
//    ElemType e = {{0},-1,-1,-1,-1,-1,0,Ready};
//    e.ArrivalTime = 0;
//    e.ProcessState = Ready;
//    e.TimeUsedCPU = 0;
//    strcpy(e.Name,"A");
//    e.NeedRunningTime = 4;
//    e.Priority = GetPriority(&e, PR);
//    if(PR == SPF)   e.ArrivalTime = 0;
//    GetProcess(*pPCBdata,e);
//
//    e.ArrivalTime = 1;
//    e.ProcessState = Ready;
//    e.TimeUsedCPU = 0;
//    strcpy(e.Name,"B");
//    e.NeedRunningTime = 3;
//    e.Priority = GetPriority(&e, PR);
//    if(PR == SPF)   e.ArrivalTime = 0;
//    GetProcess(*pPCBdata,e);
//
//    e.ArrivalTime = 2;
//    e.ProcessState = Ready;
//    e.TimeUsedCPU = 0;
//    strcpy(e.Name,"C");
//    e.NeedRunningTime = 5;
//    e.Priority = GetPriority(&e, PR);
//    if(PR == SPF)   e.ArrivalTime = 0;
//    GetProcess(*pPCBdata,e);
//
//    e.ArrivalTime = 3;
//    e.ProcessState = Ready;
//    e.TimeUsedCPU = 0;
//    strcpy(e.Name,"D");
//    e.NeedRunningTime = 2;
//    e.Priority = GetPriority(&e, PR);
//    if(PR == SPF)   e.ArrivalTime = 0;
//    GetProcess(*pPCBdata,e);
//
//    e.ArrivalTime = 4;
//    e.ProcessState = Ready;
//    e.TimeUsedCPU = 0;
//    strcpy(e.Name,"E");
//    e.NeedRunningTime = 4;
//    e.Priority = GetPriority(&e, PR);
//    if(PR == SPF)   e.ArrivalTime = 0;
//    GetProcess(*pPCBdata,e);
//}


int main(void)
{
    LinkList PCBQueue;	//InitPCBdata里面存放PCB初始数据
    ElemType e = {{0},-1,-1,-1,-1,-1,0,Ready};
    ElemType *pcb = NULL;
    PriorityRule PR;
    PR = FCFS;	   //   SPF    or   FCFS
    //***********    初始化就绪队列    *************//
    Init(&PCBQueue);
    InputData(&PCBQueue, PR);
    printf("初始数据如下：\n");
    PrintProQueue(PCBQueue, pcb);

    //***********    进程根据优先级上CPU    *************//
    printf("\n进程运行信息如下：\n");
    while (OutProsess(PCBQueue, &e))
    {
        while(e.TimeUsedCPU < e.NeedRunningTime)	//上完CPU的进程是否完毕
        {
            CPURunPro(PCBQueue, &e);		        //上CPU
            ++CPUUsedTime;					        //CPU时间增加
        }
    //***********    当进程执行完毕时打印输出    *************//
        e.FinishTime = CPUUsedTime;
        PrintProResult(&e);
    }

    return 0;
}