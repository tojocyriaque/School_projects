#include "search.h"

int main(){
    //si il  n'y a eu aucune authentification
    if(authenticated() == 0){
        printf("Content-Type:text/html \n\n");
        printf("<html><head><meta http-equiv='refresh' content='0;url=../index.html'></head></html>\n");
    }
    else{
    	print_head();
    	print_body();
    	print_foot();
    }
    return 0;
}
