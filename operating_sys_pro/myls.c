/*
PROBLEM STATEMENT :

The task is to write your own ls program. You will be given directory via Command Line argument 
and are required to print directory's content to stdout. You can expect the input directory name to be 
accompanied by these 3 option(­l,­a,­h) in any combination in which case output should reflect the 
effect of these options. 
Eg. Test cases 
$ ./myls dirname 
dircontent 
$ ./myls dirname ­lh
dircontent with effects of these options 
$./myls ­lah  dirname

*/

#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
//just used this to make the output better.
#include <sys/ioctl.h>
#define YEAR_TO_DAYS(y) ((y)*365 + (y)/4 - (y)/100 + (y)/400)
#define handle_error(msg) \
do { print(msg,2); exit(EXIT_FAILURE); } while (0)
typedef struct time_t ok;
int total=0;
int jaadu_ends(char *a,char *b)
{
  //don't see me, else all the jaadu world would get over.. :'(
  //ok ur wish, you can see.. :P
  int i;
  if(length(a)==length(b))
  {
    i=length(a);
    i--;
    for(;i>-1;i--)
      if(a[i]!=b[i])
        return 0;
    return 1;
  }
  return 0;
}
char * mystrstr(const char* str, const char* target){
if(!*target) return NULL;
char *p1 = (char*)str;
while(*p1)
{
char *p1Begin = p1, *p2 = (char*)target;
while(*p1 && *p2 && *p1 == *p2)
{
p1++;
p2++;
}
if(!*p2)
return p1Begin;
p1 = p1Begin + 1;
}
return NULL;
}
int fall_back=1000,h_on=0;
void print(char *str, int type)
{
int i=0;
while(i<50&&str[i]!='\0')
i++;
write(1,str,i);
if(type==1)
write(1," ",1);
if(type==2)
write(1,"\n",1);
}
char* itoa(int val, int base)
{
static char buf[100] = {0};
int i = 30;
  if(val==0)
  {
    buf[0]='0';
    return buf;
  }
for(; val && i ; --i, val /= base)
buf[i] = "0123456789abcdef"[val % base];
return &buf[i+1];
} 
void getName(int uid){
int fd = open("/etc/passwd", O_RDONLY), i;
char buf[100000] = {'\0'};
char * num;
//print(itoa(uid,10),0);
if(uid==0)
  uid=fall_back;
fall_back=uid;
num=itoa(uid,10);
struct stat sb;
fstat(fd, &sb);
read(fd, &buf,(int)sb.st_size);
char* ptr = mystrstr(buf,num);
char* temp;
while(*(ptr)!='\n')
{
ptr--;
}
ptr++;
temp=ptr;
i=0;
while(*(ptr)!=':')
{
ptr++;
i++;
}
write(STDOUT_FILENO, temp, i);
write(STDOUT_FILENO, " ", 1);
return;
}
char* itoa_t(int val, int base)
{
static char buf[32] = {0};
int i = 30;
int flag=0;
  if(val<10)
    flag=1;
  if(val==0)
  {
    buf[0]='0';
    buf[1]='0';
    return buf;
  }
for(; val && i ; --i, val /= base)
buf[i] = "0123456789abcdef"[val % base];
  if(flag)
  {
    buf[i--]='0';
  }
return &buf[i+1];
}
void concat(char *s1,char *s2)
{
     while(*s1!='\0')
             s1++;
     while(*s2!='\0')
     {
            *s1=*s2;
             s1++;                                         
             s2++;                                         
     }
      *s1='\0';
}
char* time_str(unsigned long unixtime)
{
static char buf[32] = {0};
buf[0]='\0';
unsigned int year, month, day, hour, minute, second;
unixtime += 19800;  //We live in IST sorry.. :P
second = unixtime % 60;
unixtime /= 60;
minute = unixtime % 60; 
unixtime /= 60;
hour = unixtime % 24;
unixtime /= 24;
unixtime += 719499;
for (year = 1969; unixtime > YEAR_TO_DAYS(year + 1) + 30; year++);
unixtime -= YEAR_TO_DAYS(year);
for (month = 1; month < 12 && unixtime > 367*(month+1)/12; month++);
unixtime -= 367*month/12;
month += 2;
if (month > 12) {
month -= 12;
year++;
}
day = unixtime;
switch(month)
{
case 1:
  concat(buf,"Jan");
  break;
case 2:
  concat(buf,"Feb");
  break;
case 3:
  concat(buf,"Mar");
  break;
case 4:
  concat(buf,"Apr");
  break;
case 5:
  concat(buf,"May");
  break;
case 6:
  concat(buf,"Jun");
  break;
case 7:
  concat(buf,"Jul");
  break;
case 8:
  concat(buf,"Aug");
  break;
case 9:
  concat(buf,"Sep");
  break;
case 10:
  concat(buf,"Oct");
  break;
case 11:
  concat(buf,"Nov");
  break;
case 12:
  concat(buf,"Dec");
  break;
}
concat(buf," ");
concat(buf,itoa_t(day,10));
concat(buf," ");
concat(buf,itoa_t(hour,10));
concat(buf,":");
concat(buf,itoa_t(minute,10));
return buf;
}
int length(char *str)
{
    int i=0;
    while(i<50&&str[i]!='\0')
    i++;
    return i;
}
void strcatt(char *s,char *t)
{
while(*s!='\0')
{    
 s++;
}
*s=' ';
++s;
while(*t!='\0')
{
    *s=*t;
    s++;
    t++;
}
*s=*t;
}
void print_name(char *str,int x)
{
int i=0;
while(i<50&&str[i]!='\0')
i++;
write(1,str,i);
i=0;
while(i++<x)
write(1," ",1);
}
struct linux_dirent {
long           d_ino;
off_t          d_off;
unsigned short d_reclen;
char           d_name[];
};

int strcmpp(char *a,char *b)
{
  int i=0,j=0;
  while(a[i]!='\0'&&a[i]!='\n')
  {
      if(a[i]!=b[i])
        return 0;
      i++;
  }
  if(b[i]!='\0'&&b[i]!='\n')
    return 0;
  else
    return 1;
}

void link_check(struct linux_dirent *d,struct stat sb)
{
  char *linkname;
  linkname = malloc(sb.st_size + 1);
  ssize_t r;
  r = readlink(d->d_name, linkname, sb.st_size + 1);
  linkname[sb.st_size] = '\0';
  print(" -> ",0);
  print(linkname,0);
}
void acc_to_name(char *a)
{
  int i=0,j=-1;
  char buf[32] = {0};
  while(a[i]!='\0'&&a[i]!='\n')
  {
    if(a[i]=='.')
      j=i;
    i++;
  }
  j++;
  if(j!=-1)
  {
    concat(buf,a+j);
    if(strcmpp(buf,"tar")||strcmpp(buf,"tgz")||strcmpp(buf,"arj")||strcmpp(buf,"taz")||strcmpp(buf,"lzh")||strcmpp(buf,"lzma")||strcmpp(buf,"tlz")||strcmpp(buf,"txz")||strcmpp(buf,"zip")||strcmpp(buf,"z")||strcmpp(buf,"Z")||strcmpp(buf,"dz")||strcmpp(buf,"gz")||strcmpp(buf,"lz")||strcmpp(buf,"xz")||strcmpp(buf,"bz2")||strcmpp(buf,"bz")||strcmpp(buf,"tbz")||strcmpp(buf,"tbz2")||strcmpp(buf,"tz")||strcmpp(buf,"deb")||strcmpp(buf,"rpm")||strcmpp(buf,"jar")||strcmpp(buf,"rar")||strcmpp(buf,"7z"))
      print("\033[1;31m",0);
    if(strcmpp(buf,"jpg")||strcmpp(buf,"jpeg")||strcmpp(buf,"gif")||strcmpp(buf,"bmp")||strcmpp(buf,"pbm")||strcmpp(buf,"pgm")||strcmpp(buf,"ppm")||strcmpp(buf,"tga")||strcmpp(buf,"xbm")||strcmpp(buf,"xpm")||strcmpp(buf,"tif")||strcmpp(buf,"tiff")||strcmpp(buf,"png")||strcmpp(buf,"svg")||strcmpp(buf,"svgz")||strcmpp(buf,"mng")||strcmpp(buf,"pcx")||strcmpp(buf,"mov")||strcmpp(buf,"mpg")||strcmpp(buf,"mpeg")||strcmpp(buf,"m2v")||strcmpp(buf,"mkv")||strcmpp(buf,"ogm")||strcmpp(buf,"mp4")||strcmpp(buf,"m4v")||strcmpp(buf,"mp4v")||strcmpp(buf,"vob")||strcmpp(buf,"qt")||strcmpp(buf,"nuv")||strcmpp(buf,"wmv")||strcmpp(buf,"asf")||strcmpp(buf,"rm")||strcmpp(buf,"rmvb")||strcmpp(buf,"flc")||strcmpp(buf,"avi")||strcmpp(buf,"fli")||strcmpp(buf,"flv")||strcmpp(buf,"gl")||strcmpp(buf,"dl")||strcmpp(buf,"xcf")||strcmpp(buf,"xwd")||strcmpp(buf,"yuv")||strcmpp(buf,"cgm")||strcmpp(buf,"emf")||strcmpp(buf,"axv")||strcmpp(buf,"anx")||strcmpp(buf,"ogv")||strcmpp(buf,"ogx"))
      print("\033[1;36m",0);    
    if(strcmpp(buf,"desktop")||strcmpp(buf,"out")||strcmpp(buf,"sh"))
      print("\033[1;32m",0);      
  }
}
int show_size(int i)
{
  int c=0;
  float a=i,len=0;
  while(i/1000>0)
  {
    a=a/1000;
    i=i/1000;
    c++;
  }
  i=(int)a;
  len+=length(itoa(i,10));
  print(itoa(i,10),0);
  if(c>0)
  {
    len++;
    print(".",0);
    a=a-(int)a;
    a=a*10;
    i=(int)a;
    len+=2;
    print(itoa(i,10),0);
    switch(c)
    {
      case 1:print("K",0);
              break;
      case 2:print("M",0);
              break;
      case 3:print("G",0);
              break;
      case 4:print("T",0);
              break;
      case 5:print("P",0);
              break;
    }
  }
  while(len++<7)
    print(" ",0);
}
void long_printing(struct linux_dirent *d,int d_type)
{
  struct stat sb;
  mode_t val;
  int j,temp;
  if(d_type == DT_LNK)
    lstat(d->d_name,&sb);
  else
    stat(d->d_name,&sb);
  print("\e[m",0);
  if (d_type == DT_DIR)
  {
  print("d",0);
  }
  else if (d_type == DT_LNK)
  {
  print("l",0);
  }
  else
  print("-",0);
  val=(sb.st_mode & ~S_IFMT);
  total+=sb.st_blocks;
  print( (sb.st_mode & S_IRUSR) ? "r" : "-",0);
  print( (sb.st_mode & S_IWUSR) ? "w" : "-",0);
  print( (sb.st_mode & S_IXUSR) ? "x" : "-",0);
  print( (sb.st_mode & S_IRGRP) ? "r" : "-",0);
  print( (sb.st_mode & S_IWGRP) ? "w" : "-",0);
  print( (sb.st_mode & S_IXGRP) ? "x" : "-",0);
  print( (sb.st_mode & S_IROTH) ? "r" : "-",0);
  print( (sb.st_mode & S_IWOTH) ? "w" : "-",0);
  print( (sb.st_mode & S_IXOTH) ? "x" : "-",1);
  print(itoa(sb.st_nlink,10),1);
  temp=3-length(itoa(sb.st_nlink,10))%3;
  if(temp==3)
    temp=0;
  for(j=0;j<temp;j++)
    print(" ",0);
  getName((int)sb.st_uid);
  getName((int)sb.st_gid);
  if(h_on==0)
  {
    print(itoa(sb.st_size,10),1);
    temp=10-length(itoa(sb.st_size,10))%10;
    if(temp==10)
      temp=0;
    for(j=0;j<temp;j++)
      print(" ",0);
  }
  else
  {
    show_size(sb.st_size);
  }
  print(time_str((unsigned long) sb.st_mtime),1);
  print(" ",0);
  print("\e[m",0);
  acc_to_name(d->d_name);
  if(d_type == DT_DIR)
  {
    print("\033[1;34m",0);
  }
  else if(d_type == DT_LNK)
  {
    print("\033[1;31m",0);
  }
  print(d->d_name,0);
  if(d_type==DT_LNK)
    link_check(d,sb);
  print("",2);
}




#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int skbly7[3]={0,0,0}; //a h l
    int fd, nread,jaadu=0,jaadu_mode=0,temp;
    char buf[BUF_SIZE],dir[1000],jaadu_ka_papa[100]={0};
    struct linux_dirent *d;
    int bpos;
    struct stat sb;
    int without=0,j,p,i=1;
    mode_t val;
    char d_type;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if(argc==1)
    {
      fd = open(".", O_RDONLY | O_DIRECTORY);
    }
    else
    {
      while(i<argc)
      {
        if(argv[i][0]!='-')
        {
          without++;
          p=i;
        }
        else
        {
          j=1;
          while(argv[i][j]!='\n'&&argv[i][j]!='\0')
          {
            if(argv[i][j]=='a')
              skbly7[0]=1;
            if(argv[i][j]=='h')
            {
              skbly7[1]=1;
              h_on=1;
            }
            if(argv[i][j]=='l')
              skbly7[2]=1;
            j++;
          }

        }
        i++;
      }
      if(without==1)
      {
        j=0;
        stat(argv[p],&sb);
        if ((sb.st_mode & S_IFMT) == S_IFREG) 
        {
          i=0;
          i=length(argv[p]);
          i--;
          while(argv[p][i]!='/'&&i>-1)
            i--;
          i++;
          while(i<length(argv[p]))
            jaadu_ka_papa[j++]=argv[p][i++];
          jaadu_ka_papa[j]='\0';
          acc_to_name(argv[p]);

          i=length(argv[p]);
          i--;
          while(argv[p][i]!='/'&&i>0)
            i--;
          if(i==0)
          {
            argv[p][0]='.';
            argv[p][1]='\0';
          }
          else
          argv[p][i]='\0';
          jaadu_mode=1;
        }
        if(chdir(argv[p])!=0)
        {
          print("No such file or directory",2);
          return 0;
        }
        fd=open(".",O_RDONLY | O_DIRECTORY);
      }
      else if(without==0)
      {
        fd = open(".", O_RDONLY | O_DIRECTORY);
      }
      else
      {
        print("I am confused with the inputs you just gave.",2);
        return(0);
      }
    }

    if (fd == -1)
    handle_error("No such directory");
    for ( ; ; ) {
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == -1)
        handle_error("You have enough permissions to open it / Read error");

        if (nread == 0)
        break;
        for (bpos = 0; bpos < nread;) {
            d = (struct linux_dirent *) (buf + bpos);
            d_type = *(buf + bpos + d->d_reclen - 1);
          if((jaadu_mode==0)||((jaadu_mode==1)&&(jaadu_ends(jaadu_ka_papa,d->d_name))))
          {
            print("\e[m",0);
            acc_to_name(d->d_name);
            if(d_type == DT_DIR)
            {
              print("\033[1;34m",0);
            }
            else if(d_type == DT_LNK)
            {
              print("\033[1;31m",0);
            }
            if((skbly7[0]==0)&&(!((*(d->d_name)=='.'))))
            {
              if(skbly7[2]==0)
              {
                temp=length(d->d_name);
                if((jaadu+temp+(10-temp%10))>w.ws_col)
                {
                    print("",2);
                    jaadu=0;
                }
                jaadu=jaadu+temp+(10-temp%10);
                print_name(d->d_name,(10-temp%10));
              }
              else
              {
                long_printing(d,d_type);
              } 
            }
            if(skbly7[0]==1)  
            {
              if(skbly7[2]==0)
              {
                temp=length(d->d_name);
                if((jaadu+temp+(10-temp%10))>w.ws_col)
                {
                    print("",2);
                    jaadu=0;
                }
                jaadu=jaadu+temp+(10-temp%10);
                print_name(d->d_name,(10-temp%10));
              }
              else
              {
                long_printing(d,d_type);
              }
            }
          }
            bpos += d->d_reclen;
        }
    }
    if(total!=0&&jaadu_mode==0)
    {      
      print("total : ",0);
      print(itoa(total/2,10),0);
    }
    print("\e[m",2);
    exit(EXIT_SUCCESS);
}
