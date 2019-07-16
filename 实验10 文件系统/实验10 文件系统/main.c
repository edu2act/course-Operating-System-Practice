#include "FileManage.h"

/*实验10 文件系统
* 两级文件目录
*/


int main(void)
{
	RootList Root, p = NULL;
	ElemType_R ele_r = {{0}, {0}, NULL};
	UFDList Ufd;
	ElemType_U ele_u = {{0}, NULL};
	char UserName[MAX_NAME_SIZE] = {0} ,choice, Pwd1[MAX_NAME_SIZE] = {0}, Pwd2[MAX_NAME_SIZE] = {0};
	int i;

	InitLinkList_R(&Root);
	
	while(true)
	{
		system("cls");
		printf(" ================================================\n");
		printf("|           1. 新 建 用 户                        |\n");
		printf("|           2. 用 户 登 录                        |\n");
		printf("|           3. 退 出 系 统                        |\n");
		printf(" ================================================\n");
		printf("请选择:");
		fflush(stdin);
		scanf("%c",&choice);
		
		switch (choice)
		{
		case '1':
			printf("请输入创建的用户名：");
			scanf("%s",UserName);
			printf("请输入密码：");
			scanf("%s",Pwd1);
			printf("请再次输入密码：");
			scanf("%s",Pwd2);
			if(strcmp(Pwd1, Pwd2))
			{
				printf("两次密码一不一致！\n");
				break;
			}
			
			strcpy(ele_r.UserName, UserName);
			strcpy(ele_r.UserPWD, Pwd1);
			InitLinkList_U(&(ele_r.UserFileList));
			
			ListInsert_R(Root, ele_r);
			printf("创建用户成功！\n");
			break;
		case '2':
			printf("请输入用户名：");
			scanf("%s",UserName);
			p = Root->Next;
			while (p && strcmp(p->data.UserName, UserName)){
				p = p->Next;
			}
			if(!p){
				printf("用户名不存在!\n");
				break;
			}
			printf("请输入密码：");
			scanf("%s",Pwd1);
			if(strcmp(p->data.UserPWD, Pwd1)){
				printf("密码有误!\n");
				break;
			}
			
			FileOperatInterface(&(p->data.UserFileList));

			return ;
		case '3':
			return ;

		default:
			printf("选择项输入错误，重新选择！\n");
			break;
		}
		system("pause");
	}

	return 0;
}