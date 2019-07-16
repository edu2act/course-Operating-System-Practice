#include "ProPCB.h"

void InputData(LinkList * pPCBdata)
{
	ElemType e = {{0},{{0},{0},{0}}};
	strcpy(e.Name,"P0");
	e.resList.MaxNum[0] = 7;	e.resList.MaxNum[1] = 5;	e.resList.MaxNum[2] = 3;
	e.resList.AllocationNum[0] = 0;
	e.resList.AllocationNum[1] = 1;
	e.resList.AllocationNum[2] = 0;
	e.resList.NeedNum[0] = 7;	e.resList.NeedNum[1] = 4;	e.resList.NeedNum[2] = 3;	
	GetProcess(*pPCBdata,e);

	strcpy(e.Name,"P1");
	e.resList.MaxNum[0] = 3;	e.resList.MaxNum[1] = 2;	e.resList.MaxNum[2] = 2;
	e.resList.AllocationNum[0] = 2;
	e.resList.AllocationNum[1] = 0;
	e.resList.AllocationNum[2] = 0;
	e.resList.NeedNum[0] = 1;	e.resList.NeedNum[1] = 2;	e.resList.NeedNum[2] = 2;	
	GetProcess(*pPCBdata,e);

	strcpy(e.Name,"P2");
	e.resList.MaxNum[0] = 9;	e.resList.MaxNum[1] = 0;	e.resList.MaxNum[2] = 2;
	e.resList.AllocationNum[0] = 3;
	e.resList.AllocationNum[1] = 0;
	e.resList.AllocationNum[2] = 2;
	e.resList.NeedNum[0] = 6;	e.resList.NeedNum[1] = 0;	e.resList.NeedNum[2] = 0;	
	GetProcess(*pPCBdata,e);

	strcpy(e.Name,"P3");
	e.resList.MaxNum[0] = 2;	e.resList.MaxNum[1] = 2;	e.resList.MaxNum[2] = 2;
	e.resList.AllocationNum[0] = 2;
	e.resList.AllocationNum[1] = 1;
	e.resList.AllocationNum[2] = 1;
	e.resList.NeedNum[0] = 0;	e.resList.NeedNum[1] = 1;	e.resList.NeedNum[2] = 1;	
	GetProcess(*pPCBdata,e);

	strcpy(e.Name,"P4");
	e.resList.MaxNum[0] = 4;	e.resList.MaxNum[1] = 3;	e.resList.MaxNum[2] = 3;
	e.resList.AllocationNum[0] = 0;
	e.resList.AllocationNum[1] = 0;
	e.resList.AllocationNum[2] = 2;
	e.resList.NeedNum[0] = 4;	e.resList.NeedNum[1] = 3;	e.resList.NeedNum[2] = 1;	
	GetProcess(*pPCBdata,e);
}

int main(void)
{
	LinkList PCBdata;	//PCBdata里面存放原始数据
	ElemType e = {{0},{{0},{0},{0}}};
	char PcbName[NAME_MAXSIZE], choice;
	int Max[PCB_Num][RESOURCE_NUM] = {0}, Allocation[PCB_Num][RESOURCE_NUM] = {0};
	int Need[PCB_Num][RESOURCE_NUM] = {0}, Available[RESOURCE_NUM] = {0};
	int Request[RESOURCE_NUM] = {0},pos = 0, i;
	LNode *p = NULL, *q;

	Init(&PCBdata);
	InputData(&PCBdata);

	do{
		system("cls");
		GetMatrixData(PCBdata, *Max ,*Allocation, *Need, Available);//获取矩阵
		PrintProQueue(PCBdata, Available);							//打印初态效果
		printf(" ================================================\n");
		printf("|               1.申 请 资 源                    |\n");
		printf("|               2.释 放 资 源                    |\n");
		printf("|               3.结 束 进 程                    |\n");
		printf("|               4.退 出 系 统                    |\n");
		printf(" ================================================\n");
		printf("请选择:");

		fflush(stdin);
		scanf("%c",&choice);
		switch (choice)
		{
		case '1':
			printf("请输入进程名，资源ABC：");
			scanf("%s%d%d%d",PcbName,&Request[0],&Request[1],&Request[2]);

			for (p = PCBdata->Next, pos = 1; 
				pos <= PCB_Num && strcmp(PcbName, p->data.Name); 
				pos++, p = p->Next);
			if(pos > PCB_Num)
			{
				printf("名字有误！\n");
				break;
			}
			if(BankerAlgorithm(*Allocation, Request,pos - 1, *Need, Available))
				AllocateResource(PCBdata, pos, Request);
			GetMatrixData(PCBdata, *Max ,*Allocation, *Need, Available);//获取矩阵
			PrintProQueue(PCBdata, Available);
			break;
		case '2':
			printf("请输入进程名，资源ABC：");
			scanf("%s%d%d%d",PcbName,&Request[0],&Request[1],&Request[2]);

			for (p = PCBdata->Next, pos = 1; 
				pos <= PCB_Num && strcmp(PcbName, p->data.Name); 
				pos++, p = p->Next);
			if(pos > PCB_Num)
			{
				printf("名字有误！\n");
				break;
			}
			if(ReleaseAlgorithm( *Allocation, Request, pos-1))
				ReleaseResource(PCBdata, pos, Request);
			GetMatrixData(PCBdata, *Max ,*Allocation, *Need, Available);//获取矩阵
			PrintProQueue(PCBdata, Available);	
			break;

		case '3':
			printf("请输入进程名：");
			scanf("%s",PcbName);
			for (p = PCBdata->Next, pos = 1; 
				pos <= PCB_Num && strcmp(PcbName, p->data.Name); 
				pos++, p = p->Next);
			if(pos > PCB_Num)
			{
				printf("名字有误！\n");
				break;
			}
			OutProsess(PCBdata, pos, &e);
			GetMatrixData(PCBdata, *Max ,*Allocation, *Need, Available);//获取矩阵
			PrintProQueue(PCBdata, Available);	
			break;
		case '4':
			return 0;


		}
		system("pause");

	}while (1);

	return 0;
}