#ifndef _Data_h_
#define _Data_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType PCB
#define Status int
#define true				1
#define false				0
#define OK					1
#define	ERROR				0
#define RESOURCE_NUM		3
#define	MAX_RESOURCE_A_NUM	10
#define	MAX_RESOURCE_B_NUM	5
#define	MAX_RESOURCE_C_NUM	7
#define NAME_MAXSIZE		20
#define PCB_Num 5
typedef struct{
	int MaxNum[RESOURCE_NUM];			//需要每项资源个数
	int AllocationNum[RESOURCE_NUM];	//已占用每项资源个数
	int NeedNum[RESOURCE_NUM];			//还需要的每项资源个数
}ResourceList;

typedef struct 
{
	char Name[NAME_MAXSIZE];			//进程名
	ResourceList resList;				//资源清单
}PCB;

typedef struct Node
{
	ElemType data;
	struct Node * Next;		
}LNode,*LinkList;

#endif
