#ifndef _MY_SIMPLE_SORT
#define _MY_SIMPLE_SORT

#include <stdlib.h>
#include <string.h>

#define LT(a,b) ((a) < (b))
#define LQ(a,b) ((a) <= (b))
#define GT(a,b) ((a) > (b))
#define GQ(a,b) ((a) >= (b))

typedef void (*visitSqList)(int a);
typedef void (*setArrayData)(void *target,char *data,int pos);

typedef struct{
	int *elemArray;
	int length;
}SqList;

typedef struct{
	int data;
	int next;
}BLNode;

typedef struct{
	BLNode *array;
	int length;
}SLinkList;

typedef struct elemLink{
	int key;
	struct elemLink *next;
}elemLink;

//初始化线性列表
void InitSqList(SqList *sq,char *elems);

//排序线性表(插入排序)
void SortSqList(SqList *sq);

//折半插入排序
void BInsertSort(SqList *sq);

//二路查找排序
void TwoPartInsertSort(SqList *sq);

//访问sqlist
void VisitSqList(SqList sq,visitSqList vsq);

//表插入排序
void TableInsertSort(SLinkList *sll,int *arr,int len);

//表位置调整
void Arrange(SLinkList *sll);

//访问表
void visitTableList(SLinkList sll,visitSqList vst);

//初始化线性链表
void InitElemLink(elemLink *header,char *elems);

//排序线性链表
void SortElemLink(elemLink *header);

#endif
