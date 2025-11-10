#include<stdio.h>
#include<stdlib.h>
int qiuheidongshu(int n)
{
    int a1,a2,a3;
    int max,middle,min;
    a1=n%10;
    a2=n/10%10;
    a3=n/100;
    if(a1>=a2&&a1>=a3){
        max=a1;
        if(a2>=a3){
            middle=a2;
            min=a3;
        }
        else{
            middle=a3;
            min=a2;
        }
    }
    else if(a2>=a1&&a2>=a3){
        max=a2;
        if(a1>=a3){
            middle=a1;
            min=a3;
        }
        else{
            middle=a3;
            min=a1;
        }
    }
    else{
        max=a3;
        if(a1>=a2){
            middle=a1;
            min=a2;
        }
        else{
            middle=a2;
            min=a1;
        }
    }
    int maxV=100*max+10*middle+1*min;
    int minV=100*min+10*middle+1*max;
    return maxV-minV;
}
int main(void)
{
    int n,t;
    printf("请输入一个三位整数：");
    scanf("%d",&n);
    do{
        t=t+1;
        n=qiuheidongshu(n);
    }while(n&&n!=495);
    printf("循环次数：%d",t);
    printf("黑洞数为：%d",n);
    return 0;
}