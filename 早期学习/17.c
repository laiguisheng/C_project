#include<stdio.h>
int main(void)
{
    int x,y;
    printf("请输入点的坐标：x y");
    scanf("%d%d",&x,&y);
    if((x<=1&&x>=-1)&&(y<=1&&y>=-1))
    printf("该点在正方形内");
    else
    printf("不在");
    return 0;
}