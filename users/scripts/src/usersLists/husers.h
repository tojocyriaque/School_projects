#include "string_utils.h"
#include <ctype.h>

typedef struct{
	char* name;
	int id;
	char* home;
	char* shell;
} User;

User to_user(char* str){
	char** spl = split(str,':');
	User Hu;
	
	Hu.name = spl[0];
	Hu.id = atoi(spl[2]);
	Hu.home = spl[5];
	Hu.shell = spl[6];

	return Hu;
}

int is_human(User Usr){
	if(Usr.id>=1000 && strcmp(Usr.name, "nobody")!=0){
		return 1;
	}
	return 0;
}

void printHTML_logins_from(char* filename){
	FILE* file = fopen(filename, "r");
	if(file==NULL){
		printf("Impossible d'ouvrir de fichier %s ", filename);
		exit(1);
	}

	char* line = (char*) malloc(250);

	printf("<td><table><h3>Login</h3><hr>");
	while(fgets(line, 250, file)!=NULL){
		User u;
		char** spl = split(line, ':');
		
		u.name = spl[0];
		u.id = atoi(spl[2]);
		u.home = spl[5];
		u.shell = spl[6];
		
		if(is_human(u)){
			printf("<tr><h4 class=\"login\">%s</h4></tr>", u.name);	
		}

	} 
	printf("</table></td>");
	fclose(file);
}

void printHTML_ids_from(char* filename){
	FILE* file = fopen(filename, "r");
	if(file==NULL){
		printf("Impossible d'ouvrir de fichier %s ", filename);
		exit(1);
	}

	char* line = (char*) malloc(250);
	
	printf("<td><table><h3>ID</h3><hr>");
	while(fgets(line, 250, file)!=NULL){
		User u;
		char** spl = split(line, ':');
		
		u.name = spl[0];
		u.id = atoi(spl[2]);
		u.home = spl[5];
		u.shell = spl[6];
		
		if(is_human(u)){
			printf("<tr class=\"id\"><h4 class=\"id\">%d</h4></tr></tr>", u.id);	
		}

	} 
	printf("</table></td>\n");
	fclose(file);
}

void printHTML_homes_from(char* filename){
	FILE* file = fopen(filename, "r");
	if(file==NULL){
		printf("Impossible d'ouvrir de fichier %s ", filename);
		exit(1);
	}

	char* line = (char*) malloc(250);
	
	printf("<td><table><h3>Home</h3><hr>");
	while(fgets(line, 250, file)!=NULL){
		User u;
		char** spl = split(line, ':');
		
		u.name = spl[0];
		u.id = atoi(spl[2]);
		u.home = spl[5];
		u.shell = spl[6];
		
		if(is_human(u)){
			printf("<tr><h4 class=\"home\">%s</h4></tr></tr>", u.home);	
		}

	} 
	printf("</table></td>\n");
	fclose(file);
}

void printHTML_shells_from(char* filename){
	FILE* file = fopen(filename, "r");
	if(file==NULL){
		printf("Impossible d'ouvrir de fichier %s ", filename);
		exit(1);
	}

	char* line = (char*) malloc(250);
	
	printf("<td><table><h3>Shell</h3><hr>");
	while(fgets(line, 250, file)!=NULL){
		User u;
		char** spl = split(line, ':');
		
		u.name = spl[0];
		u.id = atoi(spl[2]);
		u.home = spl[5];
		u.shell = spl[6];
		
		if(is_human(u)){
			printf("<tr><h4 class=\"shell\">%s</h4></tr></tr>", u.shell);	
		}

	} 
	printf("</table></td>\n");
	fclose(file);
}

void print_HTML_husers_table(){
	char filename[50];strcpy(filename, "files/passwd.txt");

	printf("<table>");
	
	printHTML_logins_from(filename);
	printHTML_ids_from(filename);
	printHTML_homes_from(filename);
	printHTML_shells_from(filename);

	printf("</table>\n");
}

