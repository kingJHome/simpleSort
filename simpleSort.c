#include "simpleSort.h"

int getDataNum(char *elems){
	int sqlen = 0;
	size_t elen = strlen(elems);

	for(size_t i = 0; i < elen; ++i){
		if( elems[i]==' ' || elems[i]=='\n' ){
			++sqlen;
		}
	}

	return sqlen;
}

void setSqListData(void *target,char *data,int pos){
	int *arr = (int*)target,
		curData = atoi(data);

	arr[pos+1] = curData;
}

void setLinkData(void *target,char *data,int pos){
	int curData = atoi(data);
	elemLink *header = (elemLink*)target,
			 *insertData = (elemLink*)malloc(sizeof(elemLink)),
			 *curLink = header;

	if( insertData ){
		insertData->key = curData;
		insertData->next = NULL;

		for(int i = 0; i < pos; ++i,curLink = curLink->next);
		curLink->next = insertData;
	}
}

void visitAndSetData(char *source,char *seperator,void *array,setArrayData setFn){
	int pos = 0;
	char *delim = NULL;

	delim = strtok(source, seperator);
	if( delim ){
		setFn(array, delim, pos++);
		while( delim = strtok(NULL, seperator) ){
			setFn(array, delim, pos++);
		}
	}
}

//初始化线性列表
void InitSqList(SqList *sq,char *elems){
	int sqlen = getDataNum(elems);

	sq->elemArray = (int*)malloc((sqlen+1) * sizeof(int));
	if( sq->elemArray ){
		sq->length = sqlen + 1;
		visitAndSetData(elems," \n",sq->elemArray,setSqListData);
	}
}

//排序线性表(插入排序)
void SortSqList(SqList *sq){
	for(int i = 1; i < sq->length - 1; ++i){
		sq->elemArray[0] = sq->elemArray[i];
		for(int j = i + 1; j < sq->length; ++j){
			if( sq->elemArray[j] < sq->elemArray[0] ){
				int temp = sq->elemArray[0];
				sq->elemArray[0] = sq->elemArray[j];
				sq->elemArray[j] = temp;
			}
		}
		sq->elemArray[i] = sq->elemArray[0];
	}
}

//折半插入排序
void BInsertSort(SqList *sq){
	for(int i = 2; i < sq->length; ++i){
		sq->elemArray[0] = sq->elemArray[i];
		int low = 1,high = i - 1;

		while( low <= high ){
			int mid = (low + high) / 2;

			if( LT(sq->elemArray[0],sq->elemArray[mid]) ){
				high = mid - 1;
			}else{
				low = mid + 1;
			}
		}

		for(int j = i - 1; j >= high + 1; --j){
			sq->elemArray[j+1] = sq->elemArray[j];
		}
		sq->elemArray[high+1] = sq->elemArray[0];
	}
}

//二路查找排序
void TwoPartInsertSort(SqList *sq){
	int sqlen = sq->length - 1,
		first = 0,last = 0,
		*helpArray = (int*)malloc(sqlen * sizeof(int));
	
	helpArray[0] = sq->elemArray[1];

	for(int i = 2; i < sq->length; ++i){
		if( LT(sq->elemArray[i], helpArray[first]) ){
			if( first==0 ){
				first = sqlen - 1;
			}else{
				first -= 1;
			}
			helpArray[first] = sq->elemArray[i];
		}else if( GT(sq->elemArray[i], helpArray[last]) ){
			helpArray[++last] = sq->elemArray[i];
		}else{//在最大值与最小值之间
			if( LT(sq->elemArray[i], helpArray[0]) ){
				for(int j = first; j <= sqlen; ++j){
					if( j!=sqlen && GT(sq->elemArray[i], helpArray[j]) ){
						helpArray[j-1] = helpArray[j];
					}else{
						helpArray[j-1] = sq->elemArray[i];
						break;
					}
				}
				--first;
			}else{
				for(int j = last; j >= 0; --j){
					if( j>0 && LT(sq->elemArray[i], helpArray[j]) ){
						helpArray[j+1] = helpArray[j];
					}else{
						helpArray[j+1] = sq->elemArray[i];
						break;
					}
				}
				++last;
			}
		}
	}

	//重排有序列表
	int cur = 1;
	for(int j = first; j != last; j = (j+1)%sqlen,++cur){
		sq->elemArray[cur] = helpArray[j];
	}
	sq->elemArray[cur] = helpArray[last];
}

//访问sqlist
void VisitSqList(SqList sq,visitSqList vsq){
	for(int i = 1; i < sq.length; ++i){
		vsq(sq.elemArray[i]);
	}
}

//初始化线性链表
void InitElemLink(elemLink *header,char *elems){
	visitAndSetData(elems," \n",header,setLinkData);
}

//排序线性链表
void SortElemLink(elemLink *header){

}
