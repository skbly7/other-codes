#include<conio.h>
#include<stdio.h>
#include<alloc.h>
#include<string.h>
long int t=100001;
void createrecord(struct records *r);
void createcopy(struct bookcopy *c);
void createauthor(struct author *a);
void fine();
void createbook(struct book *b);
void printlib(struct book *u);
typedef struct author
{
  char authorname[100];
  struct author *nextauthor;
}authornode;
typedef struct records
{
  int id,im,iy,rd,rm,ry;
  long int enroll;
  struct records *nextrecord;
}recordnode;
typedef struct bookcopy
{
  long int id;
  int m;
  struct records *headrecord;
  struct bookcopy *nextcopy;
}copynode;
typedef struct book
{
  char bookname[100];
  char publisher[100];
  struct author *headauthor;
  struct book *nextbook;
  struct bookcopy *headcopy;
}booknode;
void main()
{
  struct book *head;
  head=(struct book*)malloc(sizeof(booknode));
  clrscr();
  printf("\nENTER BOOK DETAILS\n");
  printf("\nENTER BOOK NAME\n");
  createbook(head);
  fine();
  getch();
  clrscr();
  printlib(head);
  printf("\n\n\n\n\n\n\n\n\n\t\t\t\tTHANK YOU!!!\n\n\n\n\n\n\n\n\n\n");
  getch();
  clrscr();
}
void createbook(struct book *booklink)
{
  char c;
  fflush(stdin);
  gets(booklink->bookname);
  printf("\nENTER BOOK PUBLISHER\n");
  fflush(stdin);
  gets(booklink->publisher);
  printf("\nENTER BOOK'S MAIN AUTHOR\n");
  fflush(stdin);
  booklink->headauthor=(struct author*)malloc(sizeof(authornode));
  createauthor(booklink->headauthor);
  booklink->headcopy=(struct bookcopy*)malloc(sizeof(copynode));
  printf("\nENTER BOOK'S COPY DETAILS\n");
  createcopy(booklink->headcopy);
  printf("\nARE THERE MORE BOOKS?y OR n\n");
  fflush(stdin);
  scanf("%c",&c);
  if(c=='n')
  {
   booklink->nextbook=NULL;
  }
  else
  {
    booklink->nextbook=(struct book*)malloc(sizeof(booknode));
    printf("\nENTER NEXT BOOK DETAIL\n");
    printf("\nENTER BOOK'S NAME\n");
    createbook(booklink->nextbook);
  }
}
void createauthor(struct author *authorlink)
{
  char c;
  fflush(stdin);
  gets(authorlink->authorname);
  printf("\nARE THERE MORE AUTHORS?y OR n\n");
  fflush(stdin);
  scanf("%c",&c);
  if(c=='n')
  {
    authorlink->nextauthor=NULL;
  }
  else
  {
    authorlink->nextauthor=(struct author*)malloc(sizeof(authornode));
    printf("\nENTER NEXT AUTHOR'S NAME\n");
    createauthor(authorlink->nextauthor);
  }
}
void createcopy(struct bookcopy *copylink)
{
  int j=1;
  char c,c1;
  struct records *temp;
  copylink->id=t;
  t=t+1;
  printf("\nENTER THE NO. OF RECORD SLIPS FOR THE BOOK");
  fflush(stdin);
  scanf("%d",&copylink->m);
  printf("\nHAS THIS BOOK,id %ld BEEN ISSUED?y OR n\n",copylink->id);
  fflush(stdin);
  scanf("%c",&c1);
  if(c1=='y')
  {
    copylink->headrecord=(struct records*)malloc(sizeof(recordnode));
    temp=copylink->headrecord;
    createrecord(temp);
    for(j=1;j<copylink->m;++j)
    {
      temp->nextrecord=(struct records *)malloc(sizeof(recordnode));
      temp=temp->nextrecord;
      createrecord(temp);
    }
    temp->nextrecord=NULL;
  }
  else copylink->headrecord=NULL;
  printf("\ARE THERE MORE COPIES OF THIS BOOK?y OR n\n");
  fflush(stdin);
  scanf("%c",&c);
  if(c=='n')
  {
    copylink->nextcopy=NULL;
  }
  else
  {
    copylink->nextcopy=(struct bookcopy*)malloc(sizeof(copynode));
    createcopy(copylink->nextcopy);
  }
}
void fine()
{char chd;
int a,fin=0;
printf("has anyone issue the book y or n");
scanf("%c",&chd);
if(chd=='y')
{printf("for how many days");
scanf("%d",&a);
if(a>15)
{fin+=100*(a-15);
printf("fine is %d",fin) ;
}
else
printf("no fine");
}
}
void createrecord(struct records* recordlink)
{
  printf("\nENTER ENROLLMENT NUMBER OF STUDENT TO WHOM BOOK HAS BEEN ISSUED\n");
  fflush(stdin);
  scanf("%ld",&recordlink->enroll);
  printf("\nENTER DATE OF ISSUE(dd mm yy)\n");
  printf("\ndd:");
  fflush(stdin);
  scanf("%d",&recordlink->id);
  printf("\nmm:");
  fflush(stdin);
  scanf("%d",&recordlink->im);
  printf("\nyy:");
  fflush(stdin);
  scanf("%d",&recordlink->iy);
  printf("\nENTER DATE OF RETURN(dd mm yy)\n");
  printf("\ndd:");
  fflush(stdin);
  scanf("%d",&recordlink->rd);
  printf("\nmm:");
  fflush(stdin);
  scanf("%d",&recordlink->rm);
  printf("\nyy:");
  fflush(stdin);
  scanf("%d",&recordlink->ry);
}
void printlib(struct book *booklink)
{
  struct book *temp;
  struct author *temp1;
  struct bookcopy *temp2;
  struct records *temp3;
  temp=booklink;
  while(temp!=NULL)
  {
    printf("\nBOOK NAME:");
    printf("%s\n",temp->bookname);
    printf("\nBOOK PUBLISHER:%s\n",temp->publisher);
    printf("\nAUTHORS:\n");
    printf("MAIN AUTHOR:%s",temp->headauthor->authorname);
    temp1=temp->headauthor->nextauthor;
    while(temp1!=NULL)
    {
      printf("\nNEXT AUTHOR:%s",temp1->authorname);
      temp1=temp1->nextauthor;
    }
    printf("\nCOPIES OF BOOK\n");
    temp2=temp->headcopy;
    while(temp2!=NULL)
    {
      printf("\nID OF BOOK:%ld",temp2->id);
      printf("\nNUMBER OF ISSUE SLIPS TO BOOK:%d",temp2->m);
      printf("\nRECORDS OF BOOK WITH ID %ld\n",temp2->id);
      temp3=temp2->headrecord;
      while(temp3!=NULL)
      {
	 printf("\nTHIS BOOK WAS ISSUED TO STUDENT WITH ENROLLMENT NUMBER %ld",temp3->id);
	 printf("\nISSUE DATE: %d - %d - %d",temp3->id,temp3->im,temp3->iy);
	 printf("\nRETURN DATE:%d - %d - %d",temp3->rd,temp3->rm,temp3->ry);
	 temp3=temp3->nextrecord;
      }
      temp2=temp2->nextcopy;
    }
    temp=temp->nextbook;
    getch();
    clrscr();
  }
}





