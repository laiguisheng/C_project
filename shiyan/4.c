//铁路购票系统
#include<stdio.h>
#include<string.h>

// 函数声明：分配座位
// seat：三维数组，存储所有座位的编号（[排数][列数][编号长度]）
// kongwei：需要分配的座位数量
int distribute(char seat[][5][4], int kongwei);

// 函数声明：生成座位编号
// seat：三维数组，存储所有座位的编号
// i：座位所在的排数（数组索引，实际排数为i+1）
// j：座位所在的列数（数组索引，对应A/B/C/D/F列）
void haoma(char seat[20][5][4], int i, int j);

// 主函数：程序入口
int main(){
    // 定义三维数组存储20排5列的座位编号，每个编号最多3个字符+1个结束符，初始化为0（空字符串）
    char seat[20][5][4]={0};
    int n;  // 定义需要处理的购票请求数量
    scanf("%d",&n);  // 输入购票请求数量
    int deal[n];  // 定义数组存储每个购票请求需要的座位数
    
    // 循环输入每个购票请求的座位数量
    for(int i=0;i<n;i++){
        scanf("%d",&deal[i]);
    }
    
    // 循环处理每个购票请求，为每个请求分配座位
    for(int j=0;j<n;j++){
        distribute(seat,deal[j]);
    }
    
    return 0;  // 程序正常结束
}

// 函数实现：分配座位的核心逻辑
int distribute(char seat[][5][4],int kongwei){
    // 第一步：优先为乘客分配同一排的连续空位（提高乘车体验）
    for(int i=0;i<20;i++){  // 遍历20排座位
        int count=0;  // 记录当前排的空座位数量
        // 遍历当前排的5列座位，统计空座位数
        for(int k=0;k<5;k++){
            // 座位数组首字符为'\0'表示该座位为空
            if(seat[i][k][0]=='\0'){
                count++;
            }
        }
        
        // 如果当前排的空座位数大于等于需要分配的座位数，满足连续分配条件
        if(count>=kongwei){
            // 从当前排的第一个空位开始，分配需要的座位数
            for(int j=5-count;j<(5-count+kongwei);j++){
                haoma(seat,i,j);  // 为该座位生成编号
                printf("%s",seat[i][j]);  // 输出座位编号
                
                // 控制输出格式：最后一个座位后不输出空格，其余座位后输出空格
                if(j!=(4-count+kongwei)){
                    printf(" ");
                }
            }
            printf("\n");  // 一个购票请求的座位分配完成，换行
            return 0;  // 分配成功，结束函数
        }
    }
    
    // 第二步：如果没有满足条件的连续空位，则进行零散分配（按排按列依次分配）
    int located=0;  // 记录已分配的座位数量
    // 遍历所有座位，直到分配完需要的座位数
    for(int i=0;i<20&&located<kongwei;i++){
        for(int j=0;j<5&&located<kongwei;j++){
            // 找到空座位
            if(seat[i][j][0]=='\0'){
                haoma(seat,i,j);  // 生成座位编号
                printf("%s",seat[i][j]);  // 输出座位编号
                located++;  // 已分配座位数加1
                
                // 控制输出格式：未分配完时输出空格，分配完时输出换行
                if(located!=kongwei){
                    printf(" ");
                }
                else{
                    printf("\n");
                }
            }
        }
    }
    return 0;  // 零散分配完成，结束函数
}

// 函数实现：生成座位编号（格式：排数+列字母，如1A、2B、20F等）
void haoma(char seat[20][5][4], int i, int j){
    char row_str[3];  // 存储排数字符串（最多2位，对应1-20排）
    char col_char;    // 存储列对应的字母（A/B/C/D/F）
    
    // 将排数（i是数组索引，实际排数为i+1）转换为字符串
    sprintf(row_str, "%d", i + 1);
    
    // 根据列索引j，映射为对应的列字母（0-A,1-B,2-C,3-D,4-F）
    switch(j) {
        case 0: col_char = 'A'; break;
        case 1: col_char = 'B'; break;
        case 2: col_char = 'C'; break;
        case 3: col_char = 'D'; break;
        default: col_char = 'F'; break;  // j=4时对应F列
    }
    
    // 将排数字符串和列字母拼接，存入座位数组，生成完整座位编号
    sprintf(seat[i][j], "%s%c", row_str, col_char);
}