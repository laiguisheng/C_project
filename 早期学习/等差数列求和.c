#include<stdio.h>
int main(void)
{
    int a,d,n,sum=0;
    scanf("%d %d %d",&a,&d,&n);
    for(int i=1;i<=n;i++){
        sum+=a;
        a+=d;
    }
    printf("sum=%d\n",sum);
    return 0;
}