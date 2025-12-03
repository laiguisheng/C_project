#include<stdio.h>
int main(void)
{
    int a=1,b=3,c=5;
    a=b,c;//先执行a=b，再执行c
    printf("a的值为%d\n",a);
    a=(b,c);//(b,c)是一个表达式，结果是c，逗号运算符会按从左到右的顺序执行多个表达式，并且最终的结果是最右边表达式的值，逗号运算符的优先级是最低的
    printf("a的值为%d\n",a);
    return 0;
}