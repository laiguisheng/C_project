#include<stdio.h>
int main(void)
{
    long long seconds;
    printf("输入秒数：");
    scanf("%lld",seconds);
    printf("%lld秒=",seconds);
    int days=seconds/86400;
    int hours=(seconds%86400)/3600;
    int minutes=(seconds%3600)/60;
    int remaining_seconds=seconds%60;
    printf("%d天，%d小时，%d分钟，%d秒\n",days,hours,minutes,remaining_seconds);
    return 0;
}