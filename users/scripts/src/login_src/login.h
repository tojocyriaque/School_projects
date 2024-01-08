#ifndef __LOGIN__
#define __LOGIN__

#include "signin.h"
#include "signup.h"
#include "splitstr.h"

void add_authentification(char* username){
    char* mkf = "files/marqueur.txt";
   
    FILE* mf = fopen(mkf, "a+");
    FILE* lf = fopen("files/logs.txt", "a+");
    
    fprintf(mf,"%s=l\n", username);
    fprintf(lf, "%s\n", username);

    fclose(mf);
    fclose(lf);
}

void disconnect(char* username){
    char* uname = alloc_char1(200);
    strcpy(uname, username);
    char* marqueur = "files/marqueur.txt";
    
    FILE* lf = fopen("files/logs.txt", "r");
    while( fgets(uname, 200, lf)!=NULL);
    fclose(lf);

    FILE* mq = fopen(marqueur, "a");
    if(mq==NULL){
        printf("No marker file!");
        exit(0);
    }
    uname = split(uname, "\n")[0];
    strcat(uname, "=nl\n");
    fprintf(mq, "%s", uname);
    fclose(mq);
}

int register_to_db(char* database){
    int success = 0;
    int len = 0;
    char* data = alloc_char1(1000);
    char* username = alloc_char1(200);
    char* password = alloc_char1(200);
    char* action = alloc_char1(100);
    char* len_str = getenv("CONTENT_LENGTH");
    char* welcome_msg = alloc_char1(200);
    
    if(len_str==NULL){
        error_alarm("Please fill all entries correctly!");
        exit(0);
    }
    
    len=atoi(len_str)+1;
    fscanf(stdin, "username=%[^&]&password=%[^&]&action=%[^&]", username, password, action);

    if( strcmp(action, "signin") == 0 ){
        success = sign_in(database, username, password);
    }
    else{
        success = sign_up(database, username, password);
    }
    if(success==0){
        add_authentification(username);
        //printf("hello");
        printf("<html><head><meta http-equiv='refresh' content='0;url=usersAuth.cgi'></head></html>\n");
    }
    return success;
}

#endif
