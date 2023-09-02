#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
coord.X = x; coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

typedef struct livre{
	char titre[50];
	char auteurs[100];
	char edition[50];
	int nbexemp;
	struct livre* code;
	struct livre* nextlivre;
	
}Livre;

typedef struct abonne{
	int score;
	int id;
	char fullname[50];
	int day;
	int month;
	int year;
	char annee_etude[50];
	struct abonne* nextabonne;
}Abonne;

typedef struct date{
	int d,m,y;
}Date;

typedef struct emprunt{
	int id;
	Date d_emprunt;
	Date d_f_emprunt;
	Date d_retourne_livre;
	char titre[50];
	struct emprunt* nextemprunt;
}Emprunt;


typedef struct reservation{
	int id;
	char titre[50];
	struct reservation *nextreservation;
}Reservation;


typedef struct classement{
	char name[75];
	int score;
}Class;

void intro();
void remplivre();
void ajoutlivre();
void supplivre();
void modiflivre();
void gestlivre();
void ajoutabonne();
void suppabonne();
void modifabonne();
void gestabonne();
void ajoutemprunt();
void suppemprunt();
void modifemprunt();
void gestemprunt();
void recherchelivre();
void gestreservation();
void rempreservation();
void calculepoints();
void classement();
void insertionsort();


void calculepoints(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	Abonne *pa=NULL;
	Emprunt *pe=NULL;
	Emprunt *pe2=NULL;
	Emprunt *pe3=NULL;
	pa=ha;
	pe=he;
	int ID,x=0,la=1,le=1;
	while((pa->nextabonne!=NULL) || (pa==ha) || (la==1)){
		ID=pa->id;
		x=0;
		while(pe->nextemprunt!=NULL || pe==he || le==1){
			if(pe->id==ID){
				x++;
			}
			pe=pe->nextemprunt;
			if(pe->nextemprunt==NULL){
				x++;
				le=0;
			}
		}
		
		if(x>=3){
			pa->score=((x/3)*10 + x%3);
		}
		else if(x<3){
			pa->score=x;
		}
		if(pa->nextabonne==NULL){
			la=0;
		}
			
	}
	
	
	
	
}


void insertionsort(int list[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = list[i];
        j = i - 1;
        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
    }
}
 

 
void classement(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	system("cls");
	Class *first=(Class*)malloc(sizeof(Class));
	Class *second=(Class*)malloc(sizeof(Class));
	Class *third=(Class*)malloc(sizeof(Class));
	Abonne *pa=NULL;
	Abonne *tmp=NULL;
	pa=ha;
	tmp=ha;
	int x=0;
	if((pa==NULL)||(pa->nextabonne==NULL)||(pa->nextabonne->nextabonne==NULL)){
		gotoxy(15,5);
		printf("nombre d'abonne insuffisant");
		gotoxy(15,7);
		printf("retour en 3 secondes...");
		sleep(3);
		intro(hl,ha,he,hr);
	}
	int count=0;
 
    while(tmp != NULL){
       tmp = tmp->nextabonne;
        count++;
 
    }
    
    int scorelist[count];
    while(pa!=NULL){
    	scorelist[x]=pa->score;
    	x++;
    	pa=pa->nextabonne;
	}
	pa=ha;
	x=0;
	int y=0,z=0;
	insertionsort(scorelist,count);
	first->score=scorelist[0];
	second->score=scorelist[1];
	third->score=scorelist[2];
	
	while(pa!=NULL){
		if(pa->score==first->score){
			x++;
			if(x==1){
				strcpy(first->name,pa->fullname);
			}
			else if(x>1){
				strcat(first->name," & ");
				strcat(first->name,pa->fullname);
			}
			
		}
		if(pa->score==second->score){
			y++;
			if(y==1){
				strcpy(second->name,pa->fullname);
			}
			else if(y>1){
				strcat(second->name," & ");
				strcat(second->name,pa->fullname);
			}
			
		}
		if(pa->score==third->score){
			z++;
			if(y==1){
				strcpy(third->name,pa->fullname);
			}
			else if(z>1){
				strcat(third->name," & ");
				strcat(third->name,pa->fullname);
			}
			
		}
		pa=pa->nextabonne;
	}
	gotoxy(15,5);
	printf("\xB2\xB2\ Classement des abonnees ");
	gotoxy(15,8);
	printf("\xB2\ le ou les premiers : ");
	puts(first->name);
	gotoxy(18,10);
	printf("\xB2\ Avec un score de %d points",first->score);
	gotoxy(15,14);
	printf("\xB2\ le ou les deuxiemes : ");
	puts(second->name);
	gotoxy(18,16);
	printf("\xB2\ Avec un score de %d points",second->score);
	gotoxy(15,20);
	printf("\xB2\ le ou les troisiemes : ");
	puts(third->name);
	gotoxy(18,22);
	printf("\xB2\ Avec un score de %d points",third->score);
	gotoxy(12,25);
	printf("retour dans 5 seconds...");
	sleep(5);
	intro(hl,ha,he,hr);
}
 
 
void gestreservation(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	system("cls");
	Reservation *p=NULL;
	p=hr;
	int x=0;
	while(p->nextreservation != NULL){
		x++;
		p=p->nextreservation;
	}
	if(x!=0){
	Reservation* newreservation=NULL;
    newreservation = (Reservation*)malloc(sizeof(Reservation));
    p->nextreservation=newreservation;
    newreservation->nextreservation=NULL;
    rempreservation(newreservation);
    
	}
	else{
		rempreservation(p);
	}
	gotoxy(12,10);
	printf("ajout accomplie!");
	gotoxy(12,12);
	printf("retour dans 3 secondes");
	sleep(3);
	intro(hl,ha,he,hr);
	
} 


void rempreservation(Reservation *res){
	system("cls");
	char a[50];
	int b;
	gotoxy(15,5);
	printf("\xB2\xB2\ entrer l'ID de l'etudiant qui veut reserver: ");
	scanf("%d",&b);
	res->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ entrer le titre du livre que l'etudiant veut reserver :");
	scanf("%s",&a);
	strcpy(res->titre,a);
}
 
 
 
void recherchelivre(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	system("cls");
	char a[50];
	int b;
	Livre *p=NULL;
	p=hl;
	gotoxy(0,0);
	printf("\xB2\xB2\ entrer titre du livre:");
	scanf("%s",&a);
	system("cls");
	while(strcmp(p->titre,a)!=0){
		p=p->nextlivre;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("\xB2\ livre introuvable ou titre incorrecte");
		printf("\n\n\nretour dans 2 secondes...");
		sleep(2);
		intro(hl,ha,he,hr);
	}
	system("cls");
	gotoxy(15,3);
	printf("livre trouve");
	gotoxy(15,5);
	printf("\xB2\ le titre du livre : ");
	puts(a);
	gotoxy(15,7);
	printf("\xB2\ les auteurs : ");
	puts(p->auteurs);
	gotoxy(15,9);
	printf("\xB2\ l'edition : ");
	puts(p->edition);
	gotoxy(15,11);
	printf("\xB2\ le nombre  d'exemplaires : %d",p->nbexemp);
	gotoxy(15,13);
	printf("\xB2\ le code du livre : %p",p->code);
	gotoxy(13,16);
	printf("Press any key to return");
	if(getch()){
		intro(hl,ha,he,hr);
	}
	
}	

 
 
void gestemprunt(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
system("cls");
int i;
gotoxy(20,3);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 SYSTEME DE GESTION DES EMPRUNTS\xB2\xB2\xB2\xB2\xB2\xB2");

gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> Ajout des emprunts");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Resilier des emprunts ");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Modification des emprunts");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> GO BACK");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
printf("Enter your choice:");
switch(getch()){
	case '1' : 
	ajoutemprunt(hl,ha,he,hr);
	calculepoints(hl,ha,he,hr);
	break;
	case '2' : 
	suppemprunt(hl,ha,he,hr);
	calculepoints(hl,ha,he,hr);
	break;
	case '3' : 
	modifemprunt(hl,ha,he,hr);
	calculepoints(hl,ha,he,hr);
	break;
	case '4' : 
	intro(hl,ha,he,hr);
	break;
	default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) gestemprunt(hl,ha,he,hr);
}

}
}


		
void rempemprunt(Emprunt *emp){
	char a[50];
	int b;
	int dd,mm,yy;
	gotoxy(15,5);
	printf("\xB2\xB2 entrer l'ID(code de 4 numeros) :");
	scanf("%d",&b);
	emp->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2 entrer date de l'emprente (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	emp->d_emprunt.d=dd;
	emp->d_emprunt.m=mm;
	emp->d_emprunt.y=yy;
	gotoxy(15,9);
	printf("\xB2\xB2 entrer date de fin de l'emprunt (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	emp->d_f_emprunt.d=dd;
	emp->d_f_emprunt.m=mm;
	emp->d_f_emprunt.y=yy;
	gotoxy(15,11);
	printf("\xB2\xB2 entrer titre du livre:");
	scanf("%s",&a);
	strcpy(emp->titre,a);
	
}


void ajoutemprunt(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	Emprunt *p=NULL;
	p=he;
	system("cls");
	int x=0;
	while(p->nextemprunt != NULL){
		x++;
		p=p->nextemprunt;
	}
	if(x!=0){
	Emprunt* newemprunt=NULL;
    newemprunt = (Emprunt*)malloc(sizeof(Emprunt));
    p->nextemprunt=newemprunt;
    newemprunt->nextemprunt=NULL;
    rempemprunt(newemprunt);
    
	}
	else{
		rempemprunt(p);
	}
	system("cls");
	printf("ajout accomplie!\n");
	printf("retour dans 3 secondes");
	sleep(3);
	gestemprunt(hl,ha,he,hr);
	
}


void modifemprunt(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	system("cls");
	int dd,mm,yy;
	char a[50];
	int b;
	Emprunt *p=NULL;
	p=he;
	gotoxy(0,0);
	printf("\xB2\xB2 entrer ID de l'abonne de l'emprunt :");
	scanf("%d",&b);
	gotoxy(0,2);
	printf("\xB2\xB2 entrer le titre du livre emprunte par l'abonne :");
	scanf("%s",&a);
	system("cls");
	while((p->id!=b)&&(strcmp(a,p->titre)!=0)){
		p=p->nextemprunt;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("emprunt introuvable");
		printf("\n\nretour dans 2 secondes");
		sleep(2);
		gestemprunt(hl,ha,he,hr);
	}
	
	system("cls");
	gotoxy(15,5);
	printf("\xB2\xB2\ entrer l'ID(code de 4 numeros):");
	scanf("%d",&b);
	p->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ entrer date de l'emprent (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	p->d_emprunt.d=dd;
	p->d_emprunt.m=mm;
	p->d_emprunt.y=yy;
	gotoxy(15,9);
	printf("\xB2\xB2\ entrer date de fin de l'emprunt (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	p->d_f_emprunt.d=dd;
	p->d_f_emprunt.m=mm;
	p->d_f_emprunt.y=yy;
	gotoxy(15,11);
	printf("\xB2\xB2\ entrer titre du livre:");
	scanf("%s",&a);
	strcpy(p->titre,a);
	system("cls");
	gotoxy(20,9);
	printf("modification accomplie!");
	sleep(5);
	gestemprunt(hl,ha,he,hr);
}


void suppemprunt(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	int x=0;
	char a[50];
	Emprunt *p =NULL;
	Emprunt *tmp=NULL;
	Emprunt *prevemprunt=NULL;
	p=he;
	system("cls");
	int lid;
	gotoxy(20,5);
	printf("\xB2\xB2\ entrer l'ID de l'abonne que vous voulez resilier son emprunt:");
	scanf("%d",&lid);
	gotoxy(20,7);
	printf("\xB2\xB2\ entrer le titre du livre emprunte par l'abonne ");
	scanf("%s",&a);
	while((p->id!=lid)&&(strcmp(a,p->titre)!=0)){
		x++;
		prevemprunt=p;
		p=p->nextemprunt;
		if (p==NULL){
			break;
		}
	}
	if(p==NULL){
		gotoxy(20,9);
		printf("ID ou titre incorrecte");
		printf("\n\nretour dans 2 secondes");
		sleep(2);
		gestemprunt(hl,ha,he,hr);
	}
	else{
		if(x==0){
			tmp=p->nextemprunt;
			free(p);
			he=tmp;
		}
		else if(p->nextemprunt==NULL){
			prevemprunt->nextemprunt=NULL;
			free(p);
		}
		else{
			prevemprunt->nextemprunt=p->nextemprunt;
			free(p);
		}
	}
	system("cls");
	gotoxy(15,5);
	printf("Resiliation accomplie!");
	sleep(2);
	gestemprunt(hl,ha,he,hr);
}
																																																																																																																						

void remplivre(Livre *livre){
	char a[50];
	int b;
	gotoxy(15,5);
	printf("\xB2\xB2\ entrer le titre :");
	scanf("%s",&a);
	strcpy(livre->titre,a);
	gotoxy(15,7);
	printf("\xB2\xB2\ entrer les auteurs:");
	scanf("%s",&a);
	strcpy(livre->auteurs,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ entrer edition:");
	scanf("%s",&a);
	strcpy(livre->edition,a);
	gotoxy(15,11);
	printf("\xB2\xB2\ entrer nombre d exemplaires:");
	scanf("%d",&b);
	livre->nbexemp=b;
	gotoxy(15,13);
	livre->code=livre;
	printf("\xB2\xB2 le code (generated) du livre est:%p\n",livre->code);
	
}


void rempabonne(Abonne* abo){
	char a[50];
	int b;
	abo->score=0;
	gotoxy(15,5);
	printf("\xB2\xB2\ entrer l'ID(code de 4 numeros) :");
	scanf("%d",&b);
	abo->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ entrer le nome et prenom:");
	scanf("%s",&a);
	strcpy(abo->fullname,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ entrer le jour de naissance:");
	scanf("%d",&b);
	abo->day=b;
	gotoxy(15,11);
	printf("\xB2\xB2\ entrer le mois de naissance:");
	scanf("%d",&b);
	abo->month=b;
	gotoxy(15,13);
	printf("\xB2\xB2\ entrer l'annee de naissance:");
	scanf("%d",&b);
	abo->year=b;
	gotoxy(15,15);
	printf("\xB2\xB2\ entrer l'annee d'etude(sous forme de caractere comme premiere annee etc...):");
	scanf("%s",&a);
	strcpy(abo->annee_etude,a);
	
	
}

void ajoutlivre(Livre *head,Abonne *ha,Emprunt *he,Reservation *hr){
	Livre *p=NULL;
	p=head;
	system("cls");
	int x=0;
	
	
	while(p->nextlivre != NULL){
		x++;
		p=p->nextlivre;
	}
	if(x!=0){
	Livre* newlivre=NULL;
    newlivre = (Livre*)malloc(sizeof(Livre));
    p->nextlivre=newlivre;
    newlivre->nextlivre=NULL;
    remplivre(newlivre);
    
	}
	else{
		remplivre(p);
	}
	printf("ajout accomplie!\n");
	printf("retour dans 3 secondes");
	sleep(3);
	gestlivre(head,ha,he,hr);
			
	}


void supplivre(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	int x=0;
	Livre *p =NULL;
	Livre *tmp=NULL;
	Livre *prevlivre=NULL;
	p=hl;
	system("cls");
	char title[50];
	gotoxy(20,5);
	printf("\xB2\xB2\ entrer titre du livre que vous voulez supprimer:");
	scanf("%s",&title);
	while(strcmp(p->titre,title)!=0){
		x++;
		prevlivre=p;
		p=p->nextlivre;
		if (p==NULL){
			break;
		}
	}
	if(p==NULL){
		gotoxy(20,9);
		printf("\xB2\xB2\ titre incorrecte ou livre indisponible");
		printf("\nretour dans 2 secondes");
		sleep(2);
		gestlivre(hl,ha,he,hr);
	}
	else{
		if(x==0){
			tmp=p->nextlivre;
			free(p);
			hl=tmp;
		}
		else if(p->nextlivre==NULL){
			prevlivre->nextlivre=NULL;
			free(p);
		}
		else{
			prevlivre->nextlivre=p->nextlivre;
			free(p);
		}
	}
	system("cls");
	gotoxy(15,5);
	printf("suppression accomplie!");
	sleep(2);
	gestlivre(hl,ha,he,hr);	
}	


void modiflivre(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	system("cls");
	char a[50];
	int b;
	Livre *p=NULL;
	p=hl;
	gotoxy(0,0);
	printf("\xB2\xB2\ entrer titre du livre que vous voulez modifier:");
	scanf("%s",&a);
	system("cls");
	while(strcmp(p->titre,a)!=0){
		p=p->nextlivre;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("livre introuvable");
		printf("\nretour dans 2 secondes");
		sleep(2);
		gestlivre(hl,ha,he,hr);
	}
	
	system("cls");
	gotoxy(15,5);
	printf("\xB2\xB2\ entrer le titre :");
	scanf("%s",&a);
	strcpy(p->titre,a);
	gotoxy(15,7);
	printf("\xB2\xB2\ entrer les auteurs:");
	scanf("%s",&a);
	strcpy(p->auteurs,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ entrer edition:");
	scanf("%s",&a);
	strcpy(p->edition,a);
	gotoxy(15,11);
	printf("\xB2\xB2\ entrer nombre d exemplaires:");
	scanf("%d",&b);
	p->nbexemp=b;
	system("cls");
	gotoxy(20,9);
	printf("modification accomplie!");
	sleep(5);
	gestlivre(hl,ha,he,hr);
}

void gestabonne(Livre*hl,Abonne *ha,Emprunt *he,Reservation *hr){

system("cls");
int i;
gotoxy(20,3);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 SYSTEME DE GESTION DES ABONNES\xB2\xB2\xB2\xB2\xB2\xB2");

gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> Ajout des abonnes   ");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Supprimer des abonnes ");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Modification des abonnes");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> GO BACK");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
printf("Enter your choice:");
switch(getch()){
	case '1' : 
	ajoutabonne(hl,ha,he,hr);
	break;
	case '2' : 
	suppabonne(hl,ha,he,hr);
	break;
	case '3' : 
	modifabonne(hl,ha,he,hr);
	break;
	case '4' : 
	intro(hl,ha,he,hr);
	break;
	default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) gestabonne(hl,ha,he,hr);
}

}
}

void ajoutabonne(Livre*hl,Abonne*ha,Emprunt *he,Reservation *hr){
	Abonne *p=NULL;
	p=ha;
	system("cls");
	int x=0;
	while(p->nextabonne != NULL){
		x++;
		p=p->nextabonne;
	}
	if(x!=0){
	Abonne* newabonne=NULL;
    newabonne = (Abonne*)malloc(sizeof(Abonne));
    p->nextabonne=newabonne;
    newabonne->nextabonne=NULL;
    rempabonne(newabonne);
    
	}
	else{
		rempabonne(p);
	}
	printf("ajout accomplie!\n");
	printf("retour dans 3 secondes");
	sleep(3);
	gestabonne(hl,ha,he,hr);
			
	}
	

void suppabonne(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	int x=0;
	Abonne *p =NULL;
	Abonne *tmp=NULL;
	Abonne *prevabonne=NULL;
	p=ha;
	system("cls");
	int lid;
	gotoxy(20,5);
	printf("\xB2\xB2\ entrer l'ID de l'abonne que vous voulez supprimer:");
	scanf("%d",&lid);
	while(p->id!=lid){
		x++;
		prevabonne=p;
		p=p->nextabonne;
		if (p==NULL){
			break;
		}
	}
	if(p==NULL){
		gotoxy(20,9);
		printf("ID incorrecte");
		printf("\n\nretour dans 2 secondes");
		sleep(2);
		gestlivre(hl,ha,he,hr);
	}
	else{
		if(x==0){
			tmp=p->nextabonne;
			free(p);
			ha=tmp;
		}
		else if(p->nextabonne==NULL){
			prevabonne->nextabonne=NULL;
			free(p);
		}
		else{
			prevabonne->nextabonne=p->nextabonne;
			free(p);
		}
	}
	system("cls");
	gotoxy(15,5);
	printf("suppression accomplie!");
	sleep(2);
	gestabonne(hl,ha,he,hr);	
}	


void modifabonne(Livre *hl,Abonne *ha,Emprunt *he,Reservation *hr){
	system("cls");
	char a[50];
	int b;
	Abonne *p=NULL;
	p=ha;
	gotoxy(0,0);
	printf("\xB2\xB2\ entrer ID de l'abonne que vous voulez modifier:");
	scanf("%d",&b);
	system("cls");
	while(p->id!=b){
		p=p->nextabonne;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("abonne introuvable");
		printf("\n\nretour dans 2 secondes");
		sleep(2);
		gestlivre(hl,ha,he,hr);
	}
	
	system("cls");
	gotoxy(15,5);
	printf("\xB2\xB2\ entrer l'ID:");
	scanf("%d",&b);
	p->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ entrer le nom et prenom:");
	scanf("%s",&a);
	strcpy(p->fullname,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ entrer le jour de naissance:");
	scanf("%d",&b);
	p->day=b;
	gotoxy(15,11);
	printf("\xB2\xB2\ entrer le mois de naissance:");
	scanf("%d",&b);
	p->month=b;
	gotoxy(15,13);
	printf("\xB2\xB2\ entrer l'annee de naissance:");
	scanf("%d",&b);
	p->year=b;
	gotoxy(15,15);
	printf("\xB2\xB2\ entrer l'annee d'etude(sous forme de caractere comme premiere annee etc...):");
	scanf("%s",&a);
	strcpy(p->annee_etude,a);
	system("cls");
	gotoxy(20,9);
	printf("modification accomplie!");
	sleep(5);
	gestabonne(hl,ha,he,hr);
}


void gestlivre(Livre *hl,Abonne*ha,Emprunt *he,Reservation *hr){

system("cls");
int i;
gotoxy(20,3);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 SYSTEME DE GESTION DES LIVRES\xB2\xB2\xB2\xB2\xB2\xB2");

gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> Ajout des livres   ");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Supprimer des livres ");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Modification des livres");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> GO BACK");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
printf("Enter your choice:");
switch(getch()){
	case '1' : 
	ajoutlivre(hl,ha,he,hr);
	break;
	case '2' : 
	supplivre(hl,ha,he,hr);
	break;
	case '3' : 
	modiflivre(hl,ha,he,hr);
	break;
	case '4' : 
	intro(hl,ha,he,hr);
	break;
	default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) gestlivre(hl,ha,he,hr);
}

}
}

void intro(Livre*hl,Abonne *ha,Emprunt *he,Reservation *hr)
{
system("cls");
int i;
gotoxy(20,2);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 SYSTEME DE GESTION DU BIBLIOTHEQUE\xB2\xB2\xB2\xB2\xB2\xB2");


gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> Gestion des livres   ");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Gestion des abonnes");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Gestion des emprunts");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> Rechercher un livre");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2 5=> Gestion des reservations");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2 6=> Affichage des 3 premiers etudiants ( avec tri par insertion )");
gotoxy(20,17);
printf("\xB2\xB2\xB2\xB2 7=> Fermer le programme (CELA VA RENITIALISER LA BASE DES DONNEES!!!)");
gotoxy(20,20);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,23);
printf("Enter your choice:");
gotoxy(30,25);
printf(" Fait par :");
gotoxy(32,27);
printf("\t MOHAMMED FATHI");
gotoxy(41,28);
printf(":::::::::::::::::::::::::::::::::::::::::");
gotoxy(41,29);
printf(":::::::::::::::::::::::::::::::::::::::::");
gotoxy(30,32);
printf(".............................................................>");

switch(getch())
{
case '1':
gestlivre(hl,ha,he,hr);
break;
case '2':
gestabonne(hl,ha,he,hr);
break;
case '3':
gestemprunt(hl,ha,he,hr);
break;
case '4':
recherchelivre(hl,ha,he,hr);
break;
case '5':
gestreservation(hl,ha,he,hr);
break;
case '6':
classement(hl,ha,he,hr);
break;
case '7':
	exit(0);
default:
{
gotoxy(10,23);
printf("\achoix incorrecte!! Le choix doit figurer parmi les options au-dessus. ");
if(getch()) intro(hl,ha,he,hr);
}
}

}

int main(){
	
	Livre* headlivre=NULL;
    headlivre = (Livre*)malloc(sizeof(Livre));
    headlivre->nextlivre=NULL;
    
    Abonne* headabonne=NULL;
    headabonne = (Abonne*)malloc(sizeof(Abonne));
    headabonne->nextabonne=NULL;
    
    Emprunt* heademprunt=NULL;
    heademprunt = (Emprunt*)malloc(sizeof(Emprunt));
    heademprunt->nextemprunt=NULL;
    
    Reservation* headreservation=NULL;
    headreservation = (Reservation*)malloc(sizeof(Reservation));
    headreservation->nextreservation=NULL;
    

    intro(headlivre,headabonne,heademprunt,headreservation);
    

	return 0;
}
