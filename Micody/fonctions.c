void Compteur(int y,int x, int* compteur);
char** allouer(int ligne,int colonne);
void save(char* path, char** texte, int line);
void recuperer(char** texte,int decalage,int dec);
void retireS(char** tab,int line);
void headers(char* path,int langue);
void saut_de_ligne(int y,int x,int line,char** texte,int decalage,int dec);
int supprimer(int y,int x,int line,char** texte,int decalage,int dec,char* path,int langue);
void midina(int decalage,char** texte,int dec,char* path,int langue);
void miakatra(int decalage,char** texte,int dec,char* path,int langue);
void getText(char** texte,char* path,int *line);
void nombreLine(int line,int decalage);
void execute(char* executable);
void veloma();
void micody();


void micody(){
	char bienvenu[20] = "M i c o d y";
	char figlet[100] = "figlet ";
				
	for(int i=0; i<strlen(bienvenu); i++){
		figlet[7+i] = bienvenu[i];
					
		system(figlet);
		fflush(stdout);
		usleep(100000);
		if(i<strlen(bienvenu)-1){
			system("clear");
		}
	}
}

void veloma(){
	char veloma[20] = "V e l o m a !";
	char figletVeloma[100] = "figlet ";		
	for(int i=0; i<strlen(veloma); i++){
		figletVeloma[7+i] = veloma[i];	
		system(figletVeloma);
		fflush(stdout);
		usleep(100000);
		if(i<strlen(figletVeloma)-1){
			system("clear");
		}
	}
}

void execute(char* executable){
	char exec[75];
	system("clear");
	sprintf(exec, "%s", executable);
	
	system(exec);

	fflush(stdout);
	printf("\n\n\n_____________________________________\n");
	getchar();
}

void nombreLine(int line,int decalage){
	//int y=decalageV;
	start_color();  // initialisation des couleurs

	init_pair(1, COLOR_RED, COLOR_BLACK); // définir une paire de couleurs avec le rouge sur fond noir
	attron(COLOR_PAIR(1));  // activer la paire de couleurs définie
	
	for (int i=0+decalageV;i<LINES;i++){
		for (int j=0;j<decalageH;j++){
			move(i,j);
			printw(" ");
		}
	}
	
	if(line<=decalage+LINES-decalageV){
		int a=fabs(line-decalage);
		for(int i=0;i<a;i++){
			move(i+decalageV,0);
			printw("%d",i+1+decalage);
		}
		for(int i=0;i<a;i++){
			move(i+decalageV,4);
			printw("|");
		}
	}
	
	else{
		for(int i=0;i<LINES-decalageV;i++){
			move(i+decalageV,0);
			printw("%d",i+1+decalage);
		}
		for(int i=0;i<LINES-decalageV;i++){
			move(i+decalageV,4);
			printw("|");
		}
	}
	attroff(COLOR_PAIR(1)); // désactiver la paire de couleurs
		
}

void getText(char** texte,char* path,int *line){
	FILE *file = fopen(path,"r");
	
	while(fgets(texte[*line],sizeof(char)*(COLS-1),file)!=NULL){
		(*line)++;
	}
	fclose(file);
}

void midina(int decalage,char** texte,int dec,char* path,int langue){
	clear();
	
	move(0,0);
	headers(path,langue);
	
	int y=decalageV;
	int x=decalageH;
	
	for (int i=0; i<LINES-dec; i++){
		move(y++,x);
		printw("%s\n",texte[i+decalage]);
	}
	
}

void miakatra(int decalage,char** texte,int dec,char* path,int langue){
	clear();
	
	move(0,0);
	headers(path,langue);
	
	int y=decalageV;
	int x=decalageH;

	for (int i=0; i<LINES-dec; i++){
		move(y++,x);
		printw("%s\n",texte[i+decalage]);
	}
}

int supprimer(int y,int x,int line,char** texte,int decalage,int dec,char* path,int langue){
	y--;
	int compteur=0;				// compteur des caractères sur la ligne précédente	
	int x2=decalageH; int y2=y+1;
				
	Compteur(y,0,&compteur);
	x=compteur;
	move(y,x);
	for(int i=0 ; i < COLS ;i++){
		chtype mot;
		mot=mvinch(y2,x2);
		mvdelch(y2,x2);
		mvaddch(y,x-1,mot);
		x++;
	}
	x=decalageH;y++;move(y,x);deleteln();
	
	recuperer(texte,decalage,dec);
	
	// remonter les lignes en dessous
	for (int i=LINES-1+decalage-dec; i<line ;i++){
		sprintf(texte[i],"%s",texte[i+1]);
	}
	
	
	clear();
	for (int i=line;i<line+10;i++){
		texte[i]=calloc(COLS,sizeof(char)*COLS);
	}
	move(0,0);
	headers(path,langue);
	
	int u=decalageV;
	int v=decalageH;

	for (int i=0; i<=LINES-dec-1; i++){
		move(u++,v);
		printw("%s\n",texte[i+decalage]);
	}
	return compteur;
}

void saut_de_ligne(int y,int x,int line,char** texte,int decalage,int dec){
	// decaler les lignes en dessous
	
	for (int i=line; i>LINES-1+decalage-dec ;i--){
		sprintf(texte[i],"%s",texte[i-1]);
	}
		
	int compteur = 0;
	Compteur(y,x,&compteur);
	int xtmp = x;
	x=decalageH ; y++; move(y,x);
	insertln();
	x--;
	for(int i=decalageH ; i < compteur ;i++){
		chtype mot;
		mot=mvinch(y-1,xtmp);
		mvdelch(y-1,xtmp);
		mvaddch(y,x+1,mot);
		x++;
	}	
}

void headers(char* path,int langue){
	
	attron(A_BOLD | A_REVERSE);
	for(int i=0; i<=COLS; i++){
		mvprintw(0, i, " ");
	}
	if (langue == 1){
		mvprintw(0, ((COLS-strlen(path)-4)/2)+7,"file: [ %s ]", path);
		
		mvprintw(0, 0,"F1: [Save]");
		
		mvprintw(0, 22, "F2: [Compile]");
		
		mvprintw(0, 45, "F3: [Execute]");
		
		mvprintw(0, COLS-55, "F6: [Manual]");
		
		mvprintw(0, COLS-35, "F4: [Compilation]");
		
		mvprintw(0, COLS-11 , "Esc: [Quit]");
		
		attroff(A_BOLD | A_REVERSE);
	}
	else if (langue == 0){
		mvprintw(0, ((COLS-strlen(path)-4)/2)+7,"fichier: [ %s ]", path);
		
		mvprintw(0, 0,"F1: [Sauvegarder]");
		
		mvprintw(0, 22, "F2: [Compiler]");
		
		mvprintw(0, 45, "F3: [Executer]");
		
		mvprintw(0, COLS-55, "F6: [Manuel]");
		
		mvprintw(0, COLS-35, "F4: [Compilation]");
		
		mvprintw(0, COLS-11 , "Esc: [Quitter]");
		
		attroff(A_BOLD | A_REVERSE);
	}
	else if (langue == 2){
		mvprintw(0, ((COLS-strlen(path)-4)/2)+7,"Rakitra: [ %s ]", path);
		
		mvprintw(0, 0,"F1: [Tahiry]");
		
		mvprintw(0, 22, "F2: [Compilena]");
		
		mvprintw(0, 45, "F3: [Executena]");
		
		mvprintw(0, COLS-55, "F6: [Fanampiana]");
		
		mvprintw(0, COLS-35, "F4: [Fizahana-comp]");
		
		mvprintw(0, COLS-11 , "Esc: [Hiala]");
		
		attroff(A_BOLD | A_REVERSE);
	}
}

void retireS(char** tab,int line){
	for (int i=0;i<line;i++){
		for(int j=0;j<150;j++){
			if(tab[i][j]=='\n') tab[i][j]=' ';
		}
	}
}

void recuperer(char** texte,int decalage,int dec){

	for (int a = 0 ; a < LINES-dec ; a++) {
		texte[a+decalage]=calloc(150,sizeof(char)*150);
		int compteur=0;
		Compteur(a+dec,0,&compteur);
		for (int b = 0 ; b < compteur ; b++) {
			// Se déplacer à la position x, y de la fenêtre
			move(a+dec, b+decalageH);
			// Lire le caractère dans la case actuelle de la fenêtre
			texte[a+decalage][b] = (char)inch();
		}
	}
}

void save(char* path, char** texte, int line){
	if (line==0) line++;
	
	FILE *file = fopen(path,"w");
	if(file==NULL) printf("erreur d'ouverture\n");
	for(int i=0;i<line;i++){
		fprintf(file,"%s\n",texte[i]);
	}
	fclose(file);
}

char** allouer(int ligne,int colonne){
	char **tab=NULL;
	tab=(char**)malloc(sizeof(char*)*ligne);
	for(int i=0;i<ligne;i++){
		*(tab+i)=(void*)calloc(colonne,sizeof(char)*colonne);
	}
	return tab;
}

void Compteur(int y,int x, int* compteur){
    int ce=0;
    for (x=decalageH;x<COLS;x++){
		chtype c=mvinch(y,x);
		if(c==' ') ce++;
		if(c!=' ') ce=0;
	}
	*compteur=COLS-ce+1;
}
