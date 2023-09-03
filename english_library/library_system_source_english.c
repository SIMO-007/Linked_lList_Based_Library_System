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

typedef struct book{
	char title[50];
	char authors[100];
	char edition[50];
	int nbexemp;
	struct book* code;
	struct book* nextbook;
	
}Book;

typedef struct sub{
	int score;
	int id;
	char fullname[50];
	int day;
	int month;
	int year;
	char year_study[50];
	struct sub* nextsub;
}Sub;

typedef struct date{
	int d,m,y;
}Date;

typedef struct borrow{
	int id;
	Date d_borrow;
	Date d_f_borrow;
	Date d_retourne_book;
	char title[50];
	struct borrow* nextborrow;
}Borrow;


typedef struct reservation{
	int id;
	char title[50];
	struct reservation *nextreservation;
}Reservation;


typedef struct sorting{
	char name[75];
	int score;
}Class;

void intro();
void rempbook();
void addbook();
void removebook();
void modifbook();
void managebook();
void addsub();
void removesub();
void modifsub();
void managesub();
void addborrow();
void removeborrow();
void modifborrow();
void manageborrow();
void searchbook();
void managereservation();
void rempreservation();
void calculepoints();
void sorting();
void insertionsort();


void calculepoints(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	Sub *pa=NULL;
	Borrow *pe=NULL;
	Borrow *pe2=NULL;
	Borrow *pe3=NULL;
	pa=ha;
	pe=he;
	int ID,x=0,la=1,le=1;
	while((pa->nextsub!=NULL) || (pa==ha) || (la==1)){
		ID=pa->id;
		x=0;
		while(pe->nextborrow!=NULL || pe==he || le==1){
			if(pe->id==ID){
				x++;
			}
			pe=pe->nextborrow;
			if(pe->nextborrow==NULL){
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
		if(pa->nextsub==NULL){
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
 

 
void sorting(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	system("cls");
	Class *first=(Class*)malloc(sizeof(Class));
	Class *second=(Class*)malloc(sizeof(Class));
	Class *third=(Class*)malloc(sizeof(Class));
	Sub *pa=NULL;
	Sub *tmp=NULL;
	pa=ha;
	tmp=ha;
	int x=0;
	if((pa==NULL)||(pa->nextsub==NULL)||(pa->nextsub->nextsub==NULL)){
		gotoxy(15,5);
		printf("number of subscribers is insufficient");
		gotoxy(15,7);
		printf("going back in 3s...");
		sleep(3);
		intro(hl,ha,he,hr);
	}
	int count=0;
 
    while(tmp != NULL){
       tmp = tmp->nextsub;
        count++;
 
    }
    
    int scorelist[count];
    while(pa!=NULL){
    	scorelist[x]=pa->score;
    	x++;
    	pa=pa->nextsub;
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
		pa=pa->nextsub;
	}
	gotoxy(15,5);
	printf("\xB2\xB2\ ranking of the subs ");
	gotoxy(15,8);
	printf("\xB2\ first : ");
	puts(first->name);
	gotoxy(18,10);
	printf("\xB2\ with a score of %d points",first->score);
	gotoxy(15,14);
	printf("\xB2\ second : ");
	puts(second->name);
	gotoxy(18,16);
	printf("\xB2\ with a score of %d points",second->score);
	gotoxy(15,20);
	printf("\xB2\ third : ");
	puts(third->name);
	gotoxy(18,22);
	printf("\xB2\ with a score of %d points",third->score);
	gotoxy(12,25);
	printf("going back in 5 seconds...");
	sleep(5);
	intro(hl,ha,he,hr);
}
 
 
void managereservation(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
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
	printf("added successfully");
	gotoxy(12,12);
	printf("back in 3 seconds...");
	sleep(3);
	intro(hl,ha,he,hr);
	
} 


void rempreservation(Reservation *res){
	system("cls");
	char a[50];
	int b;
	gotoxy(15,5);
	printf("\xB2\xB2\ enter ID of the student making the reservation : ");
	scanf("%d",&b);
	res->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ enter the title of the book :");
	scanf("%s",&a);
	strcpy(res->title,a);
}
 
 
 
void searchbook(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	system("cls");
	char a[50];
	int b;
	Book *p=NULL;
	p=hl;
	gotoxy(0,0);
	printf("\xB2\xB2\ enter the title of the book:");
	scanf("%s",&a);
	system("cls");
	while(strcmp(p->title,a)!=0){
		p=p->nextbook;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("\xB2\ book not found or incorrect title");
		printf("\n\n\n going back in 2 seconds...");
		sleep(2);
		intro(hl,ha,he,hr);
	}
	system("cls");
	gotoxy(15,3);
	printf("book found");
	gotoxy(15,5);
	printf("\xB2\ book title : ");
	puts(a);
	gotoxy(15,7);
	printf("\xB2\ authors : ");
	puts(p->authors);
	gotoxy(15,9);
	printf("\xB2\ edition : ");
	puts(p->edition);
	gotoxy(15,11);
	printf("\xB2\ the number of exemplaries : %d",p->nbexemp);
	gotoxy(15,13);
	printf("\xB2\ the code of the book : %p",p->code);
	gotoxy(13,16);
	printf("Press any key to return");
	if(getch()){
		intro(hl,ha,he,hr);
	}
	
}	

 
 
void manageborrow(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
system("cls");
int i;
gotoxy(20,3);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 LOAN MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2");

gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> add a loan");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> remouve a loan ");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Modify loan");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> GO BACK");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
printf("Enter choice:");
switch(getch()){
	case '1' : 
	addborrow(hl,ha,he,hr);
	calculepoints(hl,ha,he,hr);
	break;
	case '2' : 
	removeborrow(hl,ha,he,hr);
	calculepoints(hl,ha,he,hr);
	break;
	case '3' : 
	modifborrow(hl,ha,he,hr);
	calculepoints(hl,ha,he,hr);
	break;
	case '4' : 
	intro(hl,ha,he,hr);
	break;
	default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) manageborrow(hl,ha,he,hr);
}

}
}


		
void rempborrow(Borrow *emp){
	char a[50];
	int b;
	int dd,mm,yy;
	gotoxy(15,5);
	printf("\xB2\xB2 enter ID(4 number code) :");
	scanf("%d",&b);
	emp->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2 enter date of borrow (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	emp->d_borrow.d=dd;
	emp->d_borrow.m=mm;
	emp->d_borrow.y=yy;
	gotoxy(15,9);
	printf("\xB2\xB2 enter end date of the borrow (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	emp->d_f_borrow.d=dd;
	emp->d_f_borrow.m=mm;
	emp->d_f_borrow.y=yy;
	gotoxy(15,11);
	printf("\xB2\xB2 enter title of the book:");
	scanf("%s",&a);
	strcpy(emp->title,a);
	
}


void addborrow(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	Borrow *p=NULL;
	p=he;
	system("cls");
	int x=0;
	while(p->nextborrow != NULL){
		x++;
		p=p->nextborrow;
	}
	if(x!=0){
	Borrow* newborrow=NULL;
    newborrow = (Borrow*)malloc(sizeof(Borrow));
    p->nextborrow=newborrow;
    newborrow->nextborrow=NULL;
    rempborrow(newborrow);
    
	}
	else{
		rempborrow(p);
	}
	system("cls");
	printf("added successfully!\n");
	printf("back in 3 seconds...");
	sleep(3);
	manageborrow(hl,ha,he,hr);
	
}


void modifborrow(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	system("cls");
	int dd,mm,yy;
	char a[50];
	int b;
	Borrow *p=NULL;
	p=he;
	gotoxy(0,0);
	printf("\xB2\xB2 enter the subscriber ID :");
	scanf("%d",&b);
	gotoxy(0,2);
	printf("\xB2\xB2 enter the title of the book borrowed :");
	scanf("%s",&a);
	system("cls");
	while((p->id!=b)&&(strcmp(a,p->title)!=0)){
		p=p->nextborrow;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("borrow not found");
		printf("\n\n back in 2 seconds...");
		sleep(2);
		manageborrow(hl,ha,he,hr);
	}
	
	system("cls");
	gotoxy(15,5);
	printf("\xB2\xB2\ enter ID(4 nb code):");
	scanf("%d",&b);
	p->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ enter loan date (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	p->d_borrow.d=dd;
	p->d_borrow.m=mm;
	p->d_borrow.y=yy;
	gotoxy(15,9);
	printf("\xB2\xB2\ enter end date of the loan (SEPERATED WITH SPACES!):");
	scanf("%d %d %d",&dd,&mm,&yy);
	p->d_f_borrow.d=dd;
	p->d_f_borrow.m=mm;
	p->d_f_borrow.y=yy;
	gotoxy(15,11);
	printf("\xB2\xB2\ enter book title:");
	scanf("%s",&a);
	strcpy(p->title,a);
	system("cls");
	gotoxy(20,9);
	printf("modified successfully!");
	sleep(5);
	manageborrow(hl,ha,he,hr);
}


void removeborrow(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	int x=0;
	char a[50];
	Borrow *p =NULL;
	Borrow *tmp=NULL;
	Borrow *prevborrow=NULL;
	p=he;
	system("cls");
	int lid;
	gotoxy(20,5);
	printf("\xB2\xB2\ enter the ID of the subscriber that borrowed :");
	scanf("%d",&lid);
	gotoxy(20,7);
	printf("\xB2\xB2\ enter the book title : ");
	scanf("%s",&a);
	while((p->id!=lid)&&(strcmp(a,p->title)!=0)){
		x++;
		prevborrow=p;
		p=p->nextborrow;
		if (p==NULL){
			break;
		}
	}
	if(p==NULL){
		gotoxy(20,9);
		printf("ID ou title incorrect");
		printf("\n\n back in 2 seconds...");
		sleep(2);
		manageborrow(hl,ha,he,hr);
	}
	else{
		if(x==0){
			tmp=p->nextborrow;
			free(p);
			he=tmp;
		}
		else if(p->nextborrow==NULL){
			prevborrow->nextborrow=NULL;
			free(p);
		}
		else{
			prevborrow->nextborrow=p->nextborrow;
			free(p);
		}
	}
	system("cls");
	gotoxy(15,5);
	printf("Removed successfully!");
	sleep(2);
	manageborrow(hl,ha,he,hr);
}
																																																																																																																						

void rempbook(Book *book){
	char a[50];
	int b;
	gotoxy(15,5);
	printf("\xB2\xB2\ enter title :");
	scanf("%s",&a);
	strcpy(book->title,a);
	gotoxy(15,7);
	printf("\xB2\xB2\ enter the authors:");
	scanf("%s",&a);
	strcpy(book->authors,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ enter edition:");
	scanf("%s",&a);
	strcpy(book->edition,a);
	gotoxy(15,11);
	printf("\xB2\xB2\ enter the number of exemplaries:");
	scanf("%d",&b);
	book->nbexemp=b;
	gotoxy(15,13);
	book->code=book;
	printf("\xB2\xB2  the generated code of the book is:%p\n",book->code);
	
}


void rempsub(Sub* abo){
	char a[50];
	int b;
	abo->score=0;
	gotoxy(15,5);
	printf("\xB2\xB2\ enter the ID(code de 4 numeros) :");
	scanf("%d",&b);
	abo->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ enter name and surname");
	scanf("%s",&a);
	strcpy(abo->fullname,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ enter le day of birth:");
	scanf("%d",&b);
	abo->day=b;
	gotoxy(15,11);
	printf("\xB2\xB2\ enter le month of birth:");
	scanf("%d",&b);
	abo->month=b;
	gotoxy(15,13);
	printf("\xB2\xB2\ enter the year of birth:");
	scanf("%d",&b);
	abo->year=b;
	gotoxy(15,15);
	printf("\xB2\xB2\ enter the year of study(in string form not numbers):");
	scanf("%s",&a);
	strcpy(abo->year_study,a);
	
	
}

void addbook(Book *head,Sub *ha,Borrow *he,Reservation *hr){
	Book *p=NULL;
	p=head;
	system("cls");
	int x=0;
	
	
	while(p->nextbook != NULL){
		x++;
		p=p->nextbook;
	}
	if(x!=0){
	Book* newbook=NULL;
    newbook = (Book*)malloc(sizeof(Book));
    p->nextbook=newbook;
    newbook->nextbook=NULL;
    rempbook(newbook);
    
	}
	else{
		rempbook(p);
	}
	printf("add successfully!\n");
	printf(" back in 3 seconds...");
	sleep(3);
	managebook(head,ha,he,hr);
			
	}


void removebook(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	int x=0;
	Book *p =NULL;
	Book *tmp=NULL;
	Book *prevbook=NULL;
	p=hl;
	system("cls");
	char title[50];
	gotoxy(20,5);
	printf("\xB2\xB2\ enter title of the book to remove:");
	scanf("%s",&title);
	while(strcmp(p->title,title)!=0){
		x++;
		prevbook=p;
		p=p->nextbook;
		if (p==NULL){
			break;
		}
	}
	if(p==NULL){
		gotoxy(20,9);
		printf("\xB2\xB2\ title incorrect ou book not found");
		printf("\n back in 2 seconds...");
		sleep(2);
		managebook(hl,ha,he,hr);
	}
	else{
		if(x==0){
			tmp=p->nextbook;
			free(p);
			hl=tmp;
		}
		else if(p->nextbook==NULL){
			prevbook->nextbook=NULL;
			free(p);
		}
		else{
			prevbook->nextbook=p->nextbook;
			free(p);
		}
	}
	system("cls");
	gotoxy(15,5);
	printf("removed successfully!");
	sleep(2);
	managebook(hl,ha,he,hr);	
}	


void modifbook(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	system("cls");
	char a[50];
	int b;
	Book *p=NULL;
	p=hl;
	gotoxy(0,0);
	printf("\xB2\xB2\ enter book title to modify:");
	scanf("%s",&a);
	system("cls");
	while(strcmp(p->title,a)!=0){
		p=p->nextbook;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("book not found");
		printf("\n back in 2 seconds...");
		sleep(2);
		managebook(hl,ha,he,hr);
	}
	
	system("cls");
	gotoxy(15,5);
	printf("\xB2\xB2\ enter title :");
	scanf("%s",&a);
	strcpy(p->title,a);
	gotoxy(15,7);
	printf("\xB2\xB2\ enter authors:");
	scanf("%s",&a);
	strcpy(p->authors,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ enter edition:");
	scanf("%s",&a);
	strcpy(p->edition,a);
	gotoxy(15,11);
	printf("\xB2\xB2\ enter number of exemplaries:");
	scanf("%d",&b);
	p->nbexemp=b;
	system("cls");
	gotoxy(20,9);
	printf("modified successfully!");
	sleep(5);
	managebook(hl,ha,he,hr);
}

void managesub(Book*hl,Sub *ha,Borrow *he,Reservation *hr){

system("cls");
int i;
gotoxy(20,3);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 SUBSCRIPTION MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2");

gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> Add subs   ");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Remouve subs ");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Modify subs");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> GO BACK");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
printf("Enter your choice:");
switch(getch()){
	case '1' : 
	addsub(hl,ha,he,hr);
	break;
	case '2' : 
	removesub(hl,ha,he,hr);
	break;
	case '3' : 
	modifsub(hl,ha,he,hr);
	break;
	case '4' : 
	intro(hl,ha,he,hr);
	break;
	default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) managesub(hl,ha,he,hr);
}

}
}

void addsub(Book*hl,Sub*ha,Borrow *he,Reservation *hr){
	Sub *p=NULL;
	p=ha;
	system("cls");
	int x=0;
	while(p->nextsub != NULL){
		x++;
		p=p->nextsub;
	}
	if(x!=0){
	Sub* newsub=NULL;
    newsub = (Sub*)malloc(sizeof(Sub));
    p->nextsub=newsub;
    newsub->nextsub=NULL;
    rempsub(newsub);
    
	}
	else{
		rempsub(p);
	}
	printf("added successfully!\n");
	printf(" back in 3 seconds...");
	sleep(3);
	managesub(hl,ha,he,hr);
			
	}
	

void removesub(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	int x=0;
	Sub *p =NULL;
	Sub *tmp=NULL;
	Sub *prevsub=NULL;
	p=ha;
	system("cls");
	int lid;
	gotoxy(20,5);
	printf("\xB2\xB2\ enter the ID of the sub to remove:");
	scanf("%d",&lid);
	while(p->id!=lid){
		x++;
		prevsub=p;
		p=p->nextsub;
		if (p==NULL){
			break;
		}
	}
	if(p==NULL){
		gotoxy(20,9);
		printf("ID incorrect");
		printf("\n\n back in 2 seconds...");
		sleep(2);
		managebook(hl,ha,he,hr);
	}
	else{
		if(x==0){
			tmp=p->nextsub;
			free(p);
			ha=tmp;
		}
		else if(p->nextsub==NULL){
			prevsub->nextsub=NULL;
			free(p);
		}
		else{
			prevsub->nextsub=p->nextsub;
			free(p);
		}
	}
	system("cls");
	gotoxy(15,5);
	printf("removed successfully!");
	sleep(2);
	managesub(hl,ha,he,hr);	
}	


void modifsub(Book *hl,Sub *ha,Borrow *he,Reservation *hr){
	system("cls");
	char a[50];
	int b;
	Sub *p=NULL;
	p=ha;
	gotoxy(0,0);
	printf("\xB2\xB2\ enter ID of the sub to modify:");
	scanf("%d",&b);
	system("cls");
	while(p->id!=b){
		p=p->nextsub;
		if(p==NULL){
		break;
	}
		
	}
	if(p==NULL){
		gotoxy(20,8);
		printf("sub not found");
		printf("\n\n back in 2 seconds...");
		sleep(2);
		managebook(hl,ha,he,hr);
	}
	
	system("cls");
	gotoxy(15,5);
	printf("\xB2\xB2\ enter the ID:");
	scanf("%d",&b);
	p->id=b;
	gotoxy(15,7);
	printf("\xB2\xB2\ enter name and surname:");
	scanf("%s",&a);
	strcpy(p->fullname,a);
	gotoxy(15,9);
	printf("\xB2\xB2\ enter le day of birth:");
	scanf("%d",&b);
	p->day=b;
	gotoxy(15,11);
	printf("\xB2\xB2\ enter le month of birth:");
	scanf("%d",&b);
	p->month=b;
	gotoxy(15,13);
	printf("\xB2\xB2\ enter the year of birth:");
	scanf("%d",&b);
	p->year=b;
	gotoxy(15,15);
	printf("\xB2\xB2\ enter the year of study(in string form):");
	scanf("%s",&a);
	strcpy(p->year_study,a);
	system("cls");
	gotoxy(20,9);
	printf("Modified successfully!");
	sleep(5);
	managesub(hl,ha,he,hr);
}


void managebook(Book *hl,Sub*ha,Borrow *he,Reservation *hr){

system("cls");
int i;
gotoxy(20,3);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 BOOK MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2");

gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> add books   ");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Remouve books ");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Modify books");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> GO BACK");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,20);
printf("Enter your choice:");
switch(getch()){
	case '1' : 
	addbook(hl,ha,he,hr);
	break;
	case '2' : 
	removebook(hl,ha,he,hr);
	break;
	case '3' : 
	modifbook(hl,ha,he,hr);
	break;
	case '4' : 
	intro(hl,ha,he,hr);
	break;
	default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) managebook(hl,ha,he,hr);
}

}
}

void intro(Book*hl,Sub *ha,Borrow *he,Reservation *hr)
{
system("cls");
int i;
gotoxy(20,2);

printf("\xB2\xB2\xB2\xB2\xB2\xB2 LIBRARY MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2");


gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2 1=> Book management  ");
gotoxy(20,7);
printf("\xB2\xB2\xB2\xB2 2=> Subscription management");
gotoxy(20,9);
printf("\xB2\xB2\xB2\xB2 3=> Loan management");
gotoxy(20,11);
printf("\xB2\xB2\xB2\xB2 4=> Search a book");
gotoxy(20,13);
printf("\xB2\xB2\xB2\xB2 5=> Reservation management");
gotoxy(20,15);
printf("\xB2\xB2\xB2\xB2 6=> Show top 3 subs ( with insertion sort )");
gotoxy(20,17);
printf("\xB2\xB2\xB2\xB2 7=> Close program (Database will be deleted!!!)");
gotoxy(20,20);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,23);
printf("Enter your choice:");
gotoxy(30,25);
printf(" Made by :");
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
managebook(hl,ha,he,hr);
break;
case '2':
managesub(hl,ha,he,hr);
break;
case '3':
manageborrow(hl,ha,he,hr);
break;
case '4':
searchbook(hl,ha,he,hr);
break;
case '5':
managereservation(hl,ha,he,hr);
break;
case '6':
sorting(hl,ha,he,hr);
break;
case '7':
	exit(0);
default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-enter correct option");
if(getch()) intro(hl,ha,he,hr);
}
}

}

int main(){
	
	Book* headbook=NULL;
    headbook = (Book*)malloc(sizeof(Book));
    headbook->nextbook=NULL;
    
    Sub* headsub=NULL;
    headsub = (Sub*)malloc(sizeof(Sub));
    headsub->nextsub=NULL;
    
    Borrow* headborrow=NULL;
    headborrow = (Borrow*)malloc(sizeof(Borrow));
    headborrow->nextborrow=NULL;
    
    Reservation* headreservation=NULL;
    headreservation = (Reservation*)malloc(sizeof(Reservation));
    headreservation->nextreservation=NULL;
    

    intro(headbook,headsub,headborrow,headreservation);
    

	return 0;
}
