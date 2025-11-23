#include<stdio.h>
#define pi 3.14159
int fudian(void)
{
    float a;
    double b;//双精度浮点变量，能提供大约15位有效数字
    scanf("%f %lf",&a,&b);//单精度浮点变量输入用%f，双精度用%lf
    printf("a=%.6f,b=%.6f\n",a,b);//.6f表示只输出到小数点后六位
    printf("float所占字节数:%d，double所占字节数:%d",sizeof(a),sizeof(b));
    return 0;
}
int qiupingjun(void)
{
    float a,b,c,d;
    scanf("%f%f%f",&a,&b,&c);
    d=(a+b+c)/3;
    printf("%.3f",d);
    return 0;
}
int main(void)
{
    float radius,area,circumference;//单精度的浮点变量，能提供大约7位有效数字
    printf("请输入一个圆的半径：");
    scanf("%f",&radius);
    area=pi*radius*radius;
    circumference=2*pi*radius;
    printf("半径为%f的圆面积为：%f",radius,area);
    printf("半径为%f的圆周长为：%f",radius,circumference);
    //fudian();
    qiupingjun();
    return 0;
}