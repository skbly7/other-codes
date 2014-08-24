#include<stdio.h>
int main()
{
int t,x,y,z;
scanf("%d",&t);
for(;t;t--)
{
scanf("%d",&x);
scanf("%d",&y);
scanf("%d",&z);
if(x==1||y==1)
{
if((x==1&&y==1)||(x==1&&y==2)||(x==2&&y==1))
printf("0\n");
else
printf("%d\n",z);
}
else
if(z%2)
printf("%d\n",(z+1)/2);
else
printf("%d\n",z/2);
}
return 0;
}
