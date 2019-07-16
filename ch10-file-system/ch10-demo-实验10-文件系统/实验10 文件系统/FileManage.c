#include "FileManage.h"


void FileOperatInterface(LinkList_U *pUfd)
{
	char FileName[MAX_NAME_SIZE] = {0} ,choice, Pwd1[MAX_NAME_SIZE] = {0}, Pwd2[MAX_NAME_SIZE] = {0};
	int i;
	while(true)
	{
		system("cls");
		printf(" ================================================\n");
		printf("|                 1. 新 建 文 件                 |\n");
		printf("|                 2. 显示所有文件                |\n");
		printf("|                 3. 写入文件内容                |\n");
		printf("|                 4. 打 开 文 件                 |\n");
		printf("|                 5. 删 除 文 件                 |\n");
		printf("|                 6. 退 出 系 统                 |\n");
		printf(" ================================================\n");
		printf("请选择:");
		fflush(stdin);
		scanf("%c",&choice);

		switch (choice)
		{
		case '1':
			printf("请输入文件名：");
			scanf("%s", FileName);
			if(CreateFile(pUfd, FileName))
			{
				printf("文件创建成功!\n");
				break;
			}
			printf("文件创建失败!\n");

			break;
		case '2':
			VisitFile(*pUfd);
			break;
		case '3':
			printf("请输入文件名：");
			scanf("%s", FileName);
			if(!AddContent(pUfd ,FileName))
				printf("文件不存在!\n");
			break;

		case '4':
			printf("请输入文件名：");
			scanf("%s", FileName);
			if(!OpenFile(*pUfd, FileName))
				printf("文件不存在!\n");

			break;
		case '5':
			printf("请输入文件名：");
			scanf("%s", FileName);
			if(!Delete(pUfd ,FileName))
				printf("文件不存在!\n");

			break;

		case '6':
			return ;
		default:
			printf("选择项输入错误，重新选择！\n");
			break;
		}
		system("pause");
	}

}

Status CreateFile(LinkList_U  *pUfd ,char *fileName)
{
	ElemType_U ele_u = {{0}, NULL};

	strcpy(ele_u.FileName, fileName);
	ele_u.FileAddress = (FCB *)malloc(sizeof(FCB));
	if(!ele_u.FileAddress)
		return ERROR;
	strcpy(ele_u.FileAddress->Content, "");
	strcpy(ele_u.FileAddress->FileName, fileName);

	ListInsert_U(*pUfd, ele_u);

	return OK;
}

void VisitFile(LinkList_U  Ufd)
{
	LinkList_U p = Ufd->Next;
	while (p)
	{
		printf("%s   ", p->data.FileName);
		p = p->Next;
	}
    printf("\n");
}

Status OpenFile(LinkList_U  Ufd ,char *fileName)
{
	LinkList_U p = Ufd->Next;
	while (p && strcmp(p->data.FileName, fileName)){
		p = p->Next;
	}
	if(!p)
		return ERROR;
	printf("%s\n", p->data.FileAddress->Content);
	return OK;
}

Status Delete(LinkList_U  *pUfd ,char *fileName)
{
	ElemType_U ele_u = {{0}, NULL};
	LinkList_U p = (*pUfd)->Next;
	int i = 1;
	while (p && strcmp(p->data.FileName, fileName)){
		p = p->Next;
		++i;
	}
	if(!p)
		return ERROR;
	free(ele_u.FileAddress);
	ListDelete_U(*pUfd ,i ,&ele_u);

	return OK;
}

Status AddContent(LinkList_U  *pUfd ,char *fileName)
{
	LinkList_U p = (*pUfd)->Next;
	while (p && strcmp(p->data.FileName, fileName)){
		p = p->Next;
	}
	if(!p)
		return ERROR;
	printf("请输入要写入的内容：");
	fflush(stdin);
	gets(p->data.FileAddress->Content);

	return OK;
}