#include "MemoryManage.h"

/*实验06 固定分区分配
* 分配策略：
* ①离队首最近，能够装入该分区的进程；
* ②搜索能够装入该分区最大的进程。
*/

int CF_i;

void InputPCBData(PCBList * pPCBdata)
{
	PCBType e = {{0}, 0, 0, Unallocated};
	strcpy(e.Name,"P1");
	e.MemorySize = 16;
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P2");
	e.MemorySize = 32;
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P3");
	e.MemorySize = 48;
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P4");
	e.MemorySize = 96;
	InsertProcess(*pPCBdata,e);

	strcpy(e.Name,"P5");
	e.MemorySize = 100;
	InsertProcess(*pPCBdata,e);
}

void SetFixedZone(PartTable * pPartdata)
{
	PartiType se = {0, 0, {0}};
	se.PartStartAddr = 16;
	se.PartitionSize = 512 - 16;
	strcpy(se.Name, "");
	InsertTable(pPartdata, 1, se);
}
//0 - 15Kb 操作系统占用  总大小512KB
int main(void)
{
	PCBList PCBdata;		//PCBdata里面存放原始PCB数据
	PartTable partTable;	//分区表
	char PcbName[NAME_MAXSIZE] = {0}, choice;
	PCBType PCBe = {{0}, 0, 0, Unallocated};
	PartiType Parte = {0, 0};
	PCBType *pcb = NULL;
	LNode *p; 
	AllocatStrategy AS = CycleFirst; //FirstPriority, BestAdapt, CycleFirst
	int i, size, pos;

	InitList_Sq(&partTable);
	SetFixedZone(&partTable);
	InitLinkList(&PCBdata);
	InputPCBData(&PCBdata);
	InitAllocation(PCBdata, &partTable, AS);

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
			for(i = 0; i < partTable.length; i++)
			{
				if(!strcmp(PcbName, partTable.elem[i].Name))
				{
					FreeMemory(i ,&partTable);
					break;
				}
			}

			SearchSpace( PCBdata, &partTable, AS);
			break;
		case '2':
			printf("请输入添加的进程名，进程所占内存大小:");
			scanf("%s%d",PcbName , &size);
			PCBe.DistbutSt = Unallocated;
			PCBe.StartAddress = 0;
			strcpy(PCBe.Name, PcbName);
			PCBe.MemorySize = size;
			pos = SelectPart(&(PCBe), &partTable, AS);//从1开始
			if(pos)
				MallocMemory(&(PCBe), &partTable, pos - 1);
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