#include<stdio.h>
int main(void)
{
    float x,y;
    printf("请输入一个0-20以内的浮点数");
    scanf("%f",&x);
    if(x>=0&&x<5){
        y=-x+2.5;
        printf("对应y的值为%f",y);
    }
    else if(x>=5&&x<10){
        y=2-1.5*(x-3)*(x-3);
        printf("对应y的值为%f",y);
    }
    else if(x>=10&&x<20){
        y=x/2-1.5;
        printf("对应y的值为%f",y);
    }
    else printf("输入的浮点数不在定义域内");
    return 0;
}