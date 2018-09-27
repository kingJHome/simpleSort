#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleSort.h"

void getData(char **data,char *filename);
int* getIntArray(char *data,int *num);
void visitSList(int a);
void visitArray(int *array,int len);

int main(int argc,char *argv[]){
	if(argc >= 2){
		char *data = NULL;

		getData(&data,argv[2]);
		if( data ){
			if( strchr(argv[1],'a') ){
				SqList sqarr = {NULL,0};
				InitSqList(&sqarr, data);			
				printf("before sort:");
                VisitSqList(sqarr, visitSList);
				if( strcmp(argv[1],"-sa")==0 ){
					SortSqList(&sqarr);
				}else if( strcmp(argv[1],"-ba")==0 ){
                	BInsertSort(&sqarr);
				}else if( strcmp(argv[1],"-ta")==0 ){
					TwoPartInsertSort(&sqarr);
				}
				printf("\nafter sort:");
                VisitSqList(sqarr, visitSList);
                printf("\n");
			}else if( strcmp(argv[1],"-stt")==0 ){
				int alen = 0,
					*array = getIntArray(data, &alen);
				SLinkList sortArr = {NULL,alen+1};
				
				sortArr.array = (BLNode*)malloc((alen+1) * sizeof(BLNode));
				if( alen && array && sortArr.array ){
					printf("before sort:");
					visitArray(array, alen);
					TableInsertSort(&sortArr, array, alen);
					Arrange(&sortArr);
					printf("after sort:");
					visitTableList(sortArr,visitSList);
					printf("\n");
				}
			}
		}
	}

	return 0;
}

void getData(char **data,char *filename){
	FILE *fp = NULL;
	size_t getnum = 0;

	if( filename ){
		fp = fopen(filename,"r");
	}else{
		fp = fopen("testData.txt","r");
	}

	if( fp && getline(data, &getnum, fp)!=-1 ){
		fclose(fp);
	}
}

int* getIntArray(char *data,int *len){
	char *sepe = NULL,
		 seperator[] = " \n";
	size_t dlen = strlen(data);
	int *result = NULL;

	*len = 0;
	for(size_t i = 0; i < dlen; ++i){
		if(data[i]==' ' || data[i]=='\n'){
			++(*len);
		}
	}
	
	result = (int*)malloc((*len) * sizeof(int));
	if( result ){
		sepe = strtok(data, seperator);
		if( sepe ){
			int curPos = 0;
			result[curPos++] = atoi(sepe);
			while( sepe = strtok(NULL, seperator) ){
				result[curPos++] = atoi(sepe);
			}
		}
	}

	return result;
}

void visitSList(int a){
	printf("%4d", a);
}

void visitArray(int *array,int len){
	for(int i = 0; i < len; ++i){
		printf("%4d", array[i]);
	}
	printf("\n");
}
