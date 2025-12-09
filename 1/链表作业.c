// 以下假设结点通过 malloc 分配内存，在删除结点时通过 free 回收内存
#include<stdio.h>
#include <stdlib.h> // malloc, free
struct Node {
    int data;
    struct Node* next;
};
// 递归方法（由于表头结点的存在，包装一层来跳过它）
// 真正的实现
struct Node* _recursively_remove_nodes(struct Node* head, int x) {
    if(head==NULL){
        return NULL;
    }
    struct Node* processed_next=_recursively_remove_nodes(head->next,x);
    if(head->data==x){
        free(head);
        return processed_next;
    }
    else{
        head->next=processed_next;
        return head;
    }
}

// 包装函数
struct Node* recursively_remove_nodes(struct Node* head, int x) {
    head->next=_recursively_remove_nodes(head->next,x);
    return head;
}

// 迭代方法
struct Node* iteratively_remove_nodes(struct Node* head, int x) {
    //TODO
    struct Node* start=head;
    if(head==NULL){
        return NULL;
    }
    while(head->next!=NULL){
        if(head->next->data==x){
            struct Node* temp=head->next->next;
            free(head->next);
            head->next=temp;
        }
        else{
            head=head->next;
        }
    }
    return start;
}
