#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
#include <math.h>

#define decalageV 2
#define decalageH 5


#include "option.c"
#include "interface.c"
#include "fonctions.c"
#include "compilation.c"



void writing(char* path,char* executable,int langue){
	int command=0;						//valeur retournée par la fonction commandeCompile
	char parametre[300];				//parametre de compilation
	
	micody();
	FANORATANA:
	
	system("clear");
	flushinp();
	
	///Initialisation
	initscr();
	setlocale(LC_ALL,"");
	
	int decalage=0;						// decalage lors du scroll
	int line=0;							// nombre de ligne
    int dec=decalageV;					// decalage du texte par rapport à l'entête
    int x = decalageH, y = dec;			// position initiale du curseur
	
	
	char** texte=allouer(3000,COLS+1);			// allocation du tableau
	getText(texte,path,&line);					//recupère le texte du fichier							

    headers(path,langue);								// affiche l'entête
    nombreLine(line,decalage);					//affiche le numéro de ligne
    
    ///Afficher le texte à l'écran
    move(y,x);
	for(int i=0;i<LINES-dec;i++){
		for (int j=0;j<COLS;j++){
			printw("%c",texte[i][j]);
		}
		move(++y,x);
	}					
	
	retireS(texte,line);				// retire le '\n' dans chaque tableau
	
	y=decalageV; x=decalageH; move(decalageV,decalageH);
	
	keypad(stdscr, TRUE); 				// active la prise en charge des touches fléchées
	noecho(); 							// désactive l'affichage des caractères entrés par l'utilisateur
	
	int tmp; move(y,x); tmp=inch();		// caractère temporaire pour recuperer le char sur la position actuelle
	wchar_t car; 						// variable pour stocker la touche pressée
	        
	while((car = getch())) {
		
		switch(car) {
			
			///Agrandir la fenêtre
			case 410:
				clear();
				endwin();
				free(texte);
				goto FANORATANA;
				break;
				
			///TOUCHE ECHAP POUR QUITTER
			case 27:
				endwin();
				free(texte);
				system("clear");
				veloma();
				exit(0);
				break;
			
			///Save
			case KEY_F(1):
				flushinp();
				retireS(texte,line);
				save(path, texte, line);
				clear();
				endwin();
				flash();
				free(texte);
				goto FANORATANA;
				
			///Compile
			case KEY_F(2):
				recuperer(texte,decalage,dec);			// fonction pour recuperer tous les caracteres sur l'affichage et le stocke dans le tableau 
				retireS(texte,line);
				save(path, texte, line);				// écriture dans le fichier
				clear();
				endwin();
				
				///Compiler le fichier
				if( compile(path, executable,command,parametre,langue) == 1){
					
				}
				
				getchar();
				free(texte);
				goto FANORATANA;
				break;
				
			///Executer
			case KEY_F(3):
				flushinp();
				clear();
				endwin();
				execute(executable);
				free(texte);
				goto FANORATANA;
					
			///Paramètres de compilation
			case KEY_F(4):
				clear();
				endwin();
				save(path, texte, line);
				free(texte);
				command=commandCompile(parametre,langue);
				goto FANORATANA;
				break;
				
			case KEY_F(6):
				clear();
				endwin();
				save(path, texte, line);
				system ("man micody");
				free(texte);
				goto FANORATANA;
				break;
				
			case KEY_LEFT:
				flushinp();
				if(x > decalageH){
					x--;
					break;
				}
				if(x==decalageH && y!=0+dec){
					y--;
					int compteur=0;
					Compteur(y,0,&compteur);
					x=compteur-1;
				}
				if(x==decalageH && y==0+dec && decalage != 0){
					decalage--;
					miakatra(decalage,texte,dec,path,langue);
					int compteur = 0;
					Compteur(y,0,&compteur);
					x=compteur-1;
				}		
			break;
			
			case KEY_RIGHT:
				flushinp();
				int compteur=0;
				Compteur(y,0,&compteur);
				if(x <= compteur-1) x++;
				if(y==LINES-1 && x == compteur && y+decalage<=line ){
					decalage++;
					midina(decalage,texte,dec,path,langue);
					x=decalageH;
					break;
				}
				if(x == compteur && y+decalage<=line){
					y++;
					x=decalageH;
				}
			break;
			
			case KEY_UP:	
				flushinp();
				compteur=0;
				if( y > -1  ) y--;
				if(y==-1+dec && decalage != 0){
					decalage--;
					miakatra(decalage,texte,dec,path,langue);
				}
				if(y==-1+dec) y++;
											
				Compteur(y,0,&compteur);
				if(x>compteur) x=compteur-1;
			break;
			
			case KEY_DOWN:
			flushinp();
			if(y + decalage <= line){
				compteur=0;
				if(y < LINES) y++;
				if(y==LINES) {
					y--;
					decalage++;
					midina(decalage,texte,dec,path,langue);
				}
				Compteur(y,0,&compteur);
				if(x>compteur) x=compteur-1;
			}
			break;
			
			case KEY_BACKSPACE:
				if(x==decalageH && y==0+dec && decalage==0){
					
				}
				else if(x==decalageH && y!=0+dec){
					compteur=0;
					line--;
					compteur = supprimer(y,x,line,texte,decalage,dec,path,langue);
					y--;
					x=compteur-1;
					break;
				}
				else if(x==decalageH && y==0+dec && decalage!=0){
					decalage--;
					line--;
					miakatra(decalage,texte,dec,path,langue);
					y++;
					compteur = supprimer(y,x,line,texte,decalage,dec,path,langue);
					
					x=compteur-1;
					y--;
					break;
				}
				
	
				if(x>decalageH){		
					int i = x - 1;
					mvdelch(y, i);
					x--;
				}
			break;
						
			default:
				if (car==10){
					line++;
					compteur=0;
					Compteur(y,0,&compteur);
					if(y<LINES-1){
						saut_de_ligne(y,x,line,texte,decalage,dec);
						x=decalageH;y++;
						break;
					}
					if(y==LINES-1){
						decalage++;
						midina(decalage,texte,dec,path,langue);
						saut_de_ligne(y-1,x,line,texte,decalage,dec);
						x=decalageH;
					}
						
				}
				else{
					int Long=0; Compteur(y,x,&Long);
					if(Long<COLS){
						if(car==9 && Long<COLS-4){
							for(int i=0; i<4; i++){
								// décale les caractères à droite
								x++; move(y, x); insch(tmp);
						
								// insère un caractère à la position du curseur
								x--; move(y, x); addch(' ');
						
								// déplace le curseur vers la droite				
								x++;
							}
						}
						else if(car==9 && (Long>COLS-4 || x>COLS-6)){
							
						}
						else if(car==32 && x==COLS-1){
							// décale les caractères à droite
							x++; move(y, x); insch(tmp);
						
							// insère un caractère à la position du curseur
							x--; move(y, x); addch(car);
						
							// déplace le curseur vers la droite				
							x++;
						}
						else if(car>127){
							
						}
						else{
							// décale les caractères à droite
							x++; move(y, x); insch(tmp);
						
							// insère un caractère à la position du curseur
							x--; move(y, x); addch(car);
						
							// déplace le curseur vers la droite				
							x++;
						} 							
					}
				}
				break;
				
		}
		nombreLine(line,decalage);
		move(y, x);
		tmp=inch();							// récupère le caractère courant					
		recuperer(texte,decalage,dec);      // récupère le texte sur l'ecran
		refresh();
		move(y, x);
	}
    free(texte);
    clear();
    endwin();
}

int main(int argc, char** argv){
	int langue =1;
	if((argc == 2) && strcmp("-h", argv[1]) == 0){
		print_help();
		return 0;
	}
	else if((argc == 2) && strcmp("-v", argv[1]) == 0 ){
		print_version();
		return 0;
	}
	
	else if(argc == 1){
			micody();
			int op=6, l=6, h=5;
eto :
			op=interface(h,l,langue)-h;
			switch(op){
				case 0:
					system("clear");
					micody();
					char* path = (char*) malloc(COLS*sizeof(char));
					ouvrir(path,langue);
					char touch[250] = "touch ";
					sprintf(touch, "touch %s", path);
					system(touch);
					system("clear");
		
					char executable[300];
	
					if (path[0]==47){
						for(int i=0; i<strlen(path)-2; i++){
							executable[i] = path[i];
						}
						executable[strlen(path)-2] = '\0';
						writing(path, executable,langue);
						veloma();
						free(path);
					}
	
					else{
						system("pwd > /tmp/micodyP");
						FILE* file=fopen("/tmp/micodyP","r");
						char pathInit[100];
						fgets(pathInit,sizeof(char)*100,file);
						fclose(file);
		
						char pathAbs[200];
		
						for (int i=0;i<=strlen(pathInit);i++){
							if (pathInit[i]==10) pathInit[i]=0;
						}
		
						sprintf(pathAbs,"%s/%s",pathInit,path);
						printf("%s",pathAbs);
						//return 0;
			
						for(int i=0; i<strlen(pathAbs)-2; i++){
							executable[i] = pathAbs[i];
						}
						executable[strlen(pathAbs)-2] = '\0';
	
						writing(pathAbs, executable,langue);
						veloma();
						free(path);
					}
				break;
				case 1:
					propos();
					getchar();
					goto eto;
	
				case 2:
					system("clear");
					micody();
					int lang = 6;
					lang = language (h,l)-h;
					switch (lang){
						case 0:
							langue = 0;
							break;
						case 1:
							langue = 1;
							break;
						case 2:
							langue = 2;
							break;
						case 3:
							langue = 3;
							break;
						default:
							langue = 1;
							break;
					}
					
					goto eto;
					
				case 3:
					system("clear");
					veloma();
					return 0;

		}
	}
	
	char* path = (char*) malloc(COLS*sizeof(char));
	path = argv[1];
	char touch[250] = "touch ";
	sprintf(touch, "touch %s", path);
	system(touch);
	system("clear");
	
	char executable[300];
	
	if (path[0]==47){
		for(int i=0; i<strlen(path)-2; i++){
			executable[i] = path[i];
		}
		executable[strlen(path)-2] = '\0';
		writing(path, executable,langue);
		veloma();
		free(path);
	}
	
	else{
		system("pwd > /tmp/micodyP");
		FILE* file=fopen("/tmp/micodyP","r");
			char pathInit[100];
			fgets(pathInit,sizeof(char)*100,file);
		fclose(file);
		
		char pathAbs[200];
		
		for (int i=0;i<=strlen(pathInit);i++){
			if (pathInit[i]==10) pathInit[i]=0;
		}
		
		sprintf(pathAbs,"%s/%s",pathInit,path);
		
		for(int i=0; i<strlen(pathAbs)-2; i++){
			executable[i] = pathAbs[i];
		}
		executable[strlen(pathAbs)-2] = '\0';
	
		writing(pathAbs, executable,langue);
		veloma();
		free(path);
	}
	return 0;
}




