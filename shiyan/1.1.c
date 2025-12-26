/*
模拟运算器
作者：46
日期：2025.11.18
版本：1.0
*/
#include<stdio.h>
int main()
{
    int istartnum;
    int inum;
    char cyunsuanfu;
    scanf("%d",&istartnum);
    scanf("%c",&cyunsuanfu);
    while(cyunsuanfu!='='){
        scanf("%d",&inum);
        switch(cyunsuanfu){
            case'+':
                istartnum+=inum;
                break;
            case'-':
                istartnum-=inum;
                break;
            case'*':
                istartnum*=inum;
                break;
            case'/':
                if(inum==0){
                    printf("错误，算式中出现零做除数");
                    return 0;
                }
                else{
                    istartnum/=inum;
                    break;
                }
            default:
                printf("错误的运算符:%c",cyunsuanfu);
                return 0;
        }
        scanf("%c",&cyunsuanfu);
    }
    printf("%d\n",istartnum);
    return 0;
}