/*
三天打渔两天晒网
作者：46
日期：2025.11.18、
版本：v1.0
*/
#include<stdio.h>
int main()
{
    int year,month,day;
    int syear=1990,smonth=1,sday=1;
    scanf("%d-%d-%d",&year,&month,&day);
    int sumdays=0;
    for(int i=1990;i<year;i++){
        if(i%4==0){
            if(i%100==0&&i%400!=0){
                sumdays+=365;
            }
            else{
                sumdays+=366;
            }
        }
        else{
            sumdays+=365;
        }
    }
    for(int j=1;j<month;j++){
        if(j==1||j==3||j==5||j==7||j==8||j==10||j==12){
            sumdays+=31;
        }
        else if(j=2){
            if((year%4==0&&year%100!=0)||(year%400==0)){
                sumdays+=29;
            }
            else{
                sumdays+=28;
            }
        }
        else if(j==4||j==6||j==9||j==11){
            sumdays+=30;
        }
        else{
            printf("Invalid input");
            return 0;
        }
    }
//检测天数是否合法
    if((month==1||month==3||month==5||month==7||month==8||month==10||month==12)&&day>31){
            printf("Invalid input");
            return 0;
    }
    else if(month=2&&day>28){
        if(((year%4==0&&year%100!=0)||(year%400==0))&&day>29){
            printf("Invalid input");
            return 0;
        }
    }
    else if((month==4||month==6||month==9||month==11)&&day>30){
            printf("Invalid input");
            return 0;
        }
    int a=(sumdays+day)%5;
    if(a<=3&&a>0){
        printf("working");
    }
    else{
        printf("rest");
    }
    return 0;
}