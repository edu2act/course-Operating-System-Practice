#include "ProPCB.h"

extern int CPUUsedTime;

//功能：将e插入链表Q
Status GetProcess(LinkList Q,ElemType e)
{
    return ListInsert_L(Q, e);
}

//功能：根据不同的优先级规则，返回优先数
int GetPriority(ElemType *e, PriorityRule PR)
{
    if(PR == FCFS)
        return Infinity - e->ArrivalTime;
    else if(PR == SPF)
        return Infinity - e->NeedRunningTime;
    else
        printf("GetPriority Function ERROR!\n");
    return ERROR;
}

//功能：将链表Q的头结点数据放到e指向的内存，并删除
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

//功能：打印所有PCB信息
void PrintProQueue(LinkList Q, PCB *pcb)
{
    LinkList p = Q->Next;
   
    printf("进程名  优先数  到达时间  运行时间  已用CPU时间  完成时间  进程状态\n");
    if(pcb)
        printf(" %4s     %2d      %4d      %4d     %3d(+1)       %3d        %4s  \n",
        pcb->Name,pcb->Priority,pcb->ArrivalTime,pcb->NeedRunningTime,
        pcb->TimeUsedCPU, pcb->FinishTime,pcb->ProcessState == Ready ? "就绪" : "运行");
    while (p)
    {
        printf(" %4s     %2d      %4d      %4d     %3d           %3d        %4s  \n",
            p->data.Name,p->data.Priority,p->data.ArrivalTime,p->data.NeedRunningTime,
            p->data.TimeUsedCPU,p->data.FinishTime, p->data.ProcessState == Ready ? "就绪" : "运行");
        p = p->Next;
    }
    printf("-------------------------------------------------------------------------------\n");
}

//功能：当一个进程结束，打印进程信息
void PrintProResult(PCB *pcb)
{
    printf("进程名  到达时刻 运行时间 开始时刻 完成时刻 周转时间 带权周转时间 进程状态\n");
    if(pcb)
        printf(" %2s     %3d      %4d        %4d      %3d     %4d       %5.2lf       %4s  \n",
        pcb->Name,pcb->ArrivalTime,pcb->NeedRunningTime,pcb->StartTime,pcb->FinishTime,
        pcb->FinishTime-pcb->ArrivalTime,((pcb->FinishTime - pcb->ArrivalTime)*1.0)/pcb->NeedRunningTime,"完成");

    printf("-------------------------------------------------------------------------------\n");
}


