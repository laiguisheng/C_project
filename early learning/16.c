#include<stdio.h>
int main(void)
{
    int a;
    printf("请输入一个数：");
    scanf("%d",&a);
    if(a%2==0)
    printf("a为偶数");
    else
    printf("a为奇数");
    return 0;
}