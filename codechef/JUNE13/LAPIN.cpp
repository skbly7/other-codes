#include<stdio.h>
#include<string.h>
char a[1001];
int program();
int main()
{
    int i,p;
    scanf("%d",&i);
    while(i>0)
    {
        p=program();
        i--;
    }
    return 0;
}

int program()
{
    int j,k,start2=0,end1,l=0,removed=0,valid=1;
    char test;

    //gets(a);
    scanf("%s",a);
    l=strlen(a);
    if(l%2==0)
    {
        start2=l/2;
        end1=start2-1;
    }
    else
    {
        start2=(l+1)/2;
        end1=start2-2;
    }
    for(j=0;j<=end1&&(valid);j++)
    {
        test=a[j];
        removed=0;
        for(k=start2;k<l&&(!removed);k++)
        {
            if(test==a[k])
            {
                a[k]='1';
                removed=1;
            }
        }
        if((!removed))
        {
            valid=0;
        }
    }
    if(valid)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}
