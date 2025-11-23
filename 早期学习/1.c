#include<stdio.h>

int second(void)
{
    int a=10;
    printf("变量a的地址是：%#x，变量a的值是：%d\n",&a,a);
    printf("变量a占%d字节！",sizeof(a));
    return 0;
}

int main(void)
{
    int a,b;
    printf("请输入两个整数，两个整数中间用空格分隔：");
    scanf("%d%d\n",&a,&b);//%d与%d之间没有空格、有一个空格时，输入时需要间隔一个空格，若改为逗号，则需要间隔一个逗号
    printf("%d+%d=%d\n",a,b,a+b);
    second();
    return 0;
}