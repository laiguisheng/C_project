#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    printf("请输入两个整数（用空格分隔）：");
    scanf("%d %d", &a, &b); // 输入语句
    printf("两数之和：%d\n", a + b);
    system("pause"); // 暂停黑窗口，便于查看结果
    return 0;
}