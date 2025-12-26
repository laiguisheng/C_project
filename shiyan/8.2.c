// 程序功能：找出兴趣值最大的前k个客户的索引（按兴趣值从高到低排序）
#include <stdio.h>

// 函数原型声明(函数的具体实现需要你在文件末尾完成)
// interest：存储客户兴趣值的数组指针
// n：客户总数（兴趣值数组的长度）
// k：需要找出的兴趣值最高的客户数量
// top_k_index：用于存储前k个高兴趣值客户索引的数组指针
void find_top_k_index(int *interest, int n, int k, int *top_k_index);

int main() {
    int n;  // 存储客户总数
    scanf("%d", &n);  // 输入客户总数
    int k;  // 存储需要筛选的高兴趣值客户数量
    scanf("%d", &k);  // 输入需要找出的前k个客户数量
    int interest[100];  // 存储所有客户的兴趣值，最大支持100个客户
    // 循环读取每个客户的兴趣值
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    // 存储前k个高兴趣值客户的索引，数组长度固定为100，仅使用前k个元素
    int top_k_index[100];
    // 调用函数，筛选前k个高兴趣值客户的索引
    find_top_k_index(interest, n, k, top_k_index);
    // 循环输出前k个客户的索引，按兴趣值从高到低的顺序
    for (int i = 0; i < k; i++) {
        // 控制输出格式：第一个元素前无空格，后续元素前加空格
        if (i > 0) {
            printf(" ");
        }
        printf("%d", top_k_index[i]);
    }
    printf("\n");  // 输出完成后换行
    return 0;  // 程序正常结束
}

// 你需要实现的函数：核心逻辑 - 筛选前k个兴趣值最高的客户索引
void find_top_k_index(int *interest, int n, int k, int *top_k_index) {
    // 定义标记数组，标记对应索引的客户是否已被选入前k个（0：未选中，1：已选中）
    int used[n];
    // 初始化标记数组，所有客户初始状态为未选中
    for(int a=0;a<n;a++){
        used[a]=0;
    }
    
    // 循环k次，依次找出第1到第k个兴趣值最高的客户索引
    for(int i=0;i<k;i++){
        int top=0;  // 存储当前轮次找到的最高兴趣值
        int count=0;  // 存储当前轮次最高兴趣值对应的客户索引
        
        // 遍历所有客户，寻找未被选中的兴趣值最高的客户
        for(int j=0;j<n;j++){
            // 条件：当前客户兴趣值大于当前最高值，且未被选中
            if(interest[j]>top&&used[j]==0){
                top=interest[j];  // 更新当前轮次的最高兴趣值
                count=j;  // 更新当前轮次最高兴趣值对应的客户索引
            }
        }
        
        top_k_index[i]=count;  // 将当前找到的客户索引存入结果数组
        used[count]=1;  // 标记该客户为已选中，避免后续重复选取
    }
}