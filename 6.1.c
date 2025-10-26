#include<stdio.h>
#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60
int main(void)
{
    long long seconds;
    printf("输入秒数：");
    scanf("%lld",seconds);
    printf("%lld秒=",seconds);
    int days=seconds/SECONDS_PER_DAY;
    int hours=(seconds%SECONDS_PER_DAY)/SECONDS_PER_HOUR;
    int minutes=(seconds%SECONDS_PER_HOUR)/SECONDS_PER_MINUTE;
    int remaining_seconds=seconds%SECONDS_PER_MINUTE;
    printf("%d天，%d小时，%d分钟，%d秒\n",days,hours,minutes,remaining_seconds);
    return 0;
}