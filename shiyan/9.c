//json匹配
// 程序功能：实现JSON字符串的括号匹配检查（基础版+进阶版），进阶版支持忽略字符串内括号和处理转义字符
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 栈元素结构体：存储括号类型（{/}/[/]）和所在索引（便于报错定位）
typedef struct {
    char bracket;  // 存储括号字符（{、}、[、]）
    int position;  // 存储括号在JSON字符串中的位置索引（从0开始计数）
} StackElem;

// 栈结构体（动态扩容设计，避免固定容量的局限性）
typedef struct {
    StackElem* data;     // 指向栈数据数组的指针，存储栈元素
    int top;             // 栈顶指针（-1表示空栈，指向栈顶元素的下标）
    int capacity;        // 当前栈的容量（可容纳的元素个数）
    int max_capacity;    // 栈的最大容量（扩容的上限）
} Stack;

// 栈操作结果枚举：规范栈操作的返回状态，增强程序健壮性
typedef enum {
    STACK_OK,           // 操作成功
    STACK_EMPTY,        // 栈为空（弹栈/查看栈顶操作失败）
    STACK_FULL,         // 栈已满（压栈操作失败，且无法扩容）
    STACK_MEM_ERR       // 内存分配/扩容失败
} StackResult;

// ----------------------------// 学生需实现的栈接口// ----------------------------
// 1. 初始化栈（指定初始容量和最大容量）
// stack：指向待初始化的栈结构体指针
// init_capacity：栈的初始容量
// max_capacity：栈的最大容量
StackResult stackInit(Stack* stack, int init_capacity, int max_capacity){
    // 步骤1：检查init_capacity和max_capacity合法性（初始容量≤最大容量，且均大于0）
    if(init_capacity<=max_capacity&&init_capacity>0){
        // 步骤2：为栈数据数组分配内存，大小为初始容量×栈元素大小
        stack->data=(StackElem*)malloc(init_capacity*sizeof(StackElem));
        // 步骤3：初始化栈的核心参数
        stack->top=-1;          // 栈顶指针初始化为-1，表示空栈
        stack->capacity=init_capacity;  // 当前容量设为初始容量
        stack->max_capacity=max_capacity;  // 最大容量设为指定值
        return STACK_OK;        // 返回操作成功状态
    }
    else{
        return STACK_MEM_ERR;   // 参数不合法，返回内存错误状态
    }
}

// 2. 压栈（将括号和位置信息存入栈顶）
// stack：指向栈结构体的指针
// bracket：待存入的括号字符
// position：待存入括号的位置索引
StackResult stackPush(Stack* stack, char bracket, int position){
    // 步骤1：检查栈是否已满（栈顶指针+1等于当前容量）
    if(stack->top+1 == stack->capacity){
        // 步骤2：若栈未满最大容量，则进行扩容（容量+1）
        if(stack->capacity<stack->max_capacity){
            StackElem* new=(StackElem*)realloc(stack->data,(stack->capacity+1)*sizeof(StackElem));
            stack->data=new;    // 更新栈数据数组指针
            stack->capacity++;  // 更新当前栈容量
        }
        else{
            return STACK_FULL;  // 栈已达最大容量，无法扩容，返回栈满状态
        }
    }
    // 步骤3：栈顶指针上移，存入括号和位置信息
    ++stack->top;
    stack->data[stack->top].bracket=bracket;
    stack->data[stack->top].position=position;
    return STACK_OK;            // 返回压栈成功状态
}

// 3. 弹栈（取出栈顶元素，通过elem输出结果）
// stack：指向栈结构体的指针
// elem：指向栈元素的指针，用于接收弹出的栈顶数据
StackResult stackPop(Stack* stack, StackElem* elem){
    // 步骤1：检查栈是否为空
    if(stackIsEmpty(stack)){
        return STACK_EMPTY;     // 栈空，返回弹栈失败状态
    }
    // 步骤2：将栈顶元素赋值给elem，回传数据
    elem->bracket=stack->data[stack->top].bracket;
    elem->position=stack->data[stack->top].position;
    // 步骤3：栈顶指针下移，完成弹栈
    --stack->top;
    return STACK_OK;            // 返回弹栈成功状态
}

// 4. 查看栈顶（获取栈顶元素，不弹出）
// stack：指向栈结构体的指针
// elem：指向栈元素的指针，用于接收栈顶数据
StackResult stackPeek(Stack* stack, StackElem* elem) {
    // 步骤1：检查栈是否为空
    if(stackIsEmpty(stack)){
        return STACK_EMPTY;     // 栈空，返回查看失败状态
    }
    // 步骤2：将栈顶元素赋值给elem，回传数据
    elem->bracket=stack->data[stack->top].bracket;
    elem->position=stack->data[stack->top].position;
    return STACK_OK;            // 返回查看成功状态
}

// 5. 判空（判断栈是否为空）
// stack：指向栈结构体的常量指针（不修改栈内容）
// 返回值：1表示栈空，0表示栈非空
int stackIsEmpty(const Stack* stack){
    // 栈顶指针为-1时表示空栈，使用三目运算符返回判断结果
    return stack->top == -1 ? 1 : 0;
}

// 6. 销毁栈（释放内存，避免内存泄漏）
// stack：指向栈结构体的指针
void stackDestroy(Stack* stack) {
    // 步骤1：释放栈数据数组的堆内存
    free(stack->data);
    // 步骤2：重置栈的核心参数
    stack->top=-1;          // 栈顶指针重置为-1
    stack->capacity=0;      // 当前容量重置为0
}

// 辅助函数：判断字符是否为左括号（{ 或 [）
// ch：待判断的字符
// 返回值：1表示是左括号，0表示不是
int isLeftBracket(char ch) {
    return ch == '{' || ch == '[';
}

// 辅助函数：判断字符是否为右括号（} 或 ]）
// ch：待判断的字符
// 返回值：1表示是右括号，0表示不是
int isRightBracket(char ch) {
    return ch == '}' || ch == ']';
}

// 辅助函数：判断左右括号是否匹配
// left：左括号字符
// right：右括号字符
// 返回值：1表示匹配，0表示不匹配
int isBracketMatch(char left, char right) {
    // 匹配规则：{ 对应 }，[ 对应 ]
    return (left == '{' && right == '}') || (left == '[' && right == ']');
}

// 栈基础版本实现：简单JSON括号匹配检查（不处理字符串内括号）
// json_str：待检查的JSON字符串指针
// 返回值：1表示括号匹配合法，0表示不合法
int jsonBracketCheckBasic(const char *json_str) {
    // 步骤1：处理边界情况（字符串为NULL或空字符串，视为合法）
    if(*json_str==NULL || strlen(json_str)==0){
        return 1;
    }
    // 步骤2：创建并初始化栈（初始容量10，最大容量100）
    Stack* temp=(Stack*)malloc(sizeof(Stack));
    stackInit(temp,10,100);
    int count=0;  // 记录当前字符的位置索引
    // 步骤3：遍历JSON字符串的每个字符
    while(*json_str!='\0'){
        // 遇到左括号，压入栈中
        if(isLeftBracket(*json_str)){
            stackPush(temp,*json_str,count);
        }
        // 遇到右括号，检查匹配性
        if(isRightBracket(*json_str)){
            StackElem elem;
            // 栈为空（无对应的左括号），直接判定不合法
            if(stackIsEmpty(temp)){
                stackDestroy(temp);
                free(temp);
                return 0;
            }
            // 查看栈顶左括号，判断是否匹配
            stackPeek(temp,&elem);
            if(isBracketMatch(elem.bracket,*json_str)){
                stackPop(temp,&elem);  // 匹配成功，弹出栈顶左括号
            }
            else{
                // 匹配失败，释放资源后返回不合法
                stackDestroy(temp);
                free(temp);
                return 0;
            }
        }
        count++;      // 位置索引自增
        json_str++;   // 遍历下一个字符
    }
    // 步骤4：遍历结束后，栈为空表示所有括号匹配完成
    if(stackIsEmpty(temp)){
        stackDestroy(temp);
        free(temp);
        return 1;
    }
    else{
        // 栈非空（存在未匹配的左括号），返回不合法
        stackDestroy(temp);
        free(temp);
        return 0;
    }
}

// 栈进阶版本实现：增强版JSON括号匹配检查（忽略字符串内括号，处理转义字符）
// json_str：待检查的JSON字符串指针
// 返回值：1表示括号匹配合法，0表示不合法
int jsonBracketCheckAdvanced(const char *json_str) {
    // 步骤1：处理边界情况（字符串为NULL或空字符串，视为合法）
    if(json_str==NULL || strlen(json_str)==0){
        return 1;
    }
    // 步骤2：创建并初始化栈（初始容量10，最大容量100）
    Stack* temp=(Stack*)malloc(sizeof(Stack));
    stackInit(temp,10,100);
    int in_string=0;  // 标记是否处于字符串内（0：不在，1：在）
    int escape=0;     // 标记是否处于转义状态（0：未转义，1：转义中）
    int count=0;      // 记录当前字符的位置索引
    // 步骤3：遍历JSON字符串的每个字符
    while(*json_str!='\0'){
        // 情况1：处于字符串内（括号不参与匹配）
        if(in_string==1){
            if(escape==1){
                escape=0;  // 处于转义状态，当前字符转义后，取消转义标记
            }
            else if(*json_str=='\\'){
                escape=1;  // 遇到转义字符\，进入转义状态
            }
            else if(*json_str=='"'&&escape==0){
                in_string=0;  // 遇到非转义的引号"，退出字符串状态
            }
            json_str++;   // 遍历下一个字符
            count++;      // 位置索引自增
        }
        // 情况2：不处于字符串内（处理括号和引号）
        else{
            if(*json_str=='"'){
                in_string=1;  // 遇到引号"，进入字符串状态
            }
            // 遇到左括号，压入栈中
            if(isLeftBracket(*json_str)){
                stackPush(temp,*json_str,count);
            }
            // 遇到右括号，检查匹配性
            if(isRightBracket(*json_str)){
                StackElem elem;
                // 栈为空（无对应的左括号），直接判定不合法
                if(stackIsEmpty(temp)){
                    stackDestroy(temp);
                    free(temp);
                    return 0;
                }
                // 查看栈顶左括号，判断是否匹配
                stackPeek(temp,&elem);
                if(isBracketMatch(elem.bracket,*json_str)){
                    stackPop(temp,&elem);  // 匹配成功，弹出栈顶左括号
                }
                else{
                    // 匹配失败，释放资源后返回不合法
                    stackDestroy(temp);
                    free(temp);
                    return 0;
                }
            }
            json_str++;   // 遍历下一个字符
            count++;      // 位置索引自增
        }
    }
    // 步骤4：遍历结束后，栈为空且不处于字符串内，视为合法
    if(stackIsEmpty(temp)&&in_string==0){
        stackDestroy(temp);
        free(temp);
        return 1;
    }
    else{
        // 栈非空（存在未匹配左括号）或仍处于字符串内（引号未闭合），返回不合法
        stackDestroy(temp);
        free(temp);
        return 0;
    }
}

// 主函数：程序入口，负责读取输入、调用检查函数、输出结果
int main(){
    char str[100];  // 定义字符数组存储输入的JSON字符串
    // 输入JSON字符串（以空格/换行结束，最大支持99个字符）
    scanf("%s", str); 
    // 调用基础版括号检查函数
    int result1 = jsonBracketCheckBasic(str);
    // 调用进阶版括号检查函数
    int result2 = jsonBracketCheckAdvanced(str);
    // 输出两个版本的检查结果（1合法，0不合法）
    printf("%d %d", result1,result2);
    return 0;
}