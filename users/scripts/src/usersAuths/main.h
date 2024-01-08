#ifndef __MAIN_H__
#define __MAIN_H__

#include "print_normal.h"
#include "insert_auths.h"

void print_head(){
    printf("Content-Type:text/html \n\n");
    printf("<html>\n\n");
    printf("<head>");
    printf("<meta charset=UTF8>");
    printf("<title>Authentification page</title>");
    print_style();
    printf("</head>\n\n");
}

void print_body(){
    char* filename = "files/auths.txt";
    int count = 0;
    int n_scrl = 10;

    print_title();

    printf("<body>");
    print_search_bar();
    printf("<TABLE class=\"big_table\" >");

    print_dates_table_from(filename, n_scrl);
    print_users_table_from(filename, n_scrl);
    print_sessions_state_table_from(filename, n_scrl, &count);

    int num = count/n_scrl;

    if(count%n_scrl != 0){
        num++;
    }

    printf("</TABLE>");
    print_page_nums(num, "normal_pages.cgi");
    add_disconnect_btn();
    printf("</body>");
}

void print_foot(){
    printf("\n</html>\n");
}

#endif