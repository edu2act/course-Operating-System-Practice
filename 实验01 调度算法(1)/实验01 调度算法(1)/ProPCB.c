#include "ProPCB.h"

extern int CPUUsedTime;

//���ܣ���e��������Q
Status GetProcess(LinkList Q,ElemType e)
{
    return ListInsert_L(Q, e);
}

//���ܣ����ݲ�ͬ�����ȼ����򣬷���������
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

//���ܣ�������Q��ͷ������ݷŵ�eָ����ڴ棬��ɾ��
Status OutProsess(LinkList Q,ElemType *e)
{
    return ListDelete_L(Q ,e);
}

//��һ��CPU����ʱ������1��ʱ��Ƭ
Status CPURunPro(LinkList Q,PCB *pcb)
{
    if(pcb->StartTime == -1)
        pcb->StartTime = CPUUsedTime;
    pcb->ProcessState = Running;
    //PrintProQueue(Q, pcb);
    pcb->TimeUsedCPU += TimeSlice;

    return OK;
}

//���ܣ���ӡ����PCB��Ϣ
void PrintProQueue(LinkList Q, PCB *pcb)
{
    LinkList p = Q->Next;
   
    printf("������  ������  ����ʱ��  ����ʱ��  ����CPUʱ��  ���ʱ��  ����״̬\n");
    if(pcb)
        printf(" %4s     %2d      %4d      %4d     %3d(+1)       %3d        %4s  \n",
        pcb->Name,pcb->Priority,pcb->ArrivalTime,pcb->NeedRunningTime,
        pcb->TimeUsedCPU, pcb->FinishTime,pcb->ProcessState == Ready ? "����" : "����");
    while (p)
    {
        printf(" %4s     %2d      %4d      %4d     %3d           %3d        %4s  \n",
            p->data.Name,p->data.Priority,p->data.ArrivalTime,p->data.NeedRunningTime,
            p->data.TimeUsedCPU,p->data.FinishTime, p->data.ProcessState == Ready ? "����" : "����");
        p = p->Next;
    }
    printf("-------------------------------------------------------------------------------\n");
}

//���ܣ���һ�����̽�������ӡ������Ϣ
void PrintProResult(PCB *pcb)
{
    printf("������  ����ʱ�� ����ʱ�� ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ�� ����״̬\n");
    if(pcb)
        printf(" %2s     %3d      %4d        %4d      %3d     %4d       %5.2lf       %4s  \n",
        pcb->Name,pcb->ArrivalTime,pcb->NeedRunningTime,pcb->StartTime,pcb->FinishTime,
        pcb->FinishTime-pcb->ArrivalTime,((pcb->FinishTime - pcb->ArrivalTime)*1.0)/pcb->NeedRunningTime,"���");

    printf("-------------------------------------------------------------------------------\n");
}


