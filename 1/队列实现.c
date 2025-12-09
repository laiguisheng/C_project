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
    //TODO
}

// 入队
void enqueue(struct Queue* q, int value) {
    //TODO
}

// 出队（由于队伍可能为空，这里用返回值表示是否成功）
int dequeue(struct Queue* q, int *value) {
    //TODO
}
