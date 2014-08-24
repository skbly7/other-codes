#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <ctype.h>
#include <string.h>
#define MAXDB 500



int i;
long int phone[MAXDB+1];
int room[MAXDB+1];

long int phone_tmp[MAXDB+1];
int room_tmp[MAXDB+1];
void add_entry(int, long int);
int total_entry=0;
int current_e_add;
int delete_entry(int, long int);
int find_phone_number(long int);
int FindRoom(int);
int phone_found,room_found;
int del_entry;
int tot_del_entry=0;
int ListAll(void);
int sort_entries(char);
int GeTotalEntries(void);
int chkdig (char str[], int range);
char menu_flat(void);
char menu_hostel(void);
void loaddatabase(void);
void menu_exit(void);
void screen_draw_start(void);
void screen_draw_hostel(void);
void screen_draw_flat(void);
void remakescreen(void);
char choice_system(void);
void remakescreen_start(void);
void flat(void);
void hostel(void);
char menu_hostel(void);
char menu_flat(void);
char dbload[80];


void main()
{
char special;
special=choice_system();
if(special=='1')
hostel();
else
if(special=='2')
flat();
else
if(special=='3')
{
     clrscr();
     gotoxy(23,12);
     printf("Thank you for using this program");
     gotoxy(23,13);
     printf("Coded by: Shivam");
     gotoxy(33,14);
     printf("Akshay");
     gotoxy(33,15);
     printf("Aayush");
     getch();	 
}
else
main();
}

void flat(void)
{
char iroom[80],iphone[80],add_quit;
char option,sortopt,exit_opt;
int phone_check,room_check,delete_check,sort_check,list_check;
int iroom_search,iroom_del;
int int_iroom,total_entries;
int error_iphone,error_iroom;
long int longint_iphone;
long int iphone_search;
long int iphone_del;


strcpy(dbload, "DATABASE ERROR...");

do
 {
  do
   { option = menu_flat();
     if (option == '1')
     {  current_e_add=0;
	for (i=total_entry; i < MAXDB; i++)
	{   clrscr();
	    remakescreen();
	    screen_draw_flat();
	    gotoxy(1,4);
	    printf("## ADD NEW ENTRY ##");
	    gotoxy(1,25);
	    cprintf("Please Add Your Entry, leave blank to reach to Main Menu..");
	    gotoxy(1,6);
	    printf("Enter Room  Number[%3d]: ",i+1);
	    gets(iroom);

	    if (iroom[0] == '\0' )
	    {  gotoxy(1,25);
	       cprintf("You chose to quit: Entry %d was not added to the database.",i+1);
	       getch();
	       break;
	    }
	    printf("Enter Phone Number[%3d]: ",i+1);
	    gets(iphone);

	    if (iphone[0] == '\0')
	    {  gotoxy(1,25);
	       cprintf("You chose to quit: Entry %d was not added to the database.",i+1);
	       getch();
	       break;
	    }

	    error_iroom = chkdig(iroom,4);
	    error_iphone = chkdig(iphone,8);

	    while(error_iroom != 0)
	    {	if (error_iroom == -1)
		{  clrscr();
		   remakescreen();
		   screen_draw_flat();
		   gotoxy(1,4);
		   printf("## ADD NEW ENTRY ##");
		   gotoxy(1,25);
		   cprintf("Error: Room  Number - out of Range, Your entry was greater than 4 digits. ");
		   gotoxy(1,6);
		   printf("Renter Room  Number[%3d]: ",i+1);
		   gets(iroom);
		}
		if (error_iroom == -2)
		{  clrscr();
		   remakescreen();
		   screen_draw_flat();
		   gotoxy(1,4);
		   printf("*** Add Entry ***");
		   gotoxy(1,25);
		   cprintf("Error: Room  Number - Character(s) detected, character(s) are not allowed.");
		   gotoxy(1,6);
		   printf("Renter Room  Number[%3d]: ",i+1);
		   gets(iroom);
		}
		error_iroom = chkdig(iroom,4);
	    }
	    while(error_iphone !=0)
		{	if (error_iphone == -1)
		{  clrscr();
		   remakescreen();
		   screen_draw_flat();
		   gotoxy(1,4);
		   printf("## ADD NEW ENTRY ##");
		   gotoxy(1,25);
		   cprintf("Error: Phone Number - out of Range, Your entry was greater than 8 digits. ");
		   gotoxy(1,6);
		   printf("Room  Number[%3d] Entry: %s",i+1,iroom);
		   gotoxy(1,7);
		   printf("Renter Phone Number[%3d]: ",i+1);
		   gets(iphone);
		}
		if (error_iphone == -2)
		{  clrscr();
		   remakescreen();
		   screen_draw_flat();
		   gotoxy(1,4);
		   printf("## ADD NEW ENTRY ##");
		   gotoxy(1,25);
		   cprintf("Error: Phone Number - Character(s) detected, character(s) are not allowed.");
		   gotoxy(1,6);
		   printf("Room  Number[%3d] Entry: %s",i+1,iroom);
		   gotoxy(1,7);
		   printf("Renter Phone Number[%3d]: ",i+1);
		   gets(iphone);
		}
		error_iphone = chkdig(iphone,8);
	    }
	    if (error_iroom == 0 && error_iphone == 0)
	    {  int_iroom = atoi(iroom);
	       longint_iphone = atol(iphone);

	       current_e_add++;
	       add_entry(int_iroom,longint_iphone);
	    }
	}
	if (total_entry == MAXDB)
	{  gotoxy(1,25);
	   cprintf("\aDatabase is full!: %d entries were added, ",total_entry);
	   cprintf("that is the Maximum No. I can hold.");
	   getch();
	}
     }
     else
     if (option == '2')
     {  del_entry = 0; 	clrscr();
	remakescreen();
	screen_draw_flat();
	gotoxy(1,4);
	printf("## Delete Entry ##");
	gotoxy(1,6);
	printf("Enter room  number to delete: ");
	scanf("%d",&iroom_del);
	flushall();

	printf("Enter phone number to delete: ");
	scanf("%ld",&iphone_del);
	flushall();

	delete_check = delete_entry(iroom_del,iphone_del);

	if (delete_check == 0)
	{  gotoxy(1,25);
	   cprintf("Successful: There are presently %d entries in the database, ",total_entry);
	   cprintf("deleted %d.",del_entry);
	   getch();
	}
	if (delete_check == -1) 
	{  gotoxy(1,25);
	   cprintf("Error: The Room No./Phone No. Your looking for was Not Found.                  ");
	   getch();
	}

     }
     else
     if (option == '3')
     {  phone_found = 0;
	clrscr();
	remakescreen();
	screen_draw_flat();
	gotoxy(1,4);
	printf("## Find Room Number ##");

	gotoxy(1,6);
	printf("Enter the phone number to search for: ");
	scanf("%ld",&iphone_search);
	flushall(); 

	phone_check = find_phone_number(iphone_search);

	if (phone_check == 0)
	{  gotoxy(1,25);
	   cprintf("Successful: There are presently %d entries in the database, ",total_entry);

	   printf("found %d.",phone_found);
	   getch();
	}
	if (phone_check == -1) 
	{  gotoxy(1,25);
	   cprintf("Error: The Phone No. Your looking for was Not Found.");
	   getch();
	}
     }
     else
     if (option == '4')
     {  room_found = 0;
	clrscr();
	remakescreen();
	screen_draw_flat();
	gotoxy(1,4);
	printf("## Find Phone Number ##");

	gotoxy(1,6);
	printf("Enter the room number to search for: ");
	scanf("%d",&iroom_search);
	flushall();

	room_check = FindRoom(iroom_search);

	if (room_check == 0) 
	{  gotoxy(1,25);
	   cprintf("Successful: There are presently %d entries in the database, ",total_entry);
	   cprintf("found %d.",room_found);
	   getch();
	}
	if (room_check == -1) 
	{  gotoxy(1,25);
	   cprintf("Error: The Room No. Your looking for was Not Found.");
	   getch();
	}

     }
     else
     if (option == '5')
     {  clrscr();
	remakescreen();
	screen_draw_flat();
	gotoxy(1,4);
	printf("## ListAll ##\n\n");

	list_check = ListAll();

	if (list_check == 0)
	{  gotoxy(1,25);
	   cprintf("List Sucuessful");
	   getch();
	}
	if (list_check == -1)
	{
	   gotoxy(1,25);
	   cprintf("Empty List");
	   getch();
	}
     }
     else
     if (option == '6')
     {  total_entries = GeTotalEntries();
	gotoxy(1,25);
	cprintf("There are presently %d entries stored in the Database.",total_entries);
	getch();
     }
     else
     if (option == '7') 
   {  clrscr();
	remakescreen();
	screen_draw_flat();
	gotoxy(1,4);
	printf("## Sort All Entries ##");
	gotoxy(1,6);
	printf("Press 'A' to sort database in [A]scending order");
	gotoxy(1,7);
	printf("Press 'D' to sort database in [D]escending order.");
	gotoxy(1,9);
	printf("Note: Database is sorted by phone no. entries.");
	sortopt = getch();
	flushall();

	sort_check = sort_entries(sortopt);
	getch();
	if (sort_check == 0)
	{  gotoxy(1,25);
	   cprintf("Database was successfully Sorted.                                      ");
	   getch();
	}
	if (sort_check == -1)
	{  gotoxy(1,25);
	   cprintf("Database was not sorted - Database is empty!");
	   getch();
	}
     }
     else
     if (option == '8') 
     {  clrscr();
	remakescreen();
	screen_draw_flat();
	gotoxy(1,4);
	printf("## Load Database ##");
	loaddatabase();
     }
     else
     if (option == '9')
     {  gotoxy(1,25);
	cprintf("Do you really want to exit?, Press 'Y' to confirm, anykey to cancel");
	exit_opt = getch();
	flushall();
	if (exit_opt == 'y' || exit_opt == 'Y')
	{  clrscr();
	   remakescreen();
	   screen_draw_flat();
	   gotoxy(1,4);
	   printf("## Exit To system ##\n\n");
	   menu_exit();
	}
     }
     else 
     {  gotoxy(1,25);
	cprintf("Error: Invalid option! Select an option between 1 and 9");
	getch();
	flushall();
     }
   }while  (option > '9' || option < '1' );
 }while (option != '`'); 
}


void hostel(void)
{
char iroom[80],iphone[80],add_quit;
char option,sortopt,exit_opt;
int phone_check,room_check,delete_check,sort_check,list_check;
int iroom_search,iroom_del;
int int_iroom,total_entries;
int error_iphone,error_iroom;
long int longint_iphone;
long int iphone_search;
long int iphone_del;


strcpy(dbload, "DATABASE ERROR...");

do
 {
  do
   { option = menu_hostel();
     if (option == '1')
     {  current_e_add=0;
	for (i=total_entry; i < MAXDB; i++)
	{   clrscr();
	    remakescreen();
	    screen_draw_hostel();
	    gotoxy(1,4);
	    printf("## ADD NEW ENTRY ##");
	    gotoxy(1,25);
	    cprintf("Please Add Your Entry, leave blank to reach to Main Menu..");
	    gotoxy(1,6);
	    printf("Enter Room  Number[%3d]: ",i+1);
	    gets(iroom);

	    if (iroom[0] == '\0' )
	    {  gotoxy(1,25);
	       cprintf("You chose to quit: Entry %d was not added to the database.",i+1);
	       getch();
	       break;
	    }
	    printf("Enter Phone Number[%3d]: ",i+1);
	    gets(iphone);

	    if (iphone[0] == '\0')
	    {  gotoxy(1,25);
	       cprintf("You chose to quit: Entry %d was not added to the database.",i+1);
	       getch();
	       break;
	    }

	    error_iroom = chkdig(iroom,4);
	    error_iphone = chkdig(iphone,8);

	    while(error_iroom != 0)
	    {	if (error_iroom == -1)
		{  clrscr();
		   remakescreen();
		   screen_draw_hostel();
		   gotoxy(1,4);
		   printf("## ADD NEW ENTRY ##");
		   gotoxy(1,25);
		   cprintf("Error: Room  Number - out of Range, Your entry was greater than 4 digits. ");
		   gotoxy(1,6);
		   printf("Renter Room  Number[%3d]: ",i+1);
		   gets(iroom);
		}
		if (error_iroom == -2)
		{  clrscr();
		   remakescreen();
		   screen_draw_hostel();
		   gotoxy(1,4);
		   printf("*** Add Entry ***");
		   gotoxy(1,25);
		   cprintf("Error: Room  Number - Character(s) detected, character(s) are not allowed.");
		   gotoxy(1,6);
		   printf("Renter Room  Number[%3d]: ",i+1);
		   gets(iroom);
		}
		error_iroom = chkdig(iroom,4);
	    }
	    while(error_iphone !=0)
		{	if (error_iphone == -1)
		{  clrscr();
		   remakescreen();
		   screen_draw_hostel();
		   gotoxy(1,4);
		   printf("## ADD NEW ENTRY ##");
		   gotoxy(1,25);
		   cprintf("Error: Phone Number - out of Range, Your entry was greater than 8 digits. ");
		   gotoxy(1,6);
		   printf("Room  Number[%3d] Entry: %s",i+1,iroom);
		   gotoxy(1,7);
		   printf("Renter Phone Number[%3d]: ",i+1);
		   gets(iphone);
		}
		if (error_iphone == -2)
		{  clrscr();
		   remakescreen();
		   screen_draw_hostel();
		   gotoxy(1,4);
		   printf("## ADD NEW ENTRY ##");
		   gotoxy(1,25);
		   cprintf("Error: Phone Number - Character(s) detected, character(s) are not allowed.");
		   gotoxy(1,6);
		   printf("Room  Number[%3d] Entry: %s",i+1,iroom);
		   gotoxy(1,7);
		   printf("Renter Phone Number[%3d]: ",i+1);
		   gets(iphone);
		}
		error_iphone = chkdig(iphone,8);
	    }
	    if (error_iroom == 0 && error_iphone == 0)
	    {  int_iroom = atoi(iroom); 
	       longint_iphone = atol(iphone); 

	       current_e_add++;
	       add_entry(int_iroom,longint_iphone);
	    }
	}
	if (total_entry == MAXDB)
	{  gotoxy(1,25);
	   cprintf("\aDatabase is full!: %d entries were added, ",total_entry);
	   cprintf("that is the Maximum No. I can hold.");
	   getch();
	}
     }
     else
     if (option == '2') 
     {  del_entry = 0; 	clrscr();
	remakescreen();
	screen_draw_hostel();
	gotoxy(1,4);
	printf("## Delete Entry ##");
	gotoxy(1,6);
	printf("Enter room  number to delete: ");
	scanf("%d",&iroom_del);
	flushall(); 

	printf("Enter phone number to delete: ");
	scanf("%ld",&iphone_del);
	flushall();

	delete_check = delete_entry(iroom_del,iphone_del);

	if (delete_check == 0)
	{  gotoxy(1,25);
	   cprintf("Successful: There are presently %d entries in the database, ",total_entry);
	   cprintf("deleted %d.",del_entry);
	   getch();
	}
	if (delete_check == -1) 
	{  gotoxy(1,25);
	   cprintf("Error: The Room No./Phone No. Your looking for was Not Found.                  ");
	   getch();
	}

     }
     else
     if (option == '3')
     {  phone_found = 0;
	clrscr();
	remakescreen();
	screen_draw_hostel();
	gotoxy(1,4);
	printf("## Find Room Number ##");

	gotoxy(1,6);
	printf("Enter the phone number to search for: ");
	scanf("%ld",&iphone_search);
	flushall();

	phone_check = find_phone_number(iphone_search);

	if (phone_check == 0)
	{  gotoxy(1,25);
	   cprintf("Successful: There are presently %d entries in the database, ",total_entry);

	   printf("found %d.",phone_found);
	   getch();
	}
	if (phone_check == -1)
	{  gotoxy(1,25);
	   cprintf("Error: The Phone No. Your looking for was Not Found.");
	   getch();
	}
     }
     else
     if (option == '4')
     {  room_found = 0;
	clrscr();
	remakescreen();
	screen_draw_hostel();
	gotoxy(1,4);
	printf("## Find Phone Number ##");

	gotoxy(1,6);
	printf("Enter the room number to search for: ");
	scanf("%d",&iroom_search);
	flushall();

	room_check = FindRoom(iroom_search);

	if (room_check == 0) 
	{  gotoxy(1,25);
	   cprintf("Successful: There are presently %d entries in the database, ",total_entry);
	   cprintf("found %d.",room_found);
	   getch();
	}
	if (room_check == -1)
	{  gotoxy(1,25);
	   cprintf("Error: The Room No. Your looking for was Not Found.");
	   getch();
	}

     }
     else
     if (option == '5') 
     {  clrscr();
	remakescreen();
	screen_draw_hostel();
	gotoxy(1,4);
	printf("## ListAll ##\n\n");

	list_check = ListAll();

	if (list_check == 0)
	{  gotoxy(1,25);
	   cprintf("List Sucuessful");
	   getch();
	}
	if (list_check == -1) 
	{
	   gotoxy(1,25);
	   cprintf("Empty List");
	   getch();
	}
     }
     else
     if (option == '6')
     {  total_entries = GeTotalEntries();
	gotoxy(1,25);
	cprintf("There are presently %d entries stored in the Database.",total_entries);
	getch();
     }
     else
     if (option == '7')
   {  clrscr();
	remakescreen();
	screen_draw_hostel();
	gotoxy(1,4);
	printf("## Sort All Entries ##");
	gotoxy(1,6);
	printf("Press 'A' to sort database in [A]scending order");
	gotoxy(1,7);
	printf("Press 'D' to sort database in [D]escending order.");
	gotoxy(1,9);
	printf("Note: Database is sorted by phone no. entries.");
	sortopt = getch();
	flushall();

	sort_check = sort_entries(sortopt);
	getch();
	if (sort_check == 0)
	{  gotoxy(1,25);
	   cprintf("Database was successfully Sorted.                                      ");
	   getch();
	}
	if (sort_check == -1)
	{  gotoxy(1,25);
	   cprintf("Database was not sorted - Database is empty!");
	   getch();
	}
     }
     else
     if (option == '8')
     {  clrscr();
	remakescreen();
	screen_draw_hostel();
	gotoxy(1,4);
	printf("## Load Database ##");
	loaddatabase();
     }
     else
     if (option == '9') 
     {  gotoxy(1,25);
	cprintf("Do you really want to exit?, Press 'Y' to confirm, anykey to cancel");
	exit_opt = getch();
	flushall();
	if (exit_opt == 'y' || exit_opt == 'Y')
	{  clrscr();
	   remakescreen();
	   screen_draw_hostel();
	   gotoxy(1,4);
	   printf("## Exit To system ##\n\n");
	   menu_exit();
	}
     }
     else
     {  gotoxy(1,25);
	cprintf("Error: Invalid option! Select an option between 1 and 9");
	getch();
	flushall();
     }
   }while  (option > '9' || option < '1' );
 }while (option != '`'); 
}


int chkdig (char str[], int range)
{
int lenght=0,k;
    lenght = strlen(str);

    if (lenght > range)
    { 	return(-1);}
    if (lenght <= range)
    {  for (k=0; k < lenght; k++)
       {   if (isdigit(str[k]) == 0)
	   { return(-2); } 
       }
    return(0); 
    }
}


void loaddatabase(void)
{
int count,nofilen,dbfilecount=0;
char finphone[80];
char finroom[80];
int error_junk;

long int l_finphone;
int i_finroom;

FILE *f1;
     gotoxy(1,6);
     printf("Enter the filename of the database: ");
     gotoxy(1,7);
     printf("Example: c:\\hostel.txt or c:\\flat.txt");
     gotoxy(37,6);
     gets(dbload);
     flushall();
     f1 = fopen (dbload,"r"); 
     if (f1==NULL)
     {  gotoxy(1,25);
	fprintf(stderr,"There was an error reading your database file!");
	strcpy(dbload, "DATABASE ERROR...");
	getch();
	exit;
     }
     else
     {	for (count=0; count < MAXDB; count++)
	{   if (!feof(f1))

	    { 	fscanf(f1,"%s\t%s\n",&finroom,&finphone);
	    error_junk = chkdig(finroom,4);
	    error_junk = chkdig(finphone,8);
         if (error_junk == -1 || error_junk == -2)
         {  printf("Sorry that was an invalid database\n");
            printf("Now working in RAM MODE!");
            getch();
	    strcpy(dbload, "DATABASE ERROR...");
	    break;
	 }
	     i_finroom = atoi(finroom);
	     l_finphone = atol(finphone);
		room[count] = i_finroom;
		phone[count] = l_finphone;
		dbfilecount++; 
	    }
	}
       if (error_junk ==0)
       {
	  gotoxy(1,25);
	  printf("Database %s, was successfully loaded!",dbload);
	  getch();
	  total_entry = dbfilecount;
       }
     }
     fclose(f1);
}


void menu_exit(void)
{    char filename[20],save_opt;
     int k;
     FILE *f1;
     gotoxy(1,6);
     printf("Do You want to Save database before exiting? ");
     gotoxy(1,25);
     cprintf("Press 'Y' to confirm, anykey to cancel.");
     save_opt = getch();
     flushall();
     if (save_opt == 'y' || save_opt == 'Y')
     {  gotoxy(1,8);
	printf("Please Enter the path and filename to save to:");
	gotoxy(1,10);
	printf("Example: c:\\hostel.txt or c:\\flat.txt");
	gotoxy(48,8); 
	gets(filename);
	flushall();
	f1 = fopen (filename,"a");
	if (f1== NULL)
	{  gotoxy(1,12);
	   fprintf(stderr, "Error opening file %s.",filename);
	   gotoxy(1,25);
	   cprintf("Database was not saved!                                                   ");
	   getch();
	   exit;
	}
	else
	{   for (k=0; k < total_entry; k++)
	    {   fprintf(f1, "%d\t%ld\n",room[k],phone[k]);}
		fclose(f1);
		gotoxy(1,25);
		cprintf("Database was successfully saved in %s",filename);
		getch();
	    }
     }
     else
     {   gotoxy(1,25);
	 cprintf("Database was not saved!                                                   ");
	 getch();
     }
     clrscr();
     gotoxy(23,12);
     printf("Thank you for using this program");
     gotoxy(23,13);
     printf("Coded by: Shivam");
     gotoxy(33,14);
     printf("Akshay");
     gotoxy(33,15);
     printf("Aayush");
     getch();
     exit(0);
}

//aayush part... from here till akshay`s
int sort_entries(char sel)
{
int k,room_str_tmp,sortalldone;
long int phone_str_tmp;
    if (total_entry !=0)
    {  do
       { sortalldone=0;
	 for (k = 0; k < total_entry; k++)
	 {
	     if ((phone[k] > phone[k + 1])&&(sel == 'a' || sel == 'A')&&(k != total_entry -1))
	     {   phone_str_tmp = phone[k]; 
		 phone[k] = phone[k + 1]; 
		 phone[k + 1] = phone_str_tmp; 
	
		 room_str_tmp = room[k];
		 room[k] = room[k + 1];
		 room[k + 1] = room_str_tmp;
		 sortalldone =1;
	     }


	     if ((phone[k] < phone[k + 1])&&(sel == 'd' || sel == 'D')&&(k != total_entry -1))
	     {   phone_str_tmp = phone[k];
		 phone[k] = phone[k + 1];
		 phone[k + 1] = phone_str_tmp;
		 room_str_tmp = room[k];
		 room[k] = room[k + 1];
		 room[k + 1] = room_str_tmp;
		 sortalldone =1;
	     }
	 }
       }while (sortalldone);
    }

    if ((sel == 'a' || sel == 'A')&&total_entry !=0)
    {   gotoxy(1,25);
	printf("You have chosen to sort the database in [A]scending order. ");
	return(0);
    }
    else
    if ((sel == 'd' || sel == 'D')&&total_entry !=0)
    {  gotoxy(1,25);
       printf("You have chosen to sort the database in [D]ecending order. ");
       return(0);
    }
    else
    if ((sel != 'a' || sel != 'A' || sel != 'd' || sel != 'D')&&total_entry !=0)
    {  gotoxy(1,12);
       printf("Invalid option - database was not sorted!");
    }
    else
    { return(-1); } 
}

void add_entry(int r, long int p)
{
     room[i] = r;
     phone[i] = p;
	total_entry++;  
     printf("\nRoom No.  [%-4d]\nPhone No. [%-8ld]\n%d entries added.",r,p,current_e_add);
     getch();
}

int delete_entry(int r, long int p)
{
int k,x,del_found_flag=-1,loop_mov_stop,loop_mov,count_del=0;
char del_me;
    for(k=0; k < total_entry; k++)
    {  if (total_entry != 0)
       {  if (r == room[k] && p == phone[k])
	  {  gotoxy(1,8);
	     printf("Match Found: \n");
	     printf("Room No. [%-4d]\tPhone No. [%-8ld] was found in record No. [%3d  ]\n",room[k],phone[k],k+1);
	     del_found_flag = 0;

	     gotoxy(1,25);
	     cprintf("Delete record [%3d  ]?, Press 'Y' to confirm, anykey to cancel.",k+1);
	     del_me = getch();
	     flushall();
	     if (del_me == 'y' || del_me == 'Y')
	     {  room_tmp[tot_del_entry] = room[k];
		room[k] = -1;
		phone_tmp[tot_del_entry] = phone[k];
		phone[k] = -1;
		del_entry++; 

		tot_del_entry++;
	     }
	  }
       }
    }
    if (total_entry !=0) 
    {
       for (x=0; x < del_entry; x++)
       {   for (k=0; k < total_entry; k++)
	   {
	      if (room[k] == -1 && phone[k] == -1)
	      {  loop_mov_stop=0;
		 loop_mov =0;
		 count_del++;

		 loop_mov_stop = total_entry-(k+1);
		 while (loop_mov_stop != loop_mov)
		 {     room[k+loop_mov] = room[(k+1)+loop_mov];
		       phone[k+loop_mov] = phone[(k+1)+loop_mov];
		       loop_mov++;
		 }
	      }
	   }
       }
    }

    total_entry = total_entry - del_entry;

    if (del_found_flag == 0) 
    { return(0);  } 
    else
    { return(-1); } 
}

//akshay part from here to end....
int find_phone_number(long int p)
{
int k, phone_found_flag= -1;
    gotoxy(1,8);
    for(k=0; k < total_entry; k++)
    {  if (total_entry != 0)
       {  if (k != 0 && (k%15) == 0)
	  {  gotoxy(1,8); 
	     getch();
	  }
	  if (p == phone[k])
	  {  printf("Phone No. [%-8ld] was found in record No. [%3d  ]\tRoom No. [%-4d]\n",phone[k],k+1,room[k]);
	     phone_found++;
	     phone_found_flag = 0;
	  }
       }
    }
    if (phone_found_flag == 0)
    { return(0);  }
    else
    { return(-1); } 
}

int FindRoom(int r)
{
int k, room_found_flag=-1;

    gotoxy(1,8);
    for(k=0; k < total_entry; k++)
    {  if (total_entry != 0)
       {  if (k != 0 && (k%15) == 0)
	  {  gotoxy(1,8);
	     getch();
	  }
	  if (r == room[k])
	  {  printf("Room No. (%-4d) was found in record No. [%3d  ]\tPhone No. (%-8ld)\n",room[k],k+1,phone[k]);
	     room_found++;
	     room_found_flag = 0;
	  }
       }
    }

    if (room_found_flag == 0)
    { return(0);  }
    else
    { return(-1); } 
}

int ListAll(void)
{
int k;
    gotoxy(1,6);
    for (k=0; k < total_entry; k++)
    {
	if (k != 0 && (k%17) == 0)
	{  gotoxy(1,6);
	   getch();
	}

	if (room[k] != -1 && phone[k] != -1)
	{  printf("Room Number [%3d  ]: %-4d\t",k+1,room[k]);
	   printf("Phone Number[%3d  ]: %-8ld\n",k+1,phone[k]);
	}
    }
    if (total_entry == 0)
    {  return(-1); }
    else
    {  return(0);  } 
}

int GeTotalEntries(void)
{
   return(total_entry);
}

char choice_system(void)
{
char optrtn;
     clrscr();
     window(1,1,80,25);
     remakescreen_start();
     screen_draw_start();
     gotoxy(1,4);
     printf("[1] - HOSTEL Management System\n");
     printf("[2] - FLAT Management System\n");
     printf("[3] - EXIT\n");
     gotoxy(1,25);
     cprintf("Please select an option....");

     gotoxy(1,14);
     printf("Select an option: ");
     optrtn = getche();
     return optrtn;
}

char menu_flat(void)
{
char optrtn;
     clrscr();
     window(1,1,80,25);
     remakescreen();
     screen_draw_flat();
     gotoxy(1,4);
     printf("[1] - Add new entry\n");
     printf("[2] - Delete existing entry\n");
     printf("[3] - Find room number\n");
     printf("[4] - Find phone number\n");
     printf("[5] - List all entries\n");
     printf("[6] - Display total entries in database\n");
     printf("[7] - Sort entries\n");
     printf("[8] - Load database from file\n");
     printf("[9] - Exit");
     gotoxy(1,25);
     cprintf("Please select an option between 1 and 9.");
     gotoxy(1,15);
     printf("Database loaded: %s",dbload);
     gotoxy(1,14);
     printf("Select an option: ");
     optrtn = getch();
     return optrtn;
}

char menu_hostel(void)
{
char optrtn;
     clrscr();
     window(1,1,80,25); 
     remakescreen();
     screen_draw_hostel();
     gotoxy(1,4);
     printf("[1] - Add new entry\n");
     printf("[2] - Delete existing entry\n");
     printf("[3] - Find room number\n");
     printf("[4] - Find phone number\n");
     printf("[5] - List all entries\n");
     printf("[6] - Display total entries in database\n");
     printf("[7] - Sort entries\n");
     printf("[8] - Load database from file\n");
     printf("[9] - Exit");
     gotoxy(1,25);
     cprintf("Please select an option between 1 and 9.");
     gotoxy(1,15);
     printf("Database loaded: %s",dbload);
     gotoxy(1,14);
     printf("Select an option: ");
     optrtn = getch();
     return optrtn;
}

void screen_draw_hostel(void)
{
     gotoxy(1,1);
     cprintf("_______________________________________________________________________________");
     gotoxy(1,2);
     cprintf("                        *** ADVANCED HOSTEL PHONE DIRECTORY ***                ");
     gotoxy(1,3);
     cprintf("_______________________________________________________________________________");
}

void screen_draw_start(void)
{
     gotoxy(1,1);
     cprintf("_______________________________________________________________________________");
     gotoxy(1,2);
     cprintf("                        *** WELCOME TO PHONE DIRECTORY ***                     ");
     gotoxy(1,3);
     cprintf("_______________________________________________________________________________");
}

void screen_draw_flat(void)
{
     gotoxy(1,1);
     cprintf("_______________________________________________________________________________");
     gotoxy(1,2);
     cprintf("                        *** ADVANCED FLAT PHONE DIRECTORY ***                  ");
     gotoxy(1,3);
     cprintf("_______________________________________________________________________________");
}

void remakescreen(void)
{
	if(!strcmp(dbload,"DATABASE ERROR..."))
	{
	clrscr();
     textcolor(WHITE);
     textbackground(BLACK);
     gotoxy(1,25);
     cprintf("                                                                               ");
     clrscr();
     textcolor(WHITE);
     textbackground(RED);
     gotoxy(1,25);
     cprintf("                                                                               ");
	}
	 else
	{ 	clrscr();
     textcolor(WHITE);
     textbackground(BLACK);
     gotoxy(1,25);
     cprintf("                                                                               ");
     clrscr();
     textcolor(WHITE);
     textbackground(BLUE);
     gotoxy(1,25);
     cprintf("                                                                               ");
	 }
}

void remakescreen_start(void)
{

	clrscr();
     textcolor(WHITE);
     textbackground(BLACK);
     gotoxy(1,25);
     cprintf("                                                                               ");
     clrscr();
     textcolor(WHITE);
     textbackground(BROWN);
     gotoxy(1,25);
     cprintf("                                                                               ");

}
