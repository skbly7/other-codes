#include<stdio.h>
int main()
{
    long long int t,n,k,f,s;
    scanf("%lld",&t);
    for(;t>0;t--)
    {
        scanf("%lld %lld",&n,&k);
        if(k)
        {
            f=n/k;
            s=n-(k*f);
            printf("%lld %lld\n",f,s);
        }
        else
        printf("0 %lld\n",n);
    }
    return 0;
}
