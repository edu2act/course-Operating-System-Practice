#ifndef _Data_h_
#define _Data_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType PCB
#define Status int
#define OK		1
#define	ERROR	0
#define TimeSlice	1
#define Infinity 10 //INT_MAX


#define NAME_MAXSIZE 20
typedef enum 
{
	Ready,Running,Block
}ProState;

typedef enum 
{
	FCFS, SPF, SS	//先来先服务，短进程优先，静态优先权(自己定的)
}PriorityRule;


typedef struct 
{
	char Name[NAME_MAXSIZE];	//进程名
	int Priority;				//优先数
	int GivenPriority;			//给定优先权
	int ArrivalTime;			//到达时间		以时间片为单位
	int NeedRunningTime;		//运行时间		以时间片为单位
	int StartTime;				//开始执行时间
	int FinishTime;				//完成时间
	int TimeUsedCPU;			//已用CPU时间		以时间片为单位
	ProState ProcessState;		//进程状态
}PCB;

typedef struct Node
{
	ElemType data;
	struct Node * Next;		
}LNode,*LinkList;



#endif
