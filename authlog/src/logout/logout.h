#include <alct.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void writeLogs(char* user){
	char* u = alloc_char1(200);
	char* p = alloc_char1(200);
	char* s = alloc_char1(200);

	char* l = alloc_char1(200);
	FILE* db = fopen("../files/database","r");
	if(db==NULL){
		printf("db==NULL (1)");exit(0);
	}
	FILE* tdb = fopen("../files/tdatabase","w+");
	if(tdb==NULL){
		printf("td==NULL (1)");exit(0);
	}

	while(fgets(l,200,db)!=NULL){
		sscanf(l,"%[^:]:%[^:]:%s",u,p,s);
		if(strcmp(u,user)==0){
			fprintf(tdb,"%s:%s:disconnected\n",u,p);
		}
		else if(strcmp(l,"\n")!=0){
			fprintf(tdb,"%s",l);
		}
	}
	fclose(db);
	fclose(tdb);

	db = fopen("../files/database","w+");
	if(db==NULL){
		printf("db==NULL (2)");exit(0);
	}
	tdb = fopen("../files/tdatabase","r");
	if(tdb==NULL){
		printf("tdb==NULL (2)");exit(0);
	}

	while(fgets(l,200,tdb)!=NULL){
		sscanf(l,"%[^\n]",l);
		fprintf(db,"%s\n",l);
	}
	fclose(db);
	fclose(tdb);

}

void disconnect(char* user){
	printf("Content-Type:text/html \n\n");
	writeLogs(user);
}

void redirectToHome(char* user){
	printf("Content-Type:text/html \n\n");
	printf("<html><head><meta http-equiv='refresh' content='0;url=http://www.authlog.mg/index.html'></head></html>");
}

void logout(){
	char* user = getenv("QUERY_STRING");
	if(user==NULL){
		exit(0);
	}
	sscanf(user,"user=%s",user);
	disconnect(user);
	redirectToHome(user);
}



