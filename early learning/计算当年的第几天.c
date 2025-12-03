#include<stdio.h>
int countdays(int y,int m,int d);
int main(void)
{
    int y,m,d;
    printf("请输入年.月.日\n");
    scanf("%d.%d.%d",&y,&m,&d);
    printf("%d",countdays(y,m,d));
    return 0;
}
int countdays(int y,int m,int d)
{
    int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int days=0;
    if(y%400==0||(y%4==0&&y%100!=0)){
        a[2]=29;
    }
    for(int i=1;i<=m-1;i++){
        days+=a[i];
    }
    days+=d;
    return days;
}