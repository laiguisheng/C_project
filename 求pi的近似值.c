#include<stdio.h>
int main(void)
{
    double eps,pi=1;
    double tmp1=1,tmp2=1,term=1;
    scanf("%le",&eps);
    int i=1;
    while(term>=eps)
    {
        tmp1=tmp1*i;
        tmp2=tmp2*(2*i+1);
        term=tmp1/tmp2;
        pi+=term;
        i++;
    }
    printf("pi=%.9f",pi*2);
    return 0;
}