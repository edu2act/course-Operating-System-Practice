#ifndef _FileManage_h_
#define _FileManage_h_

#include "List.h"

//文件操作界面
void FileOperatInterface(LinkList_U *pUfd);

//创建文件或文件夹
Status CreateFile(LinkList_U  *pUfd ,char *fileName);

//显示当前文件夹下所有文件
void VisitFile(LinkList_U  Ufd);   

//打开文件或文件夹
Status OpenFile(LinkList_U  Ufd ,char *fileName);   


//删除文件或文件夹
Status Delete(LinkList_U  *pUfd ,char *fileName); 

//向文件写入内容
Status AddContent(LinkList_U  *pUfd ,char *fileName); 







#endif