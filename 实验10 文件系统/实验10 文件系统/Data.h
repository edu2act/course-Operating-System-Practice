#ifndef _Data_h_
#define _Data_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true				1
#define false				0
#define PCBType				PCB
#define Status				int
#define OK					1
#define	ERROR				0
#define	MAX_NAME_SIZE		20
#define	MAX_CONTENT_SIZE	50
#define LinkList_R		RootList
#define LinkList_U		UFDList

#define ElemType_R		RootDirData
#define ElemType_U		UserDirData

#define RNode			RootDirNode
#define UNode			UserNode


typedef struct FCB
{
	char FileName[MAX_NAME_SIZE];		//文件名
	char Content[MAX_CONTENT_SIZE];		//文件内容
}FCB;

typedef struct UserDirData				//用户目录中的一个data域
{
	char FileName[MAX_NAME_SIZE];		//文件名
	FCB *FileAddress;		
}UserDirData;

typedef struct UserNode					//用户结点
{
	UserDirData data;					
	struct UserNode *Next;		
}UserNode, *UFDList;					//UFD用户文件目录

typedef struct RootDirData				//根目录中的一个data域
{
	char UserName[MAX_NAME_SIZE];		//用户名
	char UserPWD[MAX_NAME_SIZE];		//密码
	UFDList UserFileList;				//用户文件目录
}RootDirData ;							

typedef struct RootDirNode				//根目录结点
{
	RootDirData data;					
	struct RootDirNode *Next;		
}RootDirNode, *RootList, *MFD;			//Root根,  MFD


#endif 
