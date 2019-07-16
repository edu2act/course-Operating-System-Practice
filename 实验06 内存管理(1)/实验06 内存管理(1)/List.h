#ifndef _List_h_
#define _List_h_

#include "Data.h"

//*******           Á´±í            *******//
Status InitLinkList(LinkList *L);
void PCBAssign(PCBType *e1, PCBType e2);
Status GetElemt_L(LinkList L,int i,PCBType *e);
Status ListInsert_L(LinkList L,PCBType e);
Status ListDelete_L(LinkList L,int i,PCBType *e);

//******         ¶¯Ì¬Ë³Ðò±í           ******//
void PartiAssign(PartiType *e1, PartiType e2);
Status InitList_Sq(SqList *L);
Status ListInsert_Sq(SqList *L,int i,PartiType e);
Status ListDelete_Sq(SqList *L,int i,PartiType *e);

#endif