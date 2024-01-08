#include <alct.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//Débuter le script
void begin(){
	printf("Content-Type:text/html \n\n");
}

//Redirection vers la page d'inscription si il y a une erreur
void fail(){
	printf("<head><meta charset=UTF8 http-equiv='refresh' content='0;url=http://www.authlog.mg/login/signin.html'></head></html>");
}

//Fin du script
void end(){
	printf("</html>");
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

//Gérer la récupération des données du formulaire
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

//Vérifier si l'utilisateur et le mot de passe et bien dans la base de données
int dbVerified(char* u, char* p){
	int ver = 0;
	char* line = alloc_char1(200);
	char* user = alloc_char1(200);
	char* pwd = alloc_char1(200);
	char* state = alloc_char1(50);
	FILE* db = fopen("../files/database","r");
	if(db==NULL){
		return 0;
	}
	while(fgets(line,200,db)!=NULL){
		//J'ai choisi cet algo pour peut-être crypter le mot de passe plus tard
		sscanf(line,"%[^:]:%[^:]:%s",user,pwd,state);
		if(strcmp(user,u)==0){
			if(strcmp(pwd,p)==0){
				ver = 1;
				break;
			}
		}
	}
	fclose(db);
	return ver;
}

//S'assurer que l'utilisateur est déconnecté
int userDisconnected(char* u, char* p){
	char* uconnected = alloc_char1(200);
	char* line = alloc_char1(200);
	FILE* db = fopen("../files/database","r");
	if(db==NULL){
		printf("Database not found");
		exit(0);
	}
	sprintf(uconnected,"%s:%s:connected\n",u,p);//ligne marquant que l'utilisateur est connecté
	while(fgets(line,200,db)!=NULL ){
		//retourner 0 si l'utilisateur est connecté
		if(strcmp(line,uconnected)==0){
			fclose(db);
			return 0;
		}
		//printf("%s => %d\n",line,strcmp(line,uconnected));
	}
	fclose(db);
	return 1;
}

//mettre l'état de l'utilisateur à "connected" si il est "disconnected"
int makeUserConnected(char* u, char* p){
	char* l = alloc_char1(200);
	char* ul = alloc_char1(200);
	FILE* db = fopen("../files/database","r");
	if(db==NULL){
		printf("database not found for making connection");
		exit(0);
	}
	FILE* tdb = fopen("../files/tdatabase","w+");
	if(tdb==NULL){
		printf("tdb not accessible");
		exit(0);
	}

	//copier le contenu de db vers tdb (et modifier la ligne de l'utilisateur)
	sprintf(ul,"%s:%s:disconnected",u,p);
	while( fgets(l,200,db)!=NULL ){
		//modifier la ligne marquant la déconnection de l'utilisateur
		if(strstr(l,ul)!=NULL){
			sprintf(l,"%s:%s:connected\n",u,p);
		}
		fprintf(tdb,"%s",l);
	}	
	fclose(db);
	fclose(tdb);

	FILE* DB = fopen("../files/database","w+");
	if(DB==NULL){
		printf("Rewrite db not possible");
		exit(0);
	}
	FILE* TDB = fopen("../files/tdatabase","r");
	if(TDB==NULL){
		printf("Read backup db not possible");
		exit(0);
	}
	//Réécrire le contenu de tdb dans db
	while(fgets(l,200,TDB)!=NULL){
		if(strcmp(l,"\n")!=0){
			sscanf(l,"%[^\n]",l);
			fprintf(DB,"%s\n",l);
		}
	}
	fclose(DB);
	fclose(TDB);

	return 0;
}

//redirection vers une page de bienvenue
void redirectToHome(char* user){
	printf("<html><head><meta http-equiv='refresh' content='0;url=http://www.authlog.mg/scripts/home.cgi?user=%s'></head></html>",user);
}

//generate the script for this user
void makeScript(){
	char* method = "post";
	char* user = alloc_char1(50);
	char* pwd = alloc_char1(50);
	
	begin();
	//Récupération des données (post/get) avec succès
	if (succeed(method, user, pwd)==1){
		if(dbVerified(user,pwd)==1){	
			//Utilisateur déconnecté
			if(userDisconnected(user,pwd)==1){
				makeUserConnected(user,pwd);
				redirectToHome(user);
			}
			else{//Utilisateur déjà connecté
				printf("User already conntected");
				//fail();
			}

		}
		else{
			printf("wrong password or username");
			//fail();
		}
	}
	//Echec de la récupération des données
	else{
		printf("invalid form method invalid data");
		//fail();
	}
}


