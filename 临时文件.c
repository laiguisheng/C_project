#include<stdio.h>
int main(void)
{
    int a=123;
    printf("%d/%d/%d",a%100,a%10,a%1);
    return 0;
}