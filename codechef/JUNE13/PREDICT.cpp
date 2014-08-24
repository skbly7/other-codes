#include<stdio.h>
int main()
{
    int t;
    double i,rate1,rate2,x,x2;
    scanf("%d",&t);
    for(;t>0;t--)
    {   scanf("%lf",&i);
        rate1=((2.0*i)+1.0)*(1.0-i);
        if(rate1>=1)
            printf("%0.9lf\n",rate1*10000.0);
        else
        {
            rate2=(3.0-(2.0*i))*i;
            printf("%0.9lf\n",rate2*10000.0);
        }
    }
    return 0;
}
