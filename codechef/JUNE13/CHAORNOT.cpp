//skbly7 Shivam Khandelwal
#include<stdio.h>
int a[100002];
int sol[100002];
void quicksort (int lo, int hi)
{
    int i=lo, j=hi, h;
    int x=a[(lo+hi)/2];
    do {
        while (a[i]<x) i++;     while (a[j]>x) j--;
        if (i<=j) {
            h=a[i]; a[i]=a[j]; a[j]=h; i++; j--;
        }
    } while (i<=j);
    if (lo<j) quicksort(lo, j);
    if (i<hi) quicksort(i, hi);
}
int interpolation_search(int bottom, int top, int item) {

 int mid;
 while (bottom <= top)
 {
  mid = (top+bottom)/2;
  if (item == sol[mid])
   return mid + 1;
  if (item < sol[mid])
   top = mid - 1;
  else
   bottom = mid + 1;
 }
 return -1;
}
int main()
{
    int i,j,k,p,t,add,ans,test_mode=0;
    int b[100002];
    int total=0;
    if(test_mode)
    {
        i=30000;
        for(j=0;j<i;j++)
            a[j]=j;
    }
    else
    {
        scanf("%d",&i);
        for(j=0;j<i;j++)
        {
            scanf("%d",&a[j]);
         }
    }
    quicksort(0,i-1);
    sol[0]=a[0];
    total=1;
    for(j=1;j<i;j++)
    {
        add=1;
        for(k=total-1;k>=0;k--)
        {
            if((a[j]%2)==(sol[k]%2))
            {
                if(interpolation_search(k,total,(sol[k]+((a[j]-sol[k])/2)))!=-1)
                   {
                       add=0;
                       break;
                   }
            }
        }
		if(add)
        {
            sol[total++]=a[j];
        }
    }
    printf("%d\n",total);
    for(j=0;j<total;j++)
    {
        printf("%d ",sol[j]);
    }
    return 0;
}
