#include<stdio.h>
int main(void)
{
    char c;
    printf("请输入一个字符：");
    c=getchar();//从标准输入获取一个字符，并将其赋值给c
    printf("您输入的字符是：");
    putchar(c);//将字符c输出到标准输出流
    printf("\n该字符的ASCII值是：%d",c);
    return 0;
}