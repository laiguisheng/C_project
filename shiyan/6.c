//歌唱比赛
#include<stdio.h>
#define N 100  // 定义常量N，作为学生成绩数组的最大长度

// 定义结构体：存储学生的成绩信息
// 结构体别名fenshu，包含一个整型数组score，用于存储单个学生的多门科目成绩
typedef struct student{
    int score[N];
}fenshu;

// 函数声明1：批量处理学生成绩，计算并输出最高有效平均分
// a[]：存储n个学生成绩的结构体数组
// n：学生人数
// m：每个学生的科目数量
void calculate1(fenshu a[],int n,int m);

// 函数声明2：计算单个学生的有效总分（去掉一个最高分和一个最低分后的总分）
// score[]：单个学生的成绩数组
// m：科目数量
// *p：指针，用于存储计算得到的有效总分（通过地址回传结果）
void calculate2(int score[],int m,int *p);

// 主函数：程序入口，负责读取数据、调用处理函数
int main(){
    int n,m;  // n：学生人数，m：每个学生的科目数量
    scanf("%d",&n);  // 输入学生人数
    scanf("%d",&m);  // 输入每个学生的科目数量
    fenshu a[n];     // 定义结构体数组，存储n个学生的成绩信息

    // 初始化结构体数组：读取每个学生的每门科目成绩
    for(int i=0;i<n;i++){
        for(int k=0;k<m;k++){
            scanf("%d",&a[i].score[k]);  // 读取第i个学生第k门科目的成绩
        }
    }

    calculate1(a,n,m);  // 调用批量处理函数，处理并输出结果
    return 0;  // 程序正常结束
}

// 函数实现1：批量处理学生成绩的核心逻辑
void calculate1(fenshu a[],int n,int m){
    int temp[n];  // 定义整型数组，存储每个学生的有效总分（去最高最低后的总分）

    // 遍历每个学生，计算其有效总分
    for(int i=0;i<n;i++){
        // 调用calculate2函数，计算第i个学生的有效总分，结果存入temp[i]
        calculate2(a[i].score,m,&temp[i]);
    }

    // 找出所有学生有效总分中的最大值
    float max=temp[0];  // 初始化最大值为第一个学生的有效总分
    for(int j=1;j<n;j++){
        if(temp[j]>max){
            max=temp[j];  // 更新最大值
        }
    }

    // 计算最高有效平均分：有效总分最大值 / (科目数-2)（去掉了最高和最低分）
    max=max/(m-2);
    printf("%.2f",max);  // 以保留2位小数的格式输出最高有效平均分
}

// 函数实现2：计算单个学生的有效总分（去最高最低分）
void calculate2(int score[],int m,int *p){
    // 第一步：找出该学生成绩中的最高分
    int max=score[0];
    // 第二步：找出该学生成绩中的最低分
    int min=score[0];
    for(int i=1;i<m;i++){
        if(score[i]>max){
            max=score[i];  // 更新最高分
        }
        if(score[i]<min){
            min=score[i];  // 更新最低分
        }
    }

    // 第三步：计算该学生所有科目的总分
    int result=0;
    for(int j=0;j<m;j++){
        result+=score[j];
    }

    // 第四步：计算有效总分（总分 - 最高分 - 最低分），通过指针回传结果
    *p=result-max-min;
}