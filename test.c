#include <stdio.h>
#include <string.h>
#include "simpleSort.h"

void getData(char **data,char *filename);
void visitSList(int a);

int main(int argc,char *argv[]){
	if(argc >= 2){
		char *data = NULL;

		getData(&data,argv[2]);
		if( data ){
			if( strcmp(argv[1],"-sa")==0 ){
				SqList sqarr = {NULL,0};
				InitSqList(&sqarr, data);
				printf("before sort:");
				VisitSqList(sqarr, visitSList);
				SortSqList(&sqarr);
				printf("\nafter sort:");
				VisitSqList(sqarr, visitSList);
				printf("\n");
			}else if( strcmp(argv[1],"-ba")==0 ){
				SqList sqarr = {NULL,0};
                InitSqList(&sqarr, data);
                printf("before sort:");
                VisitSqList(sqarr, visitSList);
                BInsertSort(&sqarr);
                printf("\nafter sort:");
                VisitSqList(sqarr, visitSList);
                printf("\n");

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

void visitSList(int a){
	printf("%4d", a);
}
