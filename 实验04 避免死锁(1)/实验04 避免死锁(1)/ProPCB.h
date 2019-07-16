#ifndef _ProPCB_h_
#define _ProPCB_h_

#include "ChainList.h"

Status GetProcess(LinkList Q,ElemType e);				//�Ͼ�������
Status OutProsess(LinkList Q,ElemType *e);				//�¾�������
Status BankerAlgorithm(int *Allocation, int *Request,int i, int *Need, int *Available);
Status SecurityCheck(int *Allocation,int *Need, int *Available);
Status AllocateResource(LinkList PCBdata , int pos , int *Request);
void GetMatrixData(LinkList PCBdata,int *Max,int *Allocation,int *Need,int *Available);
void PrintProQueue(LinkList L, int *A);


#endif