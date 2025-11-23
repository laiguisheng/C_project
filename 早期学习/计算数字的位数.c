#include<stdio.h>
int main(void)
{
    int n,ans=0;
    scanf("%d",&n);
    do
    {
        ans++;
        n/=10;
    } while (n!=0);
    printf("%d",ans);
    return 0;
}