//汉诺塔
#include<stdio.h>
#define N 100  // 定义常量N，作为汉诺塔盘子状态数组的最大长度（支持最多100个盘子）

// 函数声明：递归实现汉诺塔移动逻辑，并记录盘子状态
// state[]：存储每个盘子所在的柱子（'A'/'B'/'C'），下标对应盘子编号（0为最小盘，n-1为最大盘）
// n：当前需要移动的盘子数量
// source：源柱子（盘子当前所在的柱子）
// target：目标柱子（盘子需要移动到的柱子）
// other：辅助柱子（用于中转的柱子）
void move(char state[],int n,char source,char target,char other);

// 主函数：程序入口，初始化汉诺塔状态并启动递归移动
int main(){
    char state[N];  // 定义字符数组，存储每个盘子的当前所在柱子
    int n;          // 存储汉诺塔的盘子数量
    scanf("%d",&n); // 输入盘子数量
    
    // 初始化所有盘子的状态：全部位于A柱（源柱子）
    for(int i=0;i<n;i++){
        state[i]='A';// 下标i对应第i+1个盘子，初始化为全为A柱
    }
    
    // 调用递归函数，启动汉诺塔移动（将n个盘子从A柱移动到C柱，以B柱为辅助）
    move(state,n,'A','C','B');
    return 0;  // 程序正常结束
}

// 函数实现：汉诺塔递归移动的核心逻辑
void move(char state[],int n,char source,char target,char other){
    // 递归终止条件：当只有1个盘子时，直接从源柱子移动到目标柱子
    if(n==1){
        // 输出当前移动步骤
        printf("Move disk from %c to %c\n", source, target);
        // 更新最小盘（下标0）的状态为目标柱子
        state[0]=target;
        return; // 终止当前递归分支
    }
    
    // 递归步骤1：将前n-1个盘子从源柱子移动到辅助柱子（以目标柱子为中转）
    move(state,n-1,source,other,target);
    
    // 递归步骤2：将第n个盘子（最大盘，下标n-1）从源柱子移动到目标柱子
    printf("Move disk from %c to %c\n",source,target);
    // 更新最大盘的状态为目标柱子
    state[n-1]=target;
    
    // 递归步骤3：将前n-1个盘子从辅助柱子移动到目标柱子（以源柱子为中转）
    move(state,n-1,other,target,source);
}