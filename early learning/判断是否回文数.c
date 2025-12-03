#include<stdio.h>
int main(void){
    int a=0,b=0;
    printf("请输入一个整数：");
    scanf("%d",&a);
    int c=a;
    while(a){
        b=b*10+a%10;
        a=a/10;
    }
    if(b==c){
        printf("该整数为回文数");
    }
    else{
        printf("该整数不是回文数");
    }
    return 0;
}