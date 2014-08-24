#include<stdio.h>
int ans[100005];
int prime[100000],prime_count;

int count_for(int i)
{
int j,k;
k=i;

for(j=0;j<=prime_count;j++)
{
if(k%prime[j]==0)
{
for(;k%prime[j]==0;)
k=k/prime[j];
return ans[k]+1;
}
}

prime_count++;
prime[prime_count]=k;

return 1;
}

int calculate()
{
int i;
ans[1]=0;
ans[2]=1;
ans[3]=1;
prime_count=1;
prime[0]=2;
prime[1]=3;
for(i=4;i<100004;i++)
{
ans[i]=count_for(i);
}
return 1;
}

int main()
{
    int t,i,j,k,easy;
	prime_count=-1;
	calculate();
	scanf("%d",&t);
	for(;t;t--)
	{
		scanf("%d %d %d",&i,&j,&k);
		easy=0;
		for(;i<=j;i++)
		{
			if(ans[i]==k)
				easy++;
		}
		printf("%d\n",easy);
	}
    return 0;
}