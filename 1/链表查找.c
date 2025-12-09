#include <stdio.h>
#include <stdlib.h> // malloc, free

struct Node {
    int data;
    struct Node* next;
};

// 提示：快慢指针
int find_kth_from_end(struct Node* list, int k) {
    //TODO
    if(k<=0){
        return 0;
    }
    struct Node* fast=list;
    struct Node* low=list;
    for(int i=0;i<k;i++){
        fast=fast->next;
    }
    if(fast==NULL){
        return 0;
    }
    while(fast!=NULL){
        fast=fast->next;
        low=low->next;
    }
    printf("%d",low->data);
    return 1;
}
