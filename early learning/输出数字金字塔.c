#include<stdio.h>
void printSpaces(int n);
void printNumbers(int n);
void printPyramid(int n);
int main(void)
{
    int n;
    printf("请输入一个整数");
    scanf("%d",&n);
    printPyramid(n);
    return 0;
}
void printSpaces(int n)
{
    for(int i=1;i<=n;i++){
        printf(" ");
    }
}
void printNumbers(int n)
{
    for(int i=1;i<=(2*n-1);i++){
        printf("%d",n);
    }
}
void printPyramid(int n)
{
    for(int i=1;i<=n;i++){
        printSpaces(n-i);
        printNumbers(i);
        printf("\n");
    }
}