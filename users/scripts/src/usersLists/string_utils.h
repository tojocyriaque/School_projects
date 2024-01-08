#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char** allouer_char_2D(int row, int col){
	char** arr = (char**) malloc(row*sizeof(char*));
	for(int i=0; i<row; i++){
		*(arr+i) = (char*) malloc(col);
	}
	return arr;
}

char** split(char* str, char sep){
	char** spl0 = allouer_char_2D(100, 50);
	int index=0;
	for(int i=0; i<strlen(str); i++){
		if(str[i]!=sep){
			char* s = (char*) malloc(2);
			sprintf(s,"%c",str[i]);
			strcat(spl0[index], s);
		}else{
			index++;
		}
	}
	spl0[index+1]=NULL;
	return spl0;
}
