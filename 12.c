#include<stdio.h>
int main(void)
{
    char lowerch,upperch;
    printf("请输入小写字母：");
    scanf("%c",&lowerch);
    upperch=lowerch-32;//C语言中，字符型变量本质上存储的是字符对应的ASCII码，所以对其运算时实际是对ASCII码的整数进行运算
    printf("%c对应的大写字母为：%c\n",lowerch,upperch);
    printf("%c和%c对应的ASCII码值分别为%d和%d\n",lowerch,upperch,lowerch,upperch);//字符型变量的输出取决于输出符号的不同
    return 0;
}