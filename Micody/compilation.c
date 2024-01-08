int compilationInterface(int h,int l,int langue){
	initscr();
	
	WINDOW *boite;
    
    initscr();
    boite= subwin(stdscr, 9, 40, 1 , 2);
   
    box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
    refresh();
   
    char titre[]="        COMPILATION";
	char opt1[]=" STANDARD             ";
	char opt2[]=" SDL                  ";
	char opt3[]=" NCURSES              ";
	char opt4[]=" ELSE                 ";
	if (langue == 0){
		char titre[]="        COMPILATION";
		char opt4[]=" AUTRE                 ";
	}
	if (langue == 2){
		char titre[]="        COMPILATION";
		char opt4[]=" ANKOATRA                 ";
	}
	noecho();
	keypad(stdscr,TRUE);
	int y=h;
	
	chtype car=0;
	curs_set(0);
	
	
	move(h-2,l+3);
	attron( A_BOLD);
	printw("%s",titre);
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
			if(y<h+3) y++;
			break;
		}
		move(y,l);
		clear();
		box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
		if(y==h){
			move(h-2,l+3);
			attron( A_BOLD);
			printw("%s",titre);
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
			move(h-2,l+3);
			attron( A_BOLD);
			printw("%s",titre);
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
			move(h-2,l+3);
			attron( A_BOLD);
			printw("%s",titre);
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
			move(h-2,l+3);
			attron( A_BOLD);
			printw("%s",titre);
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



int commandCompile(char* parametre,int langue){
	int com=0;
	int l=5, h=4;
	com=compilationInterface(h,l,langue)-h;
	
	if (com==3){
		char pourcent[]="%";
		printf("\033[31mgcc -Wall -g %se -o %sf \033[0m",pourcent,pourcent);
		scanf("%s",parametre);
	}
	return com;
}

int compile(char* path, char* executable,int command,char* parametre,int langue){
	char compile[2000] = " ";
	
	if(command==0){
		sprintf(compile,"gcc %s -o %s -lm 2> GCC_LOGS", path, executable);
	}
	
	else if(command==2){
		sprintf(compile,"gcc %s -o %s -lncurses 2> GCC_LOGS", path, executable);
	}
	else if(command==1){
		sprintf(compile,"gcc %s -o %s $(sdl2-config --cflags --libs)2> GCC_LOGS", path, executable);
	}
	else{
		sprintf(compile,"gcc %s -o %s %s 2> GCC_LOGS", path, executable,parametre);
	}
	
	system("clear");
//	printf("eto ve ? ");
	system("cat GCC_LOGS && pwd");
	if(langue == 0){
		system("grep -E 'function|error|warning|note' GCC_LOGS > error-line.txt && trans -b -s en -t fr -i error-line.txt > translated.txt");
	}
	else if(langue == 1){
		system("cat GCC_LOGS");
	}
	else if(langue == 2){
		system("trans -b -s en -t mg -i GCC_LOGS");
	}
	system("");
	fflush(stdout);												/// TSY AIKOU OE MANINONA
	if(system(compile) != 0){
		return 1;
	}
	else{
		if (langue == 1){
			printf("COMPILATION TERMINATED SUCCESSFULLY\n\n");
			printf("\n_____________________________________\n");
		}
		else if (langue == 0){
			printf("COMPILATION TERMINEE AVEC SUCCES\n\n");
			printf("\n_____________________________________\n");
		}
		else if (langue == 2){
			printf("VITA SOA AMAN-TSARA NY COMPILATION\n\n");
			printf("\n_____________________________________\n");
		}
	}
	return 0;
}
