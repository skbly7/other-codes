#include<string.h>
#include<stdio.h>
#include<iostream>
using namespace std;
char a[201];
 
int ans,i,j,l;
void program()
{
cin>>a;
int c[2][26];
for(i=0;i<2;i++)
for(j=0;j<26;j++)
c[i][j]=0;
 
 
for(l=0;a[l]!='\0';l++);
for(i=0;i<l;i++)
{
if(a[i]<96)
c[0][((int)a[i])-65]++;
else
c[1][((int)a[i])-97]++;
}
 
ans=0;
for(i=0;i<2;i++)
for(j=0;j<26;j++)
if(c[i][j]%2==0)
ans=ans+c[i][j]/2;
else
ans=ans+1+c[i][j]/2;
cout<<ans<<endl;
}
 
 
 
 
int main()
{
int t;
cin>>t;
for(;t>0;t--)
{
program();
}
 
return 0;
}