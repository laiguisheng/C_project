#include<stdio.h>
#include<math.h>
int main(void)
{
    int x=-1;
    printf("%x\n",x);//十六进制结果
    printf("%d\n",x);
    printf("%u\n",x);
    printf("%.0f\n",ldexp(1,32)-1);
    return 0;
}