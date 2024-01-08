#include <alct.h>
#include <stdio.h>
#include <splitstr.h>
#include <ctype.h>
#include <trad_date.h>

#define SCR 6
#define PAGES_SHOWN 10

void begin(){
	printf("Content-Type:text/html \n\n");
	printf("<html>");
}

void head(){
	printf("<head>");
	printf("<meta charset=UTF8>");
	printf("<link rel='stylesheet' href='../styles/content.css'>");
	printf("<title>Authlog</title>");
	printf("</head>");
}

//for post data
int posted(char* user, int* page){
	char* data = alloc_char1(500);
	fgets(data,500,stdin);
	if(data==NULL){
		return 0;
	}
	sscanf(data,"user=%[^&]&page=%d",user,page);
	return 1;
}

//for get data
int got(char* user, int* page){
	char* data = getenv("QUERY_STRING");
	if(data==NULL){
		return 0;
	}
	sscanf(data,"user=%[^&]&page=%d",user,page);

	return 1;
}

//success data recuperation
int dataGot(char* method, char* user, int* page){
	if(strcmp(method,"get")==0){
		return got(user, page);
	}
	else if(strcmp(method,"post")==0){
		return posted(user, page);
	}
	else{
		return 0;
	}
}

//pagination
void pagination(int page, int maxPage, char* user){
	int start=page;
	int end=page;
	if(page%PAGES_SHOWN==0){
		start++;
		if(page==maxPage){
			start=page+1-PAGES_SHOWN;
		}
	}	
	else if(page%PAGES_SHOWN==1){
		start=page-(PAGES_SHOWN);
		if(page==1){
			start=1;
		}
	}
	else{
		start = page+1-(page%PAGES_SHOWN);
	}
	end = start+PAGES_SHOWN-1;
	printf("<div class='pages'>");
	for(int i=1; i<=maxPage; i++){
		if(i>=start && i<=end){
			printf("<a class='page_n'  href='http://www.authlog.mg/scripts/nosearch.cgi?user=%s&page=%d'>\
				<input type='button' value='%d'></a>",user,i,i);
		}
	}
	printf("</div>");

}

void searchBar(char* user){
	printf("<form class='searchform' action='http://www.authlog.mg/scripts/search.cgi' method='get'>\
			<input name='user' value='%s' style='display:none'>\
			<input name='page' value='1' style='display:none'>\
			<div class='searchbar' style='display:flex'>\
				<input type='search' class='searchentry' placeholder='hitady anarana' name='searched'>\
				<input type='submit' class='searchsubmit' value='karohy' name='karoka'>\
				<a href='http://www.authlog.mg/scripts/nosearch.cgi?user=%s&page=1'><input type='button' value='rehetra'></a>\
			</div>\
		</form>",user,user);
}

void logoutBtn(char* user){
        printf("<a href='http://www.authlog.mg/scripts/logout.cgi?user=%s'>\
                <input type='button' class='logout' value='hivoaka'>\
                </a>",user);
}

void usernameTable(int page, char* filename, char* user){
	int start = (page-1)*SCR;
	int end = page*SCR;
	int index = 0;

	char* u = alloc_char1(200);
	char* l = alloc_char1(200);
	FILE* auths = fopen("../files/auths.txt","r");

	printf("<td><h1>Anarana</h1><hr>");
	printf("<table class='usertable'>");
	
	while(fgets(l,200,auths)!=NULL){
		if(strstr(l,"pam_unix")!=NULL){
			if(strstr(l," opened for user ")!=NULL){
				u = split(l, " opened for user ")[1];
				u = split(u, "(uid")[0];
				if(u==NULL){
					printf("u==NULL");
					exit(0);
				}
			}	
			else{
				u = split(l, " closed for user ")[1];
				u = split(u, "\n")[0];
				if(u==NULL){
					printf("u==NULL(1)");
					exit(0);
				}
			}
		}		
		else{
			u = split(l, "(to ")[1];
			u = split(u, " ")[1];
			if(u==NULL){
				printf("u==NULL(2)");
				exit(0);
			}
		}
		index++;
		if(index>start && index<=end){
			printf("<tr><a  href='http://www.authlog.mg/scripts/search.cgi?user=%s&page=1&searched=%s&karoka=karohy'><h5 class='user'>%s</h5></a></tr>",user,u,u);
		}
	}

	printf("</table></td>");
	fclose(auths);
}

void dateTable(int page, char* filename, char* user){
	char** spl = alloc_char2(200,200);
	char* date = alloc_char1(200);
	char* l = alloc_char1(200);
	int start = (page-1)*SCR;
	int end = page*SCR;
	int index=0;
	FILE* auths = fopen("../files/auths.txt", "r");
	
	printf("<td><h1>Fotoana</h1><hr>");
	printf("<table class='datetable'>");
	
	while(fgets(l,200,auths)!=NULL){
		spl = split(l," ");
		sprintf(date,"%s %s %s %s %s %s %s",spl[0],spl[1],spl[2],spl[3],spl[4],spl[5],spl[6]);
		date = date_mlg_from_bash(date);
		index++;
		if(index>start && index<=end){
			printf("<tr><h5 class='date'>%s</h5></tr>",date);
		}
	}
	
	fclose(auths);
	printf("</table></td>");
}

void sessionTable(int page, char* filename, char* user, int* maxPage){
	char* s = alloc_char1(50);
	char* l = alloc_char1(300);
	int start = (page-1)*SCR;
	int end = page*SCR;
	int index = 0;

	FILE* auths = fopen("../files/auths.txt","r");

	printf("<td><h1>Asa</h1><hr>");
	printf("<table class='sessiontable'>");
	
	while(fgets(l,300,auths)!=NULL){
		if(strstr(l,"pam_unix")!=NULL){
			if(strstr(l,"opened for user")!=NULL){
				s = "misokatra";
			}
			else{
				s = "mihidy";
			}
		}
		else{
			s = "mihidy";
		}
		index++;
		if(start<index && index<=end){
			printf("<tr><h5 class='asa_%s' >%s</h5></tr>",s,s);
		}
		(*maxPage)++;
	}

	printf("</table></td>");

	fclose(auths);
}

void bigTable(int page, char* filename, char* user, int* maxPage){
	printf("<table class='bigtable'>");
	dateTable(page, filename, user);
	usernameTable(page, filename, user);
	sessionTable(page, filename, user, maxPage); 
	printf("</table>");
}

int userConnected(char* user){
	char* u = alloc_char1(200);
	char* p = alloc_char1(300);
	char* s = alloc_char1(200);
	char* l = alloc_char1(500);
	FILE* db = fopen("../files/database","r");
	
	while(fgets(l,500,db)!=NULL){
		sscanf(l,"%[^:]:%[^:]:%s",u,p,s);
		if(strcmp(u,user)==0){
			if(strcmp(s,"connected")==0){
				fclose(db);
				return 1;
			}
		}
	}

	fclose(db);
	return 0;	
}

void body(){
	char* method = "get";
	char* user = alloc_char1(200);
	int page = 1;
	int maxPage = 0;
	int dataSuccess = dataGot(method, user, &page);
	if(dataSuccess==0){
		printf("Got no valid data");
		exit(0);
	}
	if(userConnected(user)==0){
		printf("User %s disconnected", user);
		exit(0);
	}
	printf("<body>");
	searchBar(user);
	bigTable(page,"../files/auths.txt", user, &maxPage);
	if(maxPage%SCR>0){
		maxPage = 1+maxPage/SCR;
	}	
	else{
		maxPage /= SCR;
	}
	pagination(page, maxPage, user);	
	logoutBtn(user);
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

