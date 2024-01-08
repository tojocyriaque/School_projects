#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "print_normal.h"

//infos sur un seul utilisateurs
void uniq_user(char* uname, char* in_f, int scr){
    FILE* input = fopen(in_f, "r");
    
    printf("<TD>");
    printf("<h1>User</h1><HR>");
    printf("<TABLE class=\"users_col\" >");

    char* user = alloc_char1(200);
    char* in_line = alloc_char1(200);
    int count = 0;

    while( fgets(in_line, 200, input) != NULL ){

        if( strstr(in_line, "pam_unix") != NULL ){
            if( strstr(in_line, " opened for user ") != NULL ){
                user = split(in_line, " user ")[1];
                user = split(user, "(uid")[0];
            }
            else{
                user = split(in_line, " closed for user ")[1];
                user = split(user, "\n")[0];
            }
        }
        else{
            user = split(in_line, "(to ")[1];
            user = split(user, " ")[1];
        }

        if(strstr(user, uname)!=NULL && count<=scr){
            count++;
            printf("<TR><H5 class=\"user\" >%s<form action=\"searchUser.cgi\" method=\"get\" ><input type=\"submit\" class=\"user_submit\" value=\"%s\" name=\"user\" ></form></H5></TR>", user, user);
        }
        
    }

    printf("</TABLE></TD>");
    fclose(input);
}   

void uniq_date(char* uname, char* in_f, int scr){
    FILE* input = fopen(in_f, "r");
    
    printf("<TD>");
    printf("<h1>Date</h1><HR>");
    printf("<TABLE class=\"dates_col\" >");

    char* user = alloc_char1(200);
    char* in_line = alloc_char1(200);
    char* date  = alloc_char1(200);
    int count = 0;
    while( fgets(in_line, 200, input) != NULL ){

        if( strstr(in_line, "pam_unix") != NULL ){
            if( strstr(in_line, " opened for user ") != NULL ){
                user = split(in_line, " user ")[1];
                user = split(user, "(uid")[0];
            }
            else{
                user = split(in_line, " closed for user ")[1];
                user = split(user, "\n")[0];
            }
        }
        else{
            user = split(in_line, "(to ")[1];
            user = split(user, " ")[1];
        }
        
        if(strstr(user, uname)!=NULL && count<=scr){
            count++;
            char** spl = split(in_line, " ");
            sprintf(date, "%s %s %s %s %s %s %s", spl[0], spl[1], spl[2], spl[3], spl[4], spl[5], spl[6]);
            date = date_mlg_from_bash(date);

            printf("<TR><H5 class=\"date\" >%s<form class=\"date_form\" ><input type=\"submit\" class=\"date_submit\" value=\"%s\" name=\"date\" ></form></H5></TR>", date, date);

        }
        
    }

    printf("</TABLE></TD>");
    fclose(input);
}

void uniq_sessions(char* uname, char* in_f, int* count, int scr){

    *count = 0;

    char* user = alloc_char1(200);
    char* session = alloc_char1(200);
    char* in_line = alloc_char1(200);
    int num = 0;
    
    FILE* input = fopen(in_f, "r");
    
    printf("<TD>");
    printf("<h1>Session</h1><HR>");
    printf("<TABLE class=\"sessions_col\" >");

    while( fgets(in_line, 200, input) != NULL ){

        if( strstr(in_line, "pam_unix") != NULL ){
            if( strstr(in_line, " opened for user ") != NULL ){
                user = split(in_line, " user ")[1];
                user = split(user, "(uid")[0];
                session = "opened";
            }
            else{
                user = split(in_line, " closed for user ")[1];
                user = split(user, "\n")[0];
                session = "closed";
            }
        }
        else{
            user = split(in_line, "(to ")[1];
            user = split(user, " ")[1];
            session = "closed";
        }
        
        if(strstr(user, uname)!=NULL){
            if(num<=scr){
                num++;
                printf("<TR><H5 class=\"session_%s\" >%s<form class=\"session_form\" ><input type=\"submit\" class=\"session_submit\" value=\"%s\" name=\"session\" ></form></H5></TR>",session, session, session);
            }
            (*count)++;
        }
        
    }

    printf("</TABLE></TD>");
    fclose(input);
}

//affichage avec recherche
void search(char* uname, char* in_f, int* count, int scr){
    uniq_date(uname, in_f, scr);
    uniq_user(uname, in_f, scr);
    uniq_sessions(uname, in_f, count, scr);
}

//affichacge normal sans recherche
void nosearch(char* filename, int* count, int scrl){
    print_dates_table_from(filename, scrl);
    print_users_table_from(filename, scrl);
    print_sessions_state_table_from(filename, scrl, count);
}

void print_page_num_with_user(int num, char* href, char* username){
    printf("<div class=\"pages_container\" >");
    printf("<form class=\"pages\" action=\"%s\" method=\"get\" >", href);

    printf("<input type=\"text\" value=\"%d\" name=\"total\" style=\"display:none;position:absolute;top:0;left:0;\" >",  num);
    printf("<input type=\"text\" value=\"%s\" name=\"username\" style=\"display:none;position:absolute;top:0;left:0;\" >", username);

    for(int i=1; i<=num; i++){
        if(i>=1 && i<=3){
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
    printf("<title>Authentification page</title>");
    print_style();
    printf("</head>\n\n");
    printf("<html>\n\n");
}

void print_body(){
    char* filename = "files/auths.txt";
    char* data = getenv("QUERY_STRING");

    if(data==NULL ){
        printf("<font color=\"red\"><p>No data for now</p></font>");
        exit(0);
    }
    char* uname = split(data, "=")[1];
    if( strlen(uname)<1 ){
        uname = "all";
    }
    int count = 0;
    int n_scroll = 10;

    print_title();
    printf("<BODY>");
    print_search_bar();

    printf("<TABLE class=\"big_table\" >");
    
    
    if( strcmp( strLower(uname) , "all")==0 ){
        nosearch(filename, &count, n_scroll);
    } 
    else{
        search(uname, filename, &count, n_scroll);
        if(count == 0){
            printf("<H1 style='font-family: sans-serif; color: red'>No users found</H1>");
        }

    }

    int num = count/n_scroll;

    if(count%n_scroll != 0){
        num++;
    }
    
    printf("</TABLE>");
    print_page_num_with_user(num, "search_pages.cgi", uname);
    add_disconnect_btn();
    printf("</BODY>");
}

void print_foot(){
    printf("\n</html>\n");
}

#endif