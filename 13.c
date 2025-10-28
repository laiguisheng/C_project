#include<stdio.h>
int main(void)
{
    int a,b;
    a=29.99+10.98;//隐式类型转换，加总后才转为整数
    b=(int)29.99+(int)10.98;//显式类型转换
    printf("%d  %d",a,b);
    return 0;
}