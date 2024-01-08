int interface(int h,int l,int langue ){
	
	initscr();
	
	WINDOW *boite;
    
    initscr();
    boite= subwin(stdscr, 10, 50, 2 , 3);
   
    box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
    refresh();
	
		char opt1[]=" OPEN                ";
		char opt2[]=" ABOUT            ";
		char opt5[]=" LANGUAGE         ";
		char opt3[]=" QUIT             ";
		char opt4[]="                     ";
	if (langue == 0){
		char opt1[]=" OUVRIR               ";
		char opt2[]=" A PROPOS            ";
		char opt5[]=" LANGUE              ";
		char opt3[]=" QUITTER             ";
		char opt4[]="                     ";		
	}
	else if (langue == 2){
		char opt1[]=" SOKAFANA               ";
		char opt2[]=" MOMBAMOMBA            ";
		char opt5[]=" TENY                  ";
		char opt3[]=" HIALA                 ";
		char opt4[]="                     ";		
	}
	noecho();
	keypad(stdscr,TRUE);
	int y=h;
	
	chtype car=0;
	curs_set(0);
	
	
	move(h-3,l+4);
	attron( A_BOLD);
	printw(" MICODY ");
	attroff(A_BOLD);
	move(h,l);
	attron(A_REVERSE|A_BOLD);
	printw(" %s",opt1);
	attroff(A_REVERSE|A_BOLD);
	move(h+1,l);
	printw("%s",opt2);
	move(h+2,l);
	printw("%s",opt5);
	move(h+3,l);
	printw("%s",opt3);
	move(h+4,l);
	printw("%s",opt4);
	
	while((car=getch())!=10){
		switch(car){
			case KEY_UP:
			if(y>h) y--;
			break;
			
			case KEY_DOWN:
			if(y<h+3) y++;
			break;
		}
		move(y,l);
		clear();
		box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
		if(y==h){
			move(h-3,l+4);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt1);
			attroff(A_REVERSE|A_BOLD);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			printw("%s",opt5);
			move(h+3,l);
			printw("%s",opt3);
			move(h+4,l);
			printw("%s",opt4);
				}
			
		else if(y==h+1){
			move(h-3,l+4);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt2);
			attroff(A_REVERSE|A_BOLD);			
			move(h+2,l);
			printw("%s",opt5);
			move(h+3,l);
			printw("%s",opt3);
			move(h+4,l);
			printw("%s",opt4);
				
		}
		else if(y==h+2){
			move(h-3,l+4);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt5);
			attroff(A_REVERSE|A_BOLD);
			move(h+3,l);
			printw("%s",opt3);
			move(h+4,l);
			printw("%s",opt4);			
		}
		else if (y==h+3){
			move(h-3,l+4);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			printw("%s",opt5);
			move(h+3,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt3);	
			attroff(A_REVERSE|A_BOLD);
			move(h+4,l);
			printw("%s",opt4);			
		}
		else{
			move(h-3,l+4);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			printw("%s",opt5);
			move(h+3,l);
			printw(" %s",opt3);	
			move(h+4,l);
			attron(A_REVERSE|A_BOLD);
			printw("%s",opt4);		
			attroff(A_REVERSE|A_BOLD);
		}
		refresh();
	}
	curs_set(1);
	clear();
	delwin(boite);
	endwin();
	return y;
}

int language(int h,int l){
	initscr();
	
	WINDOW *boite;
    
    initscr();
	boite= subwin(stdscr, 10, 50, 2 , 3);
   
    box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
    refresh();
 	char opt1[]=" FRENCH               ";
	char opt2[]=" ENGLISH              ";
	char opt3[]=" MALAGASY             ";
	char opt4[]="                     ";
	noecho();
	keypad(stdscr,TRUE);
	int y=h;
	
	chtype car=0;
	curs_set(0);
	
	
	move(h-3,l+3);
	attron( A_BOLD);
	printw(" MICODY ");
	attroff(A_BOLD);
	move(h,l);
	attron(A_REVERSE|A_BOLD);
	printw(" %s",opt1);
	attroff(A_REVERSE|A_BOLD);
	move(h+1,l);
	printw("%s",opt2);
	move(h+2,l);
	printw("%s",opt3);
	move(h+3,l);
	printw("%s",opt4);
	
	while((car=getch())!=10){
		switch(car){
			case KEY_UP:
			if(y>h) y--;
			break;
			
			case KEY_DOWN:
			if(y<h+2) y++;
			break;
		}
		move(y,l);
		clear();
		box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
		if(y==h){
			move(h-3,l+3);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt1);
			attroff(A_REVERSE|A_BOLD);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			printw("%s",opt3);
			move(h+3,l);
			printw("%s",opt4);
		}
			
		else if(y==h+1){
			move(h-3,l+3);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt2);
			attroff(A_REVERSE|A_BOLD);			
			move(h+2,l);
			printw("%s",opt3);
			move(h+3,l);
			printw("%s",opt4);
		}
		else if(y==h+2){
			move(h-3,l+3);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt3);
			attroff(A_REVERSE|A_BOLD);
			move(h+3,l);
			printw("%s",opt4);			
		}
		else{
			move(h-3,l+3);
			attron( A_BOLD);
			printw(" MICODY ");
			attroff(A_BOLD);
			move(h,l);
			printw("%s",opt1);
			move(h+1,l);
			printw("%s",opt2);
			move(h+2,l);
			printw("%s",opt3);
			move(h+3,l);
			attron(A_REVERSE|A_BOLD);
			printw(" %s",opt4);	
			attroff(A_REVERSE|A_BOLD);		
		}
		refresh();
	}
	curs_set(1);
	clear();
	delwin(boite);
	endwin();
	return y;
}

void ouvrir(char* path,int langue){
	if (langue == 1){
		printf("ENTER THE PATH OF THE FILE : ");
	}
	if (langue == 0){
		printf("ENTRER LE CHEMIN DU FICHIER : ");
	}
	if (langue == 2){
		printf("SORATY NY ZOTRAN'NY RAKITRA : ");
	}
	scanf("%s",path);
}

void propos(){
	
	system("clear");
	/*
	printf("Nom du paquet: editeur\nVersion: 1.0\nAuteur: Groupe3mit <Groupe3mit@gmail.com>\nDescription: Editeur de texte en C");

	printf("\n\nInstallation\n============\nPour installer le paquet, exécutez la commande suivante :\nsudo dpkg -i micody.deb");

	printf("\n\nDépendances\n===========");
	printf("\nCe paquet dépend de la bibliothèque curses.h pour fonctionner et aussi de figlet. Si vous ne l'avez pas déjà installé, vous pouvez l'installer en exécutant quelques commandes avant de l'installer ,veuillez quitter et executez ces commandes:");
	printf("\nsudo apt install build-essential\nsudo apt-get install libncurses-dev\nsudo apt-get insall figlet");

	printf("\n\nUtilisation\n===========\nAprès l'installation, vous pouvez utiliser l'éditeur en tapant la commande suivante dans un terminal :micody");

	printf("\n\nOptions\n=======\nL'éditeur prend en charge les options suivantes :\n- v : Afficher la version de l'éditeur");
	printf("\n- h : Afficher l'aide");


	printf("\n\nBug Reports\n===========\nPour signaler un bug ou suggérer une amélioration, veuillez contacter l'auteur à l'adresse email mentionnée ci-dessus.");
	*/
	system("less propos.txt");
}


