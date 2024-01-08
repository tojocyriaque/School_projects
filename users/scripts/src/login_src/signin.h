#ifndef __SIGNIN__
#define __SIGNIN__

#include "includes.h"

int user_already_authenticated(char* username){
    char* s = alloc_char1(200);
    char* ulg = alloc_char1(200);
    char* nulg = alloc_char1(200);
    int count = 0;
    int val = 0;

    sprintf(ulg, "%s=l", username);
    sprintf(nulg, "%s=nl", username);

    //printf("%s\t%s",ulg,nulg);exit(1);

    FILE* af = fopen("files/marqueur.txt", "a+");
    while (fgets(s, 200, af) != NULL){
        if(strstr(s, ulg)!=NULL){
            val = 1;
        }
        else if (strstr(s, nulg)!=NULL){
            val = 0;
        }
	count++;
    }
    fclose(af);
    return val;
}

int sign_in(char* database, char* username, char* password){
    int correct = 1;
    int user_in = 0;
    char* line = alloc_char1(400);
    char* uname = alloc_char1(200);
    char* pwd = alloc_char1(200);
    
    FILE* logs = fopen("files/logs.txt","a");
    FILE* df = fopen(database, "r");
    if(df==NULL){
        error_alarm("Database not found!");
        exit(0);
    }
    
    while( fgets(line, 400, df)!=NULL ){
        sscanf(line, "username=%[^;];password=%s",  uname, pwd);
        if( strcmp(uname, username)==0 ){
            if( strcmp(pwd, password)==0 ){
                correct = 0;
                if(user_already_authenticated(uname)==1){
                    correct = 1;
                }
                break;
            }
            else{
		fprintf(logs,"%s\n",uname);
		printf("<html><head><meta http-equiv='refresh' meta content='0;url=usersAuth.cgi'></head></html>\n");
            	printf("wrong password");
	    }
            user_in = 1;
        }
        
    }
    if(user_in==0 && correct==1){
       printf("<html><head><meta http-equiv='refresh' content='0;url=../index.html'></head></html>\n");
    }

    fclose(df);
    fclose(logs);
    return correct;
}

#endif
