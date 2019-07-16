#ifndef _Data_h_
#define _Data_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INIT_SIZE 10
#define LISTINCREMENT  2
#define true				1
#define false				0
#define PCBType				PCB
#define Status				int
#define OK					1
#define	ERROR				0
#define NAME_MAXSIZE		20
#define PCB_Num				5
#define LIST_INITSIZE		10
#define PartiType			PartitionInfo
#define TotalMemory			512	//KB


typedef enum 
{
	Unallocated, Allocated
}DistributState, PartitionSt;

typedef enum
{
	FirstPriority, BestAdapt
}AllocatStrategy;


typedef struct 
{
	char Name[NAME_MAXSIZE];	//进程名
	int	MemorySize;				//内存的大小
	int StartAddress;			//内存起始地址
	DistributState DistbutSt;	//分配状态
}PCB;

typedef struct Node
{
	PCBType data;
	struct Node * Next;		
}LNode, *LinkList, *PCBList;			//

typedef struct {
							//分区号用数组下标代替
	int PartitionSize;
	int PartStartAddr;
	char Name[NAME_MAXSIZE];//若为空，则分区空闲
}PartitionInfo;

typedef struct
{
	PartiType *elem;
	int listsize;		//表容量
	int length;			//元素个数
}SqList, PartTable;		//分区表

#endif 
