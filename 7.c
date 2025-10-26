#include<stdio.h>//求三位整数的逆序数
int main(void)
{
    int x,a,b,c;
    scanf("%d",&x);
    a=x/100,b=x/10%10,c=x%10;
    //printf("%d%d%d\n",c,b,a);
    printf("%d",c*100+b*10+a);
    return 0;
}