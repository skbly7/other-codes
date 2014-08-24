#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<alloc.h>
int aaa,max_friend=0;
struct std{
char name[20];
int count;
struct std *next;
struct dost *dost;
};
struct dost{
char name[20];
struct dost *next;
};
struct dost *head_d,*new_d,*ptr_d,*cur_d,*ptr2_d;
struct std *head_std,*new_std,*ptr_std,*cur_std;
void student_add()
{
new_std=(struct std*)malloc(sizeof(struct std));
printf("\nEnter name of student : ");
scanf("%s",new_std->name);
new_std->next=NULL;
if(head_std==NULL)
{
head_std=new_std;
cur_std=new_std;
}
else
{
cur_std->next=new_std;
cur_std=new_std;
}
aaa=friend_add();
}

int friend_add()
{
char add='y';
head_d=NULL;
cur_d=NULL;
cur_std->count=0;
while(add=='y')
{
new_d=(struct dost *)malloc(sizeof(struct dost));
printf("\nEnter name of friend : ");
scanf("%s",new_d->name);
cur_std->count++;
if((cur_std->count)>max_friend)
max_friend=cur_std->count;
new_d->next=NULL;
if(head_d==NULL)
{
head_d=new_d;
cur_d=new_d;
}
else
{
cur_d->next=new_d;
cur_d=new_d;
}
printf("Want to enter more friends ?\nPress \'y\' to enter : ");
add=getch();
}
cur_std->dost=head_d;
return 0;
}


void display_student()
{
ptr_std=head_std;
while(ptr_std!=NULL)
{
clrscr();
printf("\nStudent name : %s\n",ptr_std->name);
printf("Total Friends : %d\n",ptr_std->count);
ptr_d=ptr_std->dost;
ptr_std=ptr_std->next;

while(ptr_d!=NULL)
{
printf("Friend name : %s\n",ptr_d->name);
ptr_d=ptr_d->next;
}
printf("\nPress Enter To See Next Record....");
getch();
}
clrscr();
}

void save_memory_association_ltd()
{
clrscr();
ptr_std=head_std;
while(ptr_std!=NULL)
{
clrscr();
cur_std=ptr_std;
ptr_d=ptr_std->dost;
ptr_std=ptr_std->next;
while(ptr_d!=NULL)
{
cur_d=ptr_d;
ptr_d=ptr_d->next;
free(cur_d);
}
free(cur_std);
}
printf("\n\n\n\t\tMEMORY HAS BEEN CLEARED SUCCESSFULLY !!!!!\n\n\t\t\t\t-Shivam Khandelwal (B4) 12103506");
getch();
}

void display_one()
{
int print=0;
char name[20];
printf("\nEnter name of student you want to search for :");
scanf("%s",name);
clrscr();
ptr_std=head_std;
while(ptr_std!=NULL)
{
if(!strcmp(ptr_std->name,name))
{
print=1;
ptr_d=ptr_std->dost;
while(ptr_d!=NULL)
{
printf("Friend name : %s\n",ptr_d->name);
ptr_d=ptr_d->next;
}
break;
}
ptr_std=ptr_std->next;
}
if(print==0)
printf("Match not found\n");
getch();
clrscr();
}

void sach_ka_saamna()
{
char name[20];
printf("\nEnter name of student you want to search for :");
scanf("%s",name);
clrscr();
ptr_std=head_std;
while(ptr_std!=NULL)
{
ptr_d=ptr_std->dost;
while(ptr_d!=NULL)
{
if(!strcmp(ptr_d->name,name))
{
printf("Student name : %s\n",ptr_std->name);
}
ptr_d=ptr_d->next;
}
ptr_std=ptr_std->next;
}
getch();
clrscr();
}

void yaariyaaa()
{
//basic from Sach ka saamna... ;)  <3  :P
int print=0;
char name1[20],name2[20];
printf("\nEnter name of both student you want to search for :");
scanf("%s %s",name1,name2);
clrscr();
ptr_std=head_std;
while(ptr_std!=NULL)
{
print=0;
ptr_d=ptr_std->dost;
while(ptr_d!=NULL)
{
if((!strcmp(ptr_d->name,name1))||(!strcmp(ptr_d->name,name2)))
{
print++;
if(print==2)
printf("Student name : %s\n",ptr_std->name);
}
ptr_d=ptr_d->next;
}
ptr_std=ptr_std->next;
}
getch();
clrscr();
}

void sabse_jyda_kiske()
{
clrscr();
ptr_std=head_std;
printf("Student(s) with max. friends are :\n");
while(ptr_std!=NULL)
{
if(ptr_std->count==max_friend)
printf("%s\n",ptr_std->name);
ptr_std=ptr_std->next;
}
getch();
clrscr();
}



void golmaal()
{
//in memory of my old dear lovly computer.. :P    <3
int maxc=0,common=0;
struct std *max1,*max2,*ptr2_std;
struct dost *ptr333;
clrscr();
ptr_std=head_std;

while(ptr_std!=NULL)
{
ptr2_std=ptr_std->next;
while(ptr2_std!=NULL)
{
common=0;
ptr_d=ptr_std->dost;

while(ptr_d!=NULL)
{
ptr2_d=ptr2_std->dost;
while(ptr2_d!=NULL)
{
if(!strcmp(ptr_d->name,ptr2_d->name))
common++;
ptr2_d=ptr2_d->next;
}
ptr_d=ptr_d->next;
}

if(common>maxc)
{
maxc=common;
max1=ptr_std;
max2=ptr2_std;
}

ptr2_std=ptr2_std->next;
}
ptr_std=ptr_std->next;
}
printf("Maximun number of common friends is : %d\nStudents with maximum common friends are %s and %s\nName of common friends are :\n\n",maxc,max1->name,max2->name);


ptr_d=max1->dost;
ptr333=max2->dost;

while(ptr_d!=NULL)
{
ptr2_d=ptr333;
while(ptr2_d!=NULL)
{
if(!strcmp(ptr_d->name,ptr2_d->name))
printf("%s\n",ptr_d->name);

ptr2_d=ptr2_d->next;
}
ptr_d=ptr_d->next;
}
getch();
clrscr();
}

void max_rebuild()
{
max_friend=0;
ptr_std=head_std;
while(ptr_std!=NULL)
{
if(ptr_std->count>max_friend)
max_friend=ptr_std->count;

ptr_std=ptr_std->next;
}

}

void chal_nikal()
{
int found=0;
char name[20];
struct std *back,*del;
clrscr();
printf("Enter name of that unlucky student : ");
scanf("%s",name);

ptr_std=head_std;
back=NULL;
while(ptr_std!=NULL)
{
if(!strcmp(ptr_std->name,name))
{
	found=1;
	if(back==NULL)
	{
	del=ptr_std;
	head_std=ptr_std->next;
	ptr_std->next=NULL;
	free(del);
	}
	else
	{
	back->next=ptr_std->next;
	del=ptr_std;
	ptr_std->next=NULL;
	free(del);
	}
break;
}
back=ptr_std;
ptr_std=ptr_std->next;
}

//to remove from friends entryyyyyyyyyyyyyyyyyyy


//to rebuild max friend entryyyyyy
max_rebuild();
switch(found)
{
case 1 : printf("\n\nStudent successfully removed from database...!!");
	 break;
case 0 :  printf("\n\nNo student found with that name, do try again please..!!");
	 break;
default : printf("\n\nProgram got an undefined error, please contact Shivam for help...!!");
}
getch();
clrscr();
}


void main()
{
int i;
clrscr();
printf("\n\n\n\n\n\n\n");
printf("\t#########################################################\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#\t\tWELCOME TO \t\t\t\t#\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#\t\tSHIVAM`s STUDENT DATABASE\t\t#\n");

printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#\t\t\tMANAGEMENT SYSTEM\t\t#\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#########################################################\n");
printf("\n\n\n\n\t\t\t\t\tPress a key to start......");
getch();
delay(1000);
clrscr();
do
{

printf("\n\t#########################################################\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#\tSHIVAM`s STUDENT DATABASE MANAGEMENT SYSTEM\t#\n");
printf("\t#\t\t\t\t\t\t\t#\n");
printf("\t#########################################################\n");




printf("\n\nMAIN MENU\n\n1.Add Entry\n2.Display All Entry\n3.Display Friend List of any one student\n4.Display to whom ABC is a friend\n5.Display student friend with ABC and XYZ\n6.Display student name(s) with maximum friends\n7.Max. common friends\n8.Remove a student from database\n9.Exit\nEnter your choice :");
scanf("%d",&i);
printf("\n\nLoading.....\n\n");
delay(500);

switch(i)
{
case 1: student_add();
	getch();
	clrscr();
	break;
case 2: display_student();
	break;
case 3: display_one();
	break;
case 4:	sach_ka_saamna();
	break;
case 5:	yaariyaaa();
	break;
case 6: sabse_jyda_kiske();
	break;
case 7: golmaal();
	break;
case 8: chal_nikal();
	break;
case 9: break;
default:clrscr();
	printf("WRONG CHOICE !! TRY AGAIN !!!!!\n\n");
	break;
}
}
while(i!=9);
save_memory_association_ltd();
//Shivam Khandelwal.....
}