#include<stdio.h>
int main(void)
{
    int m,n,i,sum;
    printf("请输入区间，形式如1 5：");
    scanf("%d %d",&m,&n);
    if (m%2==0)
    i=m+1;
    else 
    i=m;
    for(sum=0;i<=n;i=i+2){
        sum+=i;
    }
    printf("该区间内所有奇数的和为：%d",sum);
    return 0;
}