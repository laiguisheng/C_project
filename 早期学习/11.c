#include<stdio.h>
#include<math.h>
int main(void)
{
    float rate,capital,deposit;
    int n;
    printf("请输入本金（元）：");
    scanf("%f",&capital);
    printf("请输入年利率（%%）：");
    scanf("%f",&rate);
    printf("请输入存款年限：");
    scanf("%d",&n);//%f会自动跳过无意义字符，所以不需要处理缓存区的残留数据
    float factor=1.0+rate/100;
    deposit=capital*pow(factor,n);
    printf("到期时本利之和为%.2f元\n",deposit);
    return 0;
}