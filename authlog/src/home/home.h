#include <stdio.h>
#include <alct.h>
#include <string.h>

//Début du script
void begin(){
	printf("Content-Type:text/html \n\n");
	printf("<html>");
}

void style(){
	char* l = alloc_char1(5000);
	FILE* ss = fopen("/home/tojo/Documents/CGI/authlog/styles/home.css","r");
	if(ss==NULL){
		printf("stylesheet inacessible!");exit(1);
	}
	printf("<style>");
	while(fgets(l,300,ss)!=NULL){
		printf("%s\n",l);
	}
	printf("</style>");
	fclose(ss);
}

void welcome(char* user){
	printf("<section class='welcome'>");
	printf("<h1>Tongasoa %s</h1>",user);
	printf("</section>");
}

void head(){
	printf("<head>");
	printf("<meta charset=UTF8>");
	//style();
	printf("<link rel='stylesheet' href='../styles/home.css'>");
	printf("<title>Welcome page</title>");
	printf("</head>");
}

int userConnected(char* user){
	char* state = alloc_char1(100);
	char* u = alloc_char1(100);
	char* pwd = alloc_char1(100);
	char* line = alloc_char1(200);

	FILE* db = fopen("../files/database","r");
	while( fgets(line,200,db)!=NULL){
		sscanf(line,"%[^:]:%[^:]:%s", u, pwd, state);
		if(strcmp(u,user)==0){
			if(strcmp(state,"disconnected")==0){
				fclose(db);
				return 0;
			}
		}
	}
	fclose(db);
	return 1;
}

void logoutBtn(char* user){
	printf("<a class='logout' href='http://www.authlog.mg/scripts/logout.cgi?user=%s'>\
		<input type='button' value='hivoaka'>\
		</a>",user);
}

void showBtn(char* user){
	printf("<a class='show' href='http://www.authlog.mg/scripts/nosearch.cgi?user=%s&page=1'>\
		<input type='button' value='hijery'>\
		</a>",user);
}

void body(){
	char* user = getenv("QUERY_STRING");
	if(user==NULL || strcmp(user,"user=")==0){
	 	exit(0);	
	}
	else{
		sscanf(user,"user=%s",user);
		if(userConnected(user)==0){
			printf("User %s is disconnected!", user);
			exit(0);
		}
	}	
	printf("<body>");
	welcome(user);

	
	printf("<section class='btns'>");
	
	printf("<div>");
	showBtn(user);
	logoutBtn(user);
	printf("</div>");
	
	printf("</section>");
	
	printf("</body>");
}

void end(){
	printf("</html>");
}


void makeScript(){
	begin();
	head();
	body();
	end();
}



