//兴趣值排序
#include <stdio.h>

// 函数原型声明(函数的具体实现需要你在文件末尾完成)
// interest：指向存储兴趣值的数组指针
// n：兴趣值数组的元素个数（客户数量）
void sort_interest(int *interest, int n);

int main() {
    int n;  // 存储兴趣值数组的长度（客户数量）
    scanf("%d", &n);  // 输入客户数量/兴趣值个数
    int interest[100];  // 定义数组存储所有客户的兴趣值，最大支持100个元素
    // 循环读取每个客户的兴趣值，存入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    sort_interest(interest, n);  // 调用排序函数，对兴趣值数组进行排序
    // 循环输出排序后的兴趣值
    for (int i = 0; i < n; i++) {
        // 控制输出格式：第一个元素前无空格，后续元素前加空格
        if (i > 0) {
            printf(" ");
        }
        printf("%d", interest[i]);
    }
    printf("\n");  // 输出完成后换行
    return 0;  // 程序正常结束
}

// 你需要实现的函数：核心逻辑 - 对兴趣值数组进行降序排序（选择排序算法）
void sort_interest(int *interest, int n) {
    // 请在此处编写代码
    // 外层循环：遍历数组的每个位置，确定该位置应存放的最大值
    for(int i=0;i<n;i++){
        int max=interest[i];  // 初始化当前区间的最大值为当前位置的元素
        int count=i;          // 初始化最大值对应的索引为当前位置
        
        // 内层循环：在[i, n-1]区间内寻找最大值及其索引
        for(int j=i;j<n;j++){
            // 如果找到比当前最大值更大的元素，更新最大值和对应索引
            if(interest[j]>max){
                max=interest[j];  // 更新当前区间的最大值
                count=j;          // 更新最大值对应的数组索引
            }
        }
        
        // 交换当前位置i和最大值所在位置count的元素，将最大值放到当前位置
        int temp=interest[i];
        interest[i]=max;
        interest[count]=temp;
    }
}