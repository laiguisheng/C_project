//预测赢家
#include<stdio.h>
int maxDiff(int nums[],int left,int right);
int main(){
    int n;
    scanf("%d",&n);
    int nums[n];
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    int score=maxDiff(nums,0,n-1);
    if(score>=0){
        printf("true");
    }
    else{
        printf("false");
    }
    return 0;
}
int maxDiff(int nums[],int left,int right){
    if(left==right){
        return nums[left];
    }
    int choose_left=nums[left]-maxDiff(nums,left+1,right);
    int choose_right=nums[right]-maxDiff(nums,left,right-1);
    if(choose_right>=choose_left){
        return choose_right;
    }
    else{
        return choose_left;
    }
}