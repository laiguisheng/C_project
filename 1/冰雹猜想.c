#include<stdio.h>
int countSteps(int *n,int *count);
int main(){
    int n;
    scanf("%d",&n);
    int count=0;
    countSteps(&n,&count);
    printf("%d",count);
    return 0;
}
int countSteps(int *n,int *count){
    if(*n==1){
        return 0;
    }
    if(*n%2==0){
        *n/=2;
        (*count)++;
        countSteps(n,count);
    }
    else{
        *n=3*(*n)+1;
        (*count)++;
        countSteps(n,count);
    }
}