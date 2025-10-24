#include<stdio.h>
int try(void)
{
    int a1,a2,d,n,an;
    printf("请输入第一项 第二项 n\n");
    scanf("%d%d%d",&a1,&a2,&n);
    d=a2-a1;
    an=a1+(n-1)*d;
    printf("第n项为：%d\n",an);
    return 0;
}
int main(void)
{
    unsigned int s,n;
    scanf("%u",&n);
    s=(n+1)*n/2;
    printf("s=%u\n",s);
    try();
    return 0;
}