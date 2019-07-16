#include "MemoryManage.h"

/*   实验08  基本分页   */

void InputPCBData(PCBList * pPCBdata)
{
	PCBType e = {{0}, 0, NULL};
    
	strcpy(e.Name,"P1");
	e.MemorySize = 16;
    InitList_y(&(e.pPagetable));
    LoadPages(e.pPagetable, e.MemorySize);
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P2");
	e.MemorySize = 32;
    InitList_y(&(e.pPagetable));
    LoadPages(e.pPagetable, e.MemorySize);
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P3");
	e.MemorySize = 48;
    InitList_y(&(e.pPagetable));
    LoadPages(e.pPagetable, e.MemorySize);
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P4");
	e.MemorySize = 96;
    InitList_y(&(e.pPagetable));
    LoadPages(e.pPagetable, e.MemorySize);
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P5");
	e.MemorySize = 100;
    InitList_y(&(e.pPagetable));
    LoadPages(e.pPagetable, e.MemorySize);
	InsertProcess(*pPCBdata,e);
}

void SettingPage(PartTable * pPartdata)
{
	PartiType se = {0, {0}};
	int Num = (512 - 16) / PageSize , i;
	for (i = 0; i < Num; ++i)
	{
		se.PartStartAddr = 16 + i * PageSize;
		InsertTable_f(pPartdata, i + 1, se);
	}
}
//0 - 15Kb 操作系统占用  总大小512KB
int main(void)
{
	PCBList PCBdata;		//PCBdata里面存放原始PCB数据
	PartTable partTable;	//分区表
	char PcbName[NAME_MAXSIZE] = {0}, choice;
	PCBType PCBe = {{0}, 0, NULL};
	PartiType Parte = {0, 0};
	PCBType *pcb = NULL;
	LNode *p; 
	
    int i, size, pos, arr[20] = {0}, k = 0;

	InitList_f(&partTable);
	SettingPage(&partTable);
	InitLinkList(&PCBdata);
	InputPCBData(&PCBdata);
	InitAllocation(PCBdata, &partTable);

	PrintProQueue(PCBdata);
	PrintPartTable(partTable);
	
	while(true)
	{
		system("cls");
		PrintProQueue(PCBdata);
		PrintPartTable(partTable);
		printf(" ================================================\n");
		printf("|           1.结 束 进 程                        |\n");
		printf("|           2.添 加 进 程                        |\n");
		printf("|           3.退 出 系 统                        |\n");
		printf(" ================================================\n");
		printf("请选择:");
		fflush(stdin);
		scanf("%c",&choice);
		
		switch (choice)
		{
		case '1':
			printf("要结束的进程名:");
			scanf("%s",PcbName);
			for (p = PCBdata->Next, i = 1; p && strcmp(PcbName, p->data.Name); i++, p = p->Next);
			if(!p)
			{
				printf("进程名输入错误!\n");
				break;
			}
			DeleteProsess(PCBdata, i, &PCBe);
            k = 0;
			for(i = 0; i < partTable.length; i++)
			{
				if(!strcmp(PcbName, partTable.elem[i].Name))
				{
					arr[k++] = i;
				}
			}
            FreeMemory(arr, k, &partTable);

			SearchSpace(PCBdata, &partTable);
			break;
		case '2':
			printf("请输入添加的进程名，进程所占内存大小:");
			scanf("%s%d",PcbName , &size);
			strcpy(PCBe.Name, PcbName);
			PCBe.MemorySize = size;
            InitList_y(&(PCBe.pPagetable));
            LoadPages(PCBe.pPagetable, PCBe.MemorySize);
			if(SelectPart(&(PCBe), &partTable, arr))
				MallocMemory(&(PCBe), &partTable, arr);
			InsertProcess(PCBdata, PCBe);
			break;
		case '3':
			return 0;

		default:
			printf("选择项输入错误，重新选择！\n");
			break;
		}
		PrintProQueue(PCBdata);
		PrintPartTable(partTable);
		system("pause");
	}

	return 0;
}