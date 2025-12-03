#include<stdio.h>
int main(void)
{
    int aword,bword,cword,dword;
    int nums[]={1,2,3,4};
    for (int i=1; i < 5; i++)
    {    
        aword=nums[i]!=1;
        bword=nums[i]==3;
        cword=nums[i]==4;
        dword=nums[i]!=4;
        if (aword+bword+cword+dword==3)
        printf("")
    }
}