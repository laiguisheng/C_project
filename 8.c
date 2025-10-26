#include<stdio.h>
int exchange(void)
{
    int a,b,t;
    scanf("%d%d",&a,&b);
    printf("交换前a=%d，b=%d\n",a,b);
    t=a,a=b,b=t;//利用中间变量完成互换
    printf("交换后a=%d，b=%d",a,b);
    return 0;
}
int main(void)
{
    int a=7,b=7,c,d;
    a=a+1;
    c=a++;//后缀方式：先赋变量c为变量a的值，然后使变量a再增1
    d=++b;//前缀方式：先使变量b增1，再赋变量c为变量b的值
    printf("a=%d,b=%d,c=%d,d=%d",a,b,c,d);
    exchange();
    return 0;
}