#ifndef _ProPCB_h_
#define _ProPCB_h_

#include "ChainList.h"
//功能：将进程e放入链表Q
Status GetProcess(LinkList Q,ElemType e);				//上就绪队列

//功能：将链表Q中第一个结点数据域信息给了e指向的内存并删除
Status OutProsess(LinkList Q,ElemType *e);				//下就绪队列

//功能：银行家算法
Status BankerAlgorithm(int *Allocation, int *Request,int i, int *Need, int *Available);

//功能：安全检查
Status SecurityCheck(int *Allocation,int *Need, int *Available);

//功能：将申请资源分配给第pos个进程
Status AllocateResource(LinkList PCBdata , int pos , int *Request);

//功能：将PCB资源信息生成矩阵
void GetMatrixData(LinkList PCBdata,int *Max,int *Allocation,int *Need,int *Available);

//功能：打印链表中资源信息
void PrintProQueue(LinkList L, int *A);

//功能：判断释放资源合法性
Status ReleaseAlgorithm(int *Allocation, int *Request, int pos);

//功能：释放资源
Status ReleaseResource(LinkList PCBdata ,int pos, int *Request);

#endif