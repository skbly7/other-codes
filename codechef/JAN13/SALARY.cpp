/*SHIVAM KHANDELWAl*/
#include<iostream>
using namespace std;
int main()
{
int i,r,q,ans;
long long int n[101],final;
cin>>r;
for(;r;r--)
	{
	cin>>q;
	final=0;
	ans=0;
	for(i=0;i<q;i++)
	{
		cin>>n[i];
		if(n[i]<n[ans]&&i>0)
		ans=i;
	}
i--;
	for(;i>=0;i--)
	{
	if(n[i]!=n[ans])
	final=final+(n[i]-n[ans]);
	}
		cout<<final<<endl;

	}
return 0;
}