
#include "MemoryManage.h"

//*****         PCB�������        *****//
Status InsertProcess(LinkList Q,PCBType e)
{
	return ListInsert_L(Q, e);
}

Status DeleteProsess(LinkList Q,int i,PCBType *e)
{
	return ListDelete_L(Q ,i,e);
}

//*****         ���������        *****//
Status InsertTable_f(SqList_f *L, int i, PartiType e) 
{
	return ListInsert_f(L,i, e);
}

Status DeleteTable_f(SqList_f *L, int i, PartiType *e)
{
	return ListDelete_f(L, i, e);
}

//*****         ҳ�����        *****//
Status InsertTable_y(SqList_y *L, int i, BlockNumType e)
{
	return ListInsert_y(L,i, e);
}

Status DeleteTable_y(SqList_y *L, int i, BlockNumType *e)
{
	return ListDelete_y(L, i, e);
}

Status LoadPages(PageTable *L, int size)
{
    int i, pageNum = ceil( size * 1.0 / PageSize) ;
    PageData e = {-1, Unallocated};
    for (i = 0; i < pageNum; i++)
    {
        if(!InsertTable_y(L, L->length + 1, e))
            return ERROR;
    }
    return OK;
}



//���صڼ����ڴ�飬��1��ʼ��������0����������
Status SelectPart(PCB* pPCB, SqList_f *pPartTable,int *arr)
{
	/////////////     ���²���     /////////////
    int pageNum = 0, i, k = 0;

	pageNum = pPCB->PagesLoadedNum ;
	for (i = 0; i < pPartTable->length && k < pageNum; i++)
	{
		if(!strcmp( pPartTable->elem[i].Name,""))
        {
            arr[k++] = i;
        }
	}
    if(k >= pageNum)                //ע��
        return OK;
    return ERROR;
}

Status MallocMemory(PCB *pe, SqList_f *pPartTable, int *arr,int *pagenumArr)
{
    int i, pageNum = pe->PagesLoadedNum ;
    PageData e = {-1, Allocated};
    ////////////      ���²���     /////////////

    for ( i = 0; i < pageNum ; i++)
    {
        if(pe->pPagetable->elem[pagenumArr[i]].DistbutSt == Allocated){
            printf("%d��ҳ���Ѿ�װ�룬��������װ��!\n", pagenumArr[i]);
            return ERROR;
        }
        pe->pPagetable->elem[pagenumArr[i]].DistbutSt = Allocated;
        pe->pPagetable->elem[pagenumArr[i]].BlockNum = arr[i];  //length + 1, arr[i] + 1 ��Ŵ�1��ʼ
        strcpy(pPartTable->elem[arr[i]].Name , pe->Name);
    }
    return OK;

}

void InitAllocation(PCBList PCBdata, PartTable *pPartTable)
{
	LNode *p;
    int i, arr[20] = {0}, pagenumArr[PageArrLength] = {0};
	p = PCBdata->Next;
    
	while (p)
	{
        for (i = 0; i < ceil(p->data.MemorySize * 1.0 / PageSize) ; i++){
            pagenumArr[i] = i;
        }
        p->data.PagesLoadedNum = i;
		if(p->data.pPagetable->elem[0].DistbutSt == Unallocated)
		{
			if(SelectPart(&(p->data), pPartTable, arr))
			{
				MallocMemory(&(p->data), pPartTable, arr, pagenumArr);
			}
		}
		p = p->Next;
	}
}

//���ͷŽ���ֻ�ڽ�������ʱ�õ�����˲��ùܽ�����Ϣ
void FreeMemory(int *arr, int len, SqList_f *pPartTable)
{
    int i;
	////////////     ���²���   /////////////
    for (i = 0; i < len; i++)
        strcpy(pPartTable->elem[arr[i]].Name, "");
}

//void SearchSpace(PCBList PCBdata, SqList_f *partTable)
//{
//    int pos, arr[20] = {0};
//	LNode *p;
//	p = PCBdata->Next;
//	while (p)
//	{
//		if(p->data.pPagetable->elem[0].DistbutSt == Unallocated)
//		{
//			if(SelectPart(&(p->data), partTable, arr))
//			{
//				MallocMemory(&(p->data), partTable, arr);
//			}
//		}
//		p = p->Next;
//	}
//
//}

void PrintProQueue(LinkList L)
{
	int i = 0;

	L = L->Next;
	
	while(L)
	{
        printf(" -----------------------------\n");
        printf("|������ | �����С |\n");
        printf("|  %s   |  %4d    |\n", L->data.Name, L->data.MemorySize);

            printf("%sҳ����Ϣ���£�\n|   ҳ��   |   ���   | �Ƿ���� |\n", L->data.Name);
            for (i = 0; i < L->data.pPagetable->length; i++)
                printf("|  %4d    |  %4d    |  %4s    |\n", i , L->data.pPagetable->elem[i].BlockNum,
                        L->data.pPagetable->elem[i].DistbutSt == Allocated?  "��" : "��");
		L = L->Next;
	}
	printf(" ----------------------------------------\n");
}

void PrintPartTable(PartTable L)
{
	int i = 0, j = 0;
	printf(" ----------------------------------------\n");
	printf("|������ | ��ʼλ�� | ������С | �Ƿ���� |\n");
	for (i = 0; i < L.length; ++i)
		printf("|  %2d   |  %4d    |  %4d    |  %4s    |\n",
			i , L.elem[i].PartStartAddr, PageSize , strcmp(L.elem[i].Name, "") ? L.elem[i].Name :"��");
	printf(" ----------------------------------------\n");
}