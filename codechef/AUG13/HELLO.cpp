//Shivam khandelwal ( skbly7 )

#include<stdio.h>
int main()
{
    int i,plans,T,best_plan;
    float default_rate,month,new_rate,cost,minutes,max_cost,new_cost;

//    freopen("free.txt","r",stdin);
    scanf("%d",&T);
    for(;T;T--)
    {
        best_plan=0;
        scanf("%f %f %d",&default_rate,&minutes,&plans);
        max_cost=default_rate*minutes;
        for(i=0;i<plans;i++)
        {
            scanf("%f %f %f",&month,&new_rate,&cost);
            new_cost=(new_rate*minutes)+((cost*1.00)/month);
            //printf("%f\n",new_cost);
            if(max_cost>new_cost)
            {
                max_cost=new_cost;
                best_plan=i+1;
            }
        }
        printf("%d\n",best_plan);
    }
    return 0;
}

