#include "login.h"

int main(){
    char* data = getenv("QUERY_STRING");
    char* username = alloc_char1(200);

    printf("Content-Type:text/html \n\n");
    if(data==NULL){
        printf("Faild to statisfy the request!");
        exit(0);
    }
    disconnect(username);
    printf("<HTML><HEAD><META http-equiv='refresh' content='0;url=../index.html' ></HEAD></HTML>");

    return 0;
}