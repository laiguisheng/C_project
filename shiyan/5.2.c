//单词统计器
#include<stdio.h>
#include<string.h>
#define N 100  // 定义常量N，作为字符串和单词数组的最大长度

// 函数声明：读取句子并统计不重复的单词数量
// juzi[]：存储输入的句子字符串
int duqu(char juzi[]);

// 主函数：程序入口，负责读取句子、调用统计函数、输出结果
int main(){
    char juzi[N];  // 定义字符数组存储输入的句子
    gets(juzi);    // 读取整行句子（包含空格，直到换行符结束）
    int n=duqu(juzi);  // 调用duqu函数，获取不重复单词的数量
    printf("%d",n);    // 输出统计结果
    return 0;  // 程序正常结束
}

// 函数实现：核心逻辑 - 拆分句子中的单词并统计不重复单词数
int duqu(char juzi[]){
    char words[N][N];  // 二维字符数组，存储拆分出的单词（每行一个单词）
    int count=0;       // 记录不重复单词的数量
    int in_word=0;     // 标记是否正在读取一个单词（0：未在单词中，1：正在读取单词）
    int char_idx=0;    // 记录当前单词的字符索引（用于拼接单词的每个字符）
    int len=strlen(juzi);  // 获取输入句子的长度

    // 遍历句子中的每个字符，拆分单词并去重
    for(int i=0;i<len;i++){
        // 判断当前字符是否为英文字母（大写或小写）
        if((juzi[i]>='A'&&juzi[i]<='Z')||(juzi[i]>='a'&&juzi[i]<='z')){
            in_word=1;  // 标记为正在读取单词
            // 确保单词长度不超过数组限制（预留1位给字符串结束符）
            if(char_idx<N-1){
                words[count][char_idx]=tolower(juzi[i]);  // 转换为小写后存入单词数组，统一大小写便于去重
                char_idx++;  // 当前单词的字符索引后移，准备存储下一个字符
            }
        }
        else{
            // 当前字符不是字母，判断是否处于单词末尾
            if(in_word==1){
                in_word=0;  // 标记为退出单词读取状态
                words[count][char_idx]='\0';  // 为当前单词添加字符串结束符，完成单词拼接
                char_idx=0;  // 重置字符索引，准备存储下一个单词

                int repeat=0;  // 标记当前单词是否重复（0：不重复，1：重复）
                // 遍历已存储的单词（前count个），判断当前单词是否重复
                for(int j=0;j<count;j++){
                    // strcmp比较两个字符串，返回0表示两个单词完全一致（重复）
                    if(strcmp(words[j],words[count])==0){
                        repeat=1;  // 标记为重复单词
                        break;     // 找到重复，无需继续比较，跳出循环
                    }
                }
                // 如果当前单词不重复，不重复单词计数加1
                if(!repeat){
                    count++;
                }
            }
        }
    }

    // 处理句子末尾的单词（句子以字母结尾，未被上面的循环处理的情况）
    if(in_word==1){
        words[count][char_idx]='\0';  // 为末尾单词添加字符串结束符
        in_word=0;  // 标记为退出单词读取状态
        char_idx=0;  // 重置字符索引

        int repeat=0;  // 标记当前单词是否重复
        // 遍历已存储的单词，判断末尾单词是否重复
        for(int j=0;j<count;j++){
            if(strcmp(words[j],words[count])==0){
                repeat=1;
                break;
            }
        }
        // 如果末尾单词不重复，不重复单词计数加1
        if(!repeat){
            count++;
        }
    }

    return count;  // 返回不重复单词的最终数量
}