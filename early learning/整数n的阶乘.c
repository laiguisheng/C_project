#include<stdio.h>
int main(void)
{
    int n,s;
    s=1;
    printf("请输入一个整数：");
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        s*=i;
    }
    printf("该数的阶乘为：%d",s);
    return 0;
}