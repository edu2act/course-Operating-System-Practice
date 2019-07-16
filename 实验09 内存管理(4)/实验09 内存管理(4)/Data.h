#ifndef _Data_h_
#define _Data_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
#define BlockNumType		PageData //分页信息
#define TotalMemory			512	//KB
#define PageSize			16	//通常为1 ~ 8KB    //进程申请内存的大小[16, 256]KB    256 / 8 = 32页
#define PageArrLength       ((512 - 16) / PageSize)


typedef enum 
{
	Unallocated, Allocated
}DistributState, PartitionSt;



typedef struct {
							//分区号用数组下标代替
	int PartStartAddr;
	char Name[NAME_MAXSIZE];//若为空，则分区空闲
}PartitionInfo;

typedef struct
{
	PartitionInfo *elem;
	int listsize;		//表容量
	int length;			//元素个数
}SqList_f, PartTable;	//分区使用说明表


typedef struct {					    
	int BlockNum;               //块号
	DistributState DistbutSt;	//分配状态
}PageData;


typedef struct
{
	PageData *elem;	
	int listsize;		
	int length;			
}SqList_y, PageTable;	//页表


typedef struct 
{
	char Name[NAME_MAXSIZE];	//进程名
	int	MemorySize;				//内存的大小
    int PagesLoadedNum;         //装入页面个数
	PageTable *pPagetable;		//页表指针
}PCB;

typedef struct Node
{
	PCBType data;
	struct Node * Next;		
}LNode, *LinkList, *PCBList;


#endif 
