//Shivam Khandelwal ( skbly7 )

#include<stdio.h>
int main()
{
    int total[105],a[105][105],path[10005];
    long long int sum;
    int i,j,k,n,m,lol;
    //freopen("free.txt","r",stdin);
    scanf("%d",&lol);
    for(;lol;lol--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<m;i++)
        {
            scanf("%d",&path[i]);
        }
        for(i=0;i<n;i++)
        {
            scanf("%d",&total[i]);
            for(j=0;j<total[i];j++)
            {
                scanf("%d",&a[i][j]);
            }
        }
        sum=0;
        for(i=0;i<m;i++)
        {
            k=path[i];
            n=0;
            for(j=0;j<total[k];j++)
            {
                    if(a[k][j]>a[k][n])
                        n=j;
            }
            sum=sum+a[k][n];
            a[k][n]=0;
        }
        printf("%lld\n",sum);
    }
    return 0;
}
