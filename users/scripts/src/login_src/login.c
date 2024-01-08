#include "prototypes.h"

int main(){
    char* database = "files/database.txt";
    begin_cgi();
    register_to_db(database);
    return 0;
}