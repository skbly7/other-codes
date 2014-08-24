#include<stdio.h>
int main()
{
int t,x,y,z;
float ans;
scanf("%d",&t);
for(;t;t--)
{
scanf("%d %d %d %d",&x,&y,&z,&z);
y=x+y;
ans=x/(float)y;
printf("%f\n",ans);
}
return 0;
}