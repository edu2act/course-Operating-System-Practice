#include "ProPCB.h"

/****************************
*  ʵ��01: ����ռʽ��̬����Ȩ	*
*  �� ����Ȩʼ�ձ��ֲ���		*
*  �� һ������CPU�����е�����	*
*  �� FCFSֻ���ǵ���ʱ���CPU	*
*  �� SPF��Ϊ����ʱ����ͬ		*
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
    LinkList PCBQueue;	//InitPCBdata������PCB��ʼ����
    ElemType e = {{0},-1,-1,-1,-1,-1,0,Ready};
    ElemType *pcb = NULL;
    PriorityRule PR;
    PR = FCFS;	   //   SPF    or   FCFS
    //***********    ��ʼ����������    *************//
    Init(&PCBQueue);
    InputData(&PCBQueue, PR);
    printf("��ʼ�������£�\n");
    PrintProQueue(PCBQueue, pcb);

    //***********    ���̸������ȼ���CPU    *************//
    printf("\n����������Ϣ���£�\n");
    while (OutProsess(PCBQueue, &e))
    {
        while(e.TimeUsedCPU < e.NeedRunningTime)	//����CPU�Ľ����Ƿ����
        {
            CPURunPro(PCBQueue, &e);		        //��CPU
            ++CPUUsedTime;					        //CPUʱ������
        }
    //***********    ������ִ�����ʱ��ӡ���    *************//
        e.FinishTime = CPUUsedTime;
        PrintProResult(&e);
    }

    return 0;
}