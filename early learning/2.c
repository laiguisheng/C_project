#include<stdio.h>
int main(void)
{
    int ivar=10;//有符号整型变量
    signed sivar=-10;//中间省略了int
    unsigned uivar=20;//
    short svar=10;//
    long lvar;//
    unsigned long ulvar=40;//
    long long llvar=20;//
    unsigned long long ullvar=50;//
    printf("int      占的字节数：%d，ivar=%d\n",sizeof(int),ivar);
    printf("short    占的字节数：%d，svar=%hd\n",sizeof(short),svar);
    printf("long     占的字节数：%d，lvar=%hd\n",sizeof(long),lvar);
    printf("long long占的字节数：%d，llvar=%hd\n",sizeof(long long),llvar);
    return 0;
}