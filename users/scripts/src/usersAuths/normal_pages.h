#ifndef __NORMAL_PAGES_H__
#define __NORMAL_PAGES_H__

#include "print_normal.h"

void print_users_with_page(char* filename, int pn, int scrl){
    
    char* s = alloc_char1(200);
    char* user = alloc_char1(200);
    int begin = (pn-1)*scrl;
    int end = pn*scrl;
    int num=0;

    FILE* f = fopen(filename, "r");
    if(f==NULL){
        printf("Impossible d'ouvrir le fichier");
        exit(0);
    }
    printf("<TD><H1>User</H1><HR><TABLE class=\"users_col\" >");

    while(fgets(s, 200, f) != NULL){
        if( strstr(s, "pam_unix") != NULL ){
            if( strstr(s, " opened for user ") != NULL ){
                user = split(s, " user ")[1];
                user = split(user, "(uid")[0];
            }
            else{
                user = split(s, " closed for user ")[1];
                user = split(user, "\n")[0];
            }
        }
        else{
            user = split(s, "(to ")[1];
            user = split(user, " ")[1];
        }
        num++;
        if(num>begin && num<=end){
            printf("<TR><H5 class=\"user\" >%s<form action=\"searchUser.cgi\" method=\"get\" ><input type=\"submit\" class=\"user_submit\" value=\"%s\" name=\"user\" ></form></H5></TR>", user, user);
        }
    }

    printf("</TABLE></TD>");
    fclose(f);
}

void print_date_with_page(char* filename, int pn, int scrl){
    printf("<TD>");
    printf("<h1>Date</h1><HR>");
    printf("<TABLE class=\"dates_col\" >");

    FILE* f = fopen(filename, "r");

    char* date = alloc_char1(200);
    char* line = alloc_char1(200);
    
    int begin = (pn-1)*scrl;
    int end = pn*scrl;
    int num=0;

    while(fgets(line, 200, f) != NULL){
        char** spl = split(line, " ");
        sprintf(date, "%s %s %s %s %s %s %s", spl[0], spl[1], spl[2], spl[3], spl[4], spl[5], spl[6]);
        date = date_mlg_from_bash(date);
        num++;
        if(num>begin && num<=end){
            printf("<TR><H5 class=\"date\" >%s<form class=\"date_form\" ><input type=\"submit\" class=\"date_submit\" value=\"%s\" name=\"date\" ></form></H5></TR>", date, date);
        }
    }

    printf("</TABLE>");
    printf("</TD>");

    fclose(f);
}

void print_sessions_with_page(char* filename, int pn, int scrl){
    FILE* f = fopen(filename, "r");
    char* state = alloc_char1(5000);
    char* s = alloc_char1(5000);

    int begin = (pn-1)*scrl;
    int end = pn*scrl;
    int num=0;

    printf("<TD>");
    printf("<h1>Session</h1><HR>");
    printf("<TABLE class=\"sessions_col\" >");

    while(fgets(s, 5000, f) != NULL){

        if( strstr(s, "pam_unix") != NULL ){
            if( strstr(s, " opened for user ") != NULL ){
                state = "opened";
            }
            else{
                state = "closed";
            }
        }
        else{
            state = "closed";
        }

        num++;
        if(num>begin && num<=end){
            printf("<TR><H5 class=\"session_%s\" >%s<form class=\"session_form\" ><input type=\"submit\" class=\"session_submit\" value=\"%s\" name=\"session\" ></form></H5></TR>",state, state, state);
        }
    }

    printf("</TABLE>");
    printf("</TD>");
}

void print_with_page(int pn, int scrl, char* filename){
    print_date_with_page(filename, pn, scrl);
    print_users_with_page(filename, pn, scrl);
    print_sessions_with_page(filename, pn, scrl);
}

void print_page_num_with_n(int num, char* href, int n){
    int start = 0;
    int end = 0;
    if(n%3==0){
        if(n<num){
            start = n+1;
        }
        else if(n==num){
            start = n-2;
        }
    }
    else if(n%3==1){
        start = n-3;
        if(start<=0){
            start=1;
        }
    }
    else{
        start = n-1;
    }
    end=start+2;
    
    printf("<div class=\"pages_container\" >");
    printf("<form class=\"pages\" action=\"%s\" method=\"get\" >", href);

    printf("<input type=\"text\" value=\"%d\" name=\"total\" style=\"display:none;position:absolute;top:0;left:0;\" >", num);
    
    for(int i=1; i<=num; i++){
        if(i>=start && i<=end){
            printf("<input type=\"submit\" name=\"page\" value=\"%d\" class=\"page_n\" >", i);
        }
    }
    printf("</form>");
    printf("</div>");
}

void print_head(){
    printf("Content-Type:text/html \n\n");
    printf("<head>");
    printf("<meta charset=UTF8>");
    print_style();
    printf("<title>Auths page</title>");
    printf("</head>");
}

void print_body(){

    char* filename = "files/auths.txt";
    char* data = getenv("QUERY_STRING");

    if(data==NULL){
        printf("<font color=\"red\" ><p>No data from get method</p></font>");
        exit(0);
    }

    char* total_str = split(data, "&")[0];
    int total = atoi(split(total_str, "=")[1]);

    char* pn_str = split(data, "&")[1];
    int pn = atoi(split(pn_str, "=")[1]);
    int scrl = 10;


    print_title();

    printf("<body>");
    print_search_bar();
    printf("<TABLE class=\"big_table\" >");
    print_with_page(pn, scrl, filename);
    printf("</TABLE>");
    print_page_num_with_n(total, "normal_pages.cgi", pn);
    add_disconnect_btn();
    
    printf("</body>");

}

void print_foot(){
    printf("</html>");
}


#endif