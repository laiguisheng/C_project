//网盘下载
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 用户节点定义：存储单个用户的信息及链表指针
typedef struct Node {
    char name[50];       // 用户名（最多49个字符+1个结束符）
    int level;           // 用户等级（1=普通用户, 2=VIP用户, 3=SVIP用户，等级越高优先级越高）
    struct Node* next;   // 指向下一个用户节点的指针，构成链表结构
} Node;

// 队列结构体：基于链表实现的优先级队列，记录队头和队尾
typedef struct Queue {
    Node* front;  // 队头指针（指向队列第一个元素，用于出队操作）
    Node* rear;   // 队尾指针（指向队列最后一个元素，用于快速入队）
} Queue;

// 初始化队列
// 参数：q-待初始化的队列指针
void initQueue(Queue* q) {
    // TODO：完成队列初始化代码，队头用front,队尾用rear表示
    q->front=NULL;  // 队头指针初始化为NULL，表示空队列
    q->rear=NULL;   // 队尾指针初始化为NULL，表示空队列
}

// 创建用户节点：为单个用户分配内存并初始化信息
// 参数：name-用户名，level-用户等级
// 返回值：指向新创建节点的指针
Node* createNode(const char* name, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 为节点分配堆内存
    strcpy(newNode->name, name);                  // 复制用户名到节点中
    newNode->level = level;                       // 初始化用户等级
    newNode->next = NULL;                         // 初始化后继指针为NULL
    return newNode;                               // 返回新节点指针
}

// Request操作：入队（带优先级插入，高等级优先排在前面）
// 参数：q-队列指针，name-用户名，level-用户等级
void request(Queue* q, const char* name, int level) {
    Node* newNode = createNode(name, level);  // 创建新用户节点
    // 队列为空，直接将新节点作为队列唯一元素
    if (q->front == NULL) {
        // TODO：完成队列为空的逻辑
        q->front=newNode;  // 队头指向新节点
        q->rear=newNode;   // 队尾指向新节点
        return;
    }
    // 插入逻辑：高等级插在低等级用户前面，同等级则排在后面（按入队顺序）
    // TODO：请按照该部分的要求补全代码
    Node* ftemp=q->front;  // 遍历指针，初始指向队头
    Node* stemp=NULL;      // 前驱指针，记录遍历指针的上一个节点
    
    // 遍历队列，找到新节点应插入的位置（直到遇到比新节点等级低的节点或队列末尾）
    while(ftemp!=NULL&&newNode->level<=ftemp->level){
        stemp=ftemp;       // 前驱指针跟随遍历指针移动
        ftemp=ftemp->next; // 遍历指针后移
    }
    
    // 情况1：遍历到队列末尾（新节点等级最低，插入队尾）
    if(ftemp==NULL){
        stemp->next=newNode;  // 原队尾节点的后继指向新节点
        q->rear=newNode;      // 更新队尾指针为新节点
    }
    // 情况2：遍历指针未移动（新节点等级最高，插入队头）
    else if(stemp==NULL){
        q->front=newNode;     // 更新队头指针为新节点
        newNode->next=ftemp;  // 新节点的后继指向原队头
    }
    // 情况3：插入到队列中间（两个节点之间）
    else{
        newNode->next=ftemp;  // 新节点的后继指向遍历指针当前节点
        stemp->next=newNode;  // 前驱节点的后继指向新节点
    }
}

// Download操作：输出队首元素，并删除该元素（出队操作）
// 参数：q-队列指针
void download(Queue* q) {
    // 队列为空，无法执行下载操作
    if (q->front == NULL) {
        printf("队列为空，没有可下载的任务。\n");
        return;
    }
    Node* temp = q->front;  // 临时指针保存队头节点（便于释放内存）
    printf("下载中：%s (level=%d)\n", temp->name, temp->level);  // 输出队头用户信息
    //TODO：继续完成删除队首元素的逻辑
    q->front=temp->next;    // 队头指针后移，指向原队头的下一个节点
    // 若队头指针为NULL（队列仅剩一个元素），同步更新队尾指针为NULL
    if(q->front==NULL){
        q->rear=NULL;
    }
    free(temp);  // 释放原队头节点的内存，避免内存泄漏
}

// Remove操作：删除指定用户名的用户节点
// 参数：q-队列指针，name-待删除的用户名
void removeUser(Queue* q, const char* name) {
    // 队列为空，无法执行删除操作
    if (q->front == NULL) {
        printf("队列为空，无法删除。\n");
        return;
    }
    Node* prev = NULL;   // 前驱指针，记录当前节点的上一个节点
    Node* curr = q->front;  // 遍历指针，初始指向队头
    
    // TODO：请完善寻找指定用户位置的逻辑
    // 遍历队列，找到与指定用户名匹配的节点
    while (curr != NULL && strcmp(curr->name, name) != 0) {
        prev=curr;       // 前驱指针跟随遍历指针移动
        curr=curr->next; // 遍历指针后移
    }
    
    // 遍历结束未找到指定用户
    if (curr == NULL) {
        printf("未找到用户：%s\n", name);
        return;
    }
    
    // 删除指定用户，注意考虑队头、队尾和中间三种情况
    // TODO：请完善该部分代码
    // 情况1：待删除节点在队列中间（既不是队头也不是队尾）
    if(q->front!=curr&&q->rear!=curr){
        prev->next=curr->next;  // 前驱节点的后继指向当前节点的下一个节点
    }
    // 情况2：待删除节点是队头
    else if(q->front==curr){
        q->front=curr->next;    // 队头指针后移，指向当前节点的下一个节点
    }
    // 情况3：待删除节点是队尾
    else{
        q->rear=prev;           // 队尾指针更新为前驱节点
        prev->next=NULL;        // 前驱节点的后继置为NULL，成为新的队尾
    }
    
    free(curr);  // 释放待删除节点的内存
    printf("已删除用户：%s\n", name);  // 提示删除成功
}

// Display操作：显示队列中所有用户的信息
// 参数：q-队列指针
void display(Queue* q) {
    // 队列为空，提示当前队列状态
    if (q->front == NULL) {
        printf("当前队列为空。\n");
        return;
    }
    Node* curr = q->front;  // 遍历指针，初始指向队头
    printf("当前下载队列：\n");
    // 遍历队列，输出所有用户信息
    while (curr != NULL) {
        printf("用户名: %-10s | level: %d\n", curr->name, curr->level);
        // TODO：请完善剩余代码逻辑
        curr=curr->next;  // 遍历指针后移，访问下一个节点
    }
}

// 主函数：模拟某度网盘下载调度系统的操作命令
int main() {
    Queue q;
    initQueue(&q);  // 初始化下载队列

    char command[50];  // 存储用户输入的命令
    char name[50];     // 存储用户名
    int level;         // 存储用户等级
    printf("=== 某度网盘下载调度系统 ===\n"); 
    printf("支持命令：Request 用户名 level | Download | Remove 用户名 | Display | Exit\n");
    printf("请输入命令：\n");
    
    // 循环接收并处理用户命令，直到输入Exit退出
    while (1) {
        scanf("%s", command);  // 读取命令关键字
        if (strcmp(command, "Request") == 0) {
            scanf("%s %d", name, &level);  // 读取用户名和等级
            // 完善用户等级判断逻辑，当出现无效用户等级时，输出提示信息并换行
            // TODO：
            if(level!=1&&level!=2&&level!=3){
                printf("无效的用户等级，请输入 1（普通） 2（VIP） 3（SVIP）。\n");
                continue;  // 跳过本次命令，等待下一次输入
            }
            request(&q, name, level);  // 执行入队操作
            printf("用户 %s (level=%d) 已加入队列。\n", name, level);  // 提示入队成功

        } else if (strcmp(command, "Download") == 0) {
            download(&q);  // 执行出队（下载）操作
                                        
        } else if (strcmp(command, "Remove") == 0) {
            scanf("%s", name);  // 读取待删除的用户名
            removeUser(&q, name);  // 执行删除用户操作

        } else if (strcmp(command, "Display") == 0) {
            display(&q);  // 执行显示队列操作

        } else if (strcmp(command, "Exit") == 0) {
            printf("程序已退出。\n");
            break;  // 退出循环，结束程序
        } 
        // 完善代码逻辑，当输入无效命令时，输出提示信息并换行
        // TODO：
        else{
            printf("无效命令，请重新输入。\n");
            continue;  // 跳过本次命令，等待下一次输入
        }
    }

    return 0;  // 程序正常结束
}