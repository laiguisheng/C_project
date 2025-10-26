#include<stdio.h>
int main(void)
{
    char mima[1000];
    int i;
    printf("请输入密码（须为纯字母）：");
    scanf("%s",mima);
    printf("输入的原密码为：%s",mima);
    for(i=0;mima[i]!='\0';i++){
        mima[i]=mima[i]-1;
    }
    printf("凯撒算法加密后的密码为：%s",mima);
    return 0;
}