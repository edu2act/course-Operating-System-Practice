#ifndef _ChainList_h_
#define _ChainList_h_

#include "Data.h"

Status Init(LinkList *L);
Status GetElemt_L(LinkList L,int i,ElemType *e);
Status ListInsert_L(LinkList L,ElemType e);
Status OutProsess(LinkList Q,int i,ElemType *e);
Status ListDelete_L(LinkList L,int i,ElemType *e);

#endif
