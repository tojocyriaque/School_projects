#ifndef __print_normal__
#define __print_normal__

#include <splitstr.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <trad_date.h> 

void error_alarm(char* text){
    printf("<FONT color='red'><P>%s</P></FONT>", text);
}

int authenticated(){
    int aut = 1; 
    int count = 0;
    int nl=1;

    char* ul = alloc_char1(50);
    char* unl = alloc_char1(50);
    char* line = alloc_char1(50);
    FILE* uf = fopen("files/logs.txt","r");
    if(uf==NULL){
    	printf("No logs file!");
	exit(1);
    }
    while(fgets(ul,50,uf)!=NULL);
    fclose(uf);

    sscanf(ul,"%[^\n]",ul);
    strcpy(unl,ul);

    strcat(ul,"=l");
    strcat(unl,"=nl");

    FILE* mf = fopen("files/marqueur.txt","r");
    if(mf==NULL){
    	printf("No markers file");
	exit(1);
    }
    while(fgets(line,50,mf)!=NULL){
    	if(strstr(line,ul)!=NULL){
		nl=0;
	}else if(strstr(line,unl)!=NULL){
		nl=1;
	}
	count++;
    }
    fclose(mf);
    //eto zany signin no ataony
    if(nl==1 && count==0){
    	aut=1;
    }
    //eto le tode url
    if(nl==1 && count>0){
    	aut=0;
    }
    //eto izy efa logged sady efa afaka mampiasa
    if(nl==0 && count==1){
    	aut=1;
    }
    return aut;
}

void add_disconnect_btn(){
    printf("<FORM class='disconnect' method='get' action='http://www.users.mg/scripts/logout.cgi'>");
    printf("<div>");
    printf("<input type='submit' name='logout'>");
    printf("</div>");
    printf("</FORM>");
}

char* strLower(char* s){
    char* ls = alloc_char1(strlen(s));
    for(int i=0; i<(int)strlen(s); i++){
        ls[i] = tolower(s[i]);
    }
    return ls;
}

void print_users_table_from(char* filename, int scrl){
    FILE* f = fopen(filename, "r");
    char* user = alloc_char1(2000);
    char* s = alloc_char1(5000);
    int count = 0;

    if(f==NULL){
        printf("Impossible d'ouvrir le fichier users_table");
        exit(0);
    }
    
    printf("<TD>");
    printf("<h1>User</h1><HR>");
    printf("<TABLE class=\"users_col\" >");
    
    while(fgets(s, 5000, f) != NULL){

        if( strstr(s, "pam_unix") != NULL ){
            if( strstr(s, " opened for user ") != NULL ){
                user = alloc_char1(200);
                user  = split(s, " user ")[1];
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
        count++;
        if(count<=scrl){
            printf("<TR><H5 class=\"user\" >%s<form action=\"searchUser.cgi\" method=\"get\" ><input type=\"submit\" class=\"user_submit\" value=\"%s\" name=\"user\" ></form></H5></TR>", user, user);
        }
    }

    printf("</TABLE>");
    printf("</TD>");

    fclose(f);
}

void print_dates_table_from(char* filename, int scrl){

    FILE* f = fopen(filename, "r");
    if(f==NULL){
        printf("Impossible d'ouvrir le fichier dates_table");
        exit(0);
    }
    char* date = alloc_char1(200);
    char* line = alloc_char1(200);
    int count = 0;
    int closed_by = 0;

    printf("<TD>");
    printf("<h1>Date</h1><HR>");
    printf("<TABLE class=\"dates_col\" >");

    while(fgets(line, 200, f) != NULL){
        char** spl = split(line, " ");
        sprintf(date, "%s %s %s %s %s %s %s", spl[0], spl[1], spl[2], spl[3], spl[4], spl[5], spl[6]);
        date = date_mlg_from_bash(date);
        count++;
        if(count<=scrl){
            printf("<TR><H5 class=\"date\" >%s<form class=\"date_form\" ><input type=\"submit\" class=\"date_submit\" value=\"%s\" name=\"date\" ></form></H5></TR>", date, date);
        }
    }

    printf("</TABLE>");
    printf("</TD>");

    fclose(f);

}

void print_sessions_state_table_from(char* filename, int scrl, int* count){
    FILE* f = fopen(filename, "r");
    if(f==NULL){
        printf("Impossible d'ouvrir le fichier sessions_table");
        exit(0);
    }
    char* state = alloc_char1(5000);
    char* s = alloc_char1(5000);

    *count = 0;
    printf("<TD>");
    printf("<h1>Session</h1><HR>");
    printf("<TABLE class=\"sessions_col\" >");
    int num = 0;
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
        if(num<=scrl){
            printf("<TR><H5 class=\"session_%s\" >%s<form class=\"session_form\" ><input type=\"submit\" class=\"session_submit\" value=\"%s\" name=\"session\" ></form></H5></TR>",state, state, state);
        }
        (*count)++;
    }

    printf("</TABLE>");
    printf("</TD>");

    fclose(f);
}

void print_page_nums(int num, char* href){
    printf("<div class=\"pages_container\" >");
    printf("<form class=\"pages\" action=\"%s\" method=\"get\" >", href);

    printf("<input type=\"text\" value=\"%d\" name=\"total\" style=\"display:none;position:absolute;top:0;left:0;\" >", num);
    
    for(int i=1; i<=num; i++){
        if(i>=1 && i<=3){
            printf("<input type=\"submit\" name=\"page\" value=\"%d\" class=\"page_n\" >", i);
        }
    }
    printf("</form>");
    printf("</div>");
}

void print_search_bar(){
    printf("<form action=\"searchUser.cgi\" method=\"get\" class=\"search_form\" >\
        <input type=\"search\" name=\"user\" class=\"search_bar\" placeholder=\"search user \">\
        <div>\
        <input type='submit' class='search_btn' name='' value='search'>\
        </div>\
    </form>"
    );
}

void print_title(){
    printf("<H1>Users authentifications log</H1><HR>");
}

void print_style(){
    char* line = alloc_char1(200);
    FILE* style_f = fopen("/home/tojo/Documents/CGI/users/scripts/files/style.css", "r");

    printf("<STYLE>");
    if(style_f==NULL){
        printf("</STYLE>");
        exit(0);
    }

    while ( fgets(line, 200, style_f) != NULL ){
        printf("%s", line);
    }
    printf("</STYLE>");
    fclose(style_f);
}

#endif
