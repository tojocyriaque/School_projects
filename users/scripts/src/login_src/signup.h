#ifndef __SIGNUP__
#define __SIGNUP__

#include "includes.h"

int append_user(char* database, char* username, char* password){
    FILE* db = fopen(database, "a");
    if(db==NULL){
        error_alarm("Database not found ! ");
        exit(0);
    }
    
    fprintf(db, "\nusername=%s;password=%s", username, password);

    fclose(db);
    return 0;
}

int sign_up(char* database, char* username, char* password){
    int no_user = 0; // 0 si le nom d'utilisateur existe déjà sinon 1
    char* line = alloc_char1(400);
    char* uname = alloc_char1(200);
    char* pwd = alloc_char1(200);

    FILE* df = fopen(database, "r");
    if(df==NULL){
        error_alarm("Database not found!");
        exit(0);
    }
    while( fgets(line, 400, df)!=NULL ){
        sscanf(line, "username=%[^;];password=%s", uname, pwd);

        if( strcmp(uname, username)==0){
            no_user = 1;
            break;
        }

    }
    
    fclose(df);

    if(no_user==0){
        append_user(database, username, password);
    }
    else{
        error_alarm("User already exists!");
    }

    return no_user;
}

#endif