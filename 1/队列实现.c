#include<stdio.h>
#include<stdlib.h>
struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;  // 队头指针
    struct Node* rear;   // 队尾指针
};

// 初始化队列
struct Queue* init_queue() {
    struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
    q->front=NULL;
    q->rear=NULL;
    return q;
}

// 入队
void enqueue(struct Queue* q, int value) {
    struct Node* new_value=(struct Node*)malloc(sizeof(struct Node));
    new_value->data=value;
    if((q->rear==NULL)&&(q->front==NULL)){
        q->front=new_value;
        q->rear=new_value;
    }
    else{
        q->rear->next=new_value;
        q->rear=new_value;
        new_value->next=NULL;
    }
}

// 出队（由于队伍可能为空，这里用返回值表示是否成功）
int dequeue(struct Queue* q, int *value) {
    //TODO
    if((q->rear==NULL)&&(q->front==NULL)){
        return 0;
    }
    else{
        if(q->front==q->rear){
            *value=q->front->data;
            struct Node* temp=q->front;
            q->front=NULL;
            q->rear=NULL;
            free(temp);
            return 1;
        }
        struct Node* temp=q->front->next;
        *value=q->front->data;
        free(q->front);
        q->front=temp;
        return 1;
    }
}
