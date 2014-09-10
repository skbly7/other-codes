/*
a program which outputs its running status (sleep, stopped ..etc), the parent ID of that process,  
and number of threads a program is using. Input will be a pid through command line. 

this version use library calls too, see the other program named status_system for same code using system calls only
*/

#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
    FILE* fd = NULL;
    char buff[100]={0};
    int i;
    char path[100]="";
    if(argc==1)
    {
      printf("Supply PID to me please.\n");
      return 0;
    }
    if(argc>2)
    {
      printf("So many PIDs ! Error.\n");
      return 0;
    }
    strcat(path,"/proc/");
    strcat(path,argv[1]);
    strcat(path,"/status");
    fd = fopen(path,"r");
    if(NULL == fd)
    {
        printf("\nThis PID is not active.\n");
        return 1;
    }
    char tmp[256]={0x0};
    char status[100]={0};
    int flag;
	while(fd!=NULL && fgets(tmp, sizeof(tmp), fd)!=NULL)
	{
		if (strstr(tmp,"Stat"))
		{
			printf("Current status : ");
			flag=0;
			for(i=0;i<strlen(tmp);i++)
			{
				if(tmp[i]==')')
					flag=2;
				if(flag==1)
					printf("%c",tmp[i]);
				if(tmp[i]=='(')
					flag=1;
			}
			printf("\n");
		}
		if (strstr(tmp,"PPid"))
		{
			printf("Parent ID : ");
			flag=0;
			for(i=0;i<strlen(tmp);i++)
			{
				if(tmp[i]=='\n')
					flag=2;
				if(flag==1)
					printf("%c",tmp[i]);
				if(tmp[i]=='	')
					flag=1;
			}
			printf("\n");
		}
		if (strstr(tmp,"Threads"))
		{
			printf("No. of threads : ");
			flag=0;
			for(i=0;i<strlen(tmp);i++)
			{
				if(tmp[i]=='\n')
					flag=2;
				if(flag==1)
					printf("%c",tmp[i]);
				if(tmp[i]=='	')
					flag=1;
			}
			printf("\n");
		}
	}
    fclose(fd);
    return 0;
}
