#include <stdio.h>

// 函数原型声明(函数的具体实现需要你在文件末尾完成)
void find_top_k_index(int *interest, int n, int k, int *top_k_index);

int main() {
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    int interest[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    int top_k_index[100];  // 其长度固定为 100，但实际上只需将返回结果写入到其前 k 个元素即可
    find_top_k_index(interest, n, k, top_k_index);
    for (int i = 0; i < k; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", top_k_index[i]);
    }
    printf("\n");
    return 0;
}

// 你需要实现的函数
void find_top_k_index(int *interest, int n, int k, int *top_k_index) {
    int used[n];
    for(int a=0;a<n;a++){
        used[a]=0;
    }
    for(int i=0;i<k;i++){
        int top=0;
        int count=0;
        for(int j=0;j<n;j++){
            if(interest[j]>top&&used[j]==0){
                top=interest[j];
                count=j;
            }
        }
        top_k_index[i]=count;
        used[count]=1;
    }
}