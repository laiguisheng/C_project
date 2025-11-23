#include<stdio.h>
#include<ctype.h>
int main(void)
{
    char temp;
    int digits=0,letters=0;
    int spaces=0,others=0;
    while((temp=getchar())!='\n'){
        if(temp>='0'&&temp<='9')
        digits++;
        else if(temp>='a'&&temp<='z'||temp>='A'&&temp<='Z')
        letters++;
        else if(temp==' ')
        spaces++;
        else
        others++;
    }
    printf("%d  %d  %d  %d",digits,letters,spaces,others);
    return 0;
}