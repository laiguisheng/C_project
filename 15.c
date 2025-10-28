#include<stdio.h>
int main(void)
{
    int a,b,c;
    int max,min;
    printf("请输入三个整数：");
    scanf("%d%d%d",&a,&b,&c);
    max=a,min=a;
    if (b>max)
    max=b;
    if(c>max)
    max=c;
    if(b<min)
    min=b;
    if(c<min)
    min=c;
    printf("最大值是：%d\n最小值是：%d\n",max,min);
    return 0;
}