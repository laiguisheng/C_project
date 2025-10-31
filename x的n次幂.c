#include<stdio.h>
int main(void)
{
    int n;
    double sum=1;
    double x;
    printf("请输入一个整数和要求它幂的次数，如3 5：");
    scanf("%lf %d",&x,&n);
    for(int i=1;i<=n;i++){
        sum*=x;
    }
    printf("%lf",sum);
    return 0;
}