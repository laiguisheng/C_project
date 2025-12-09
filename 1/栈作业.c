#include<stdio.h>
#include<stdlib.h>
#define N 100
typedef struct STACK
{
    char* data;
    int top;
    int capacity;
}stack;
void push(stack *one,int *top,char ch);
void pop(stack *one,int *top);
int  main(){
    stack one={0,-1,N};
    one.data=(char*)malloc(one.capacity*sizeof(char));
    char ch;
    while((ch=getchar())!=EOF&&ch!='\n'){
        push(&one,&one.top,ch);
    }
    while(one.top!=-1){
        pop(&one,&one.top);
    }
    free(one.data);
    return 0;
}
void push(stack *one,int *top,char ch){
    if(*top>=one->capacity-1){
        return;
    }
    (*top)++;
    one->data[*top]=ch;
}
void pop(stack *one,int *top){
    if(*top==-1){
        return;
    }
    printf("%c",one->data[*top]);
    (*top)--;
}