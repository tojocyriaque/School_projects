#include <alct.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void begin(){
	printf("Content-Type:text/html \n\n");
}

void fail(){
	printf("<head><meta charset=UTF8 http-equiv='refresh' content='0;url=http://www.authlog.mg/login/signup.html'></head></html>");
}

//get data from post method
int posted(char* user, char* pwd){
	char* slen = getenv("CONTENT_LENGTH");
	char* data = alloc_char1(200);
	int len = 0;

	if(slen==NULL){
		return 0;
	}
	len = atoi(slen);
	fgets(data,len+1,stdin);
	
	sscanf(data, "username=%[^&]&password=%[^&]",user,pwd);

	return 1;	
}

//get data from get method
int got(char* user, char* pwd){
	char* data = getenv("QUERY_STRING");
	if(data==NULL){
		return 0;
	}
	sscanf(data,"username=%[^&]&password=%[^&]",user,pwd);
	return 1;
}

int succeed(char* method, char* u, char* p){
	if(strcmp(method,"get")==0){
		return got(u,p);
	}
	else if(strcmp(method,"post")==0){
		return posted(u,p);
	}
	printf("Unkown method %s\n", method);
	return 0;
}

int userFound(char* u){
	int found = 0;
	char* line = alloc_char1(200);
	char* ul = alloc_char1(200);

	FILE* db = fopen("../files/database","r");
	if(db==NULL){
		return 1;
	}
	while(fgets(line,200,db)!=NULL){
		//J'ai choisi cet algo pour peut-être crypter le mot de passe plus tard
		sscanf(line,"%[^:]",ul);
		if(strcmp(ul,u)==0){
			found = 1;
			break;
		}
	}
	fclose(db);
	return found;
}

void insertUser(char* user, char* pwd){
	FILE* db = fopen("../files/database","a");
	if(db==NULL){
		fail();
		exit(0);
	}
	fprintf(db,"%s:%s:connected\n",user,pwd);
	fclose(db);
}

//Rediriger l'utilisateur vers une page d'accueil
void redirectToHome(char* user){
	printf("<html><head><meta http-equiv='refresh' content='0;url=http://www.authlog.mg/scripts/home.cgi?user=%s'></head></html>",user);
}

//generate the script for this user
void makeScript(){
	char* method = "post";
	char* user = alloc_char1(50);
	char* pwd = alloc_char1(50);
	
	begin();
	if (succeed(method, user, pwd)==1){
		if(userFound(user)==0){
			insertUser(user,pwd);	
			redirectToHome(user);		
		}
		else{
			printf("username already used");
			//fail();
		}
	}
	else{
		printf("invalid form method invalid data");
		//fail();
	}
}



