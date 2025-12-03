#include<stdio.h>
#include<ctype.h>
#define N 10
void Transpose(int a[N][N], int n);
void Swap(int *x,int *y);
int main(void){
    int a[N][N]={0};
    int n,k;
    scanf("%d",&n);
    char c;
    int read_count = 0;
    while ((c = getchar()) != EOF && !isdigit(c) && c != '-' && read_count < n*n);
    if (isdigit(c) || c == '-') {
        ungetc(c, stdin); 
    }
    for(int i=0; i<n && read_count < n*n; i++){
        for(int j=0; j<n && read_count < n*n; j++){
            if (scanf("%d", &a[i][j]) == 1) {
                read_count++;
            }
            if (read_count < n*n) {
                while ((c = getchar()) != EOF && !isdigit(c) && c != '-');
                if (isdigit(c) || c == '-') {
                    ungetc(c, stdin);
                }
            }
        }
    }
    Transpose(a,n);
    printf("[");
    for (int i=0; i < n; i++) {
        printf("[");
        for (int j=0; j < n; j++) {
            printf("%d", a[i][j]);
            if(j!=n-1){
                printf(",");
            }
        }
        printf("]");
        if(i!=n-1){
            printf(",");
        }
    }
    printf("]");
    return 0;
}
void Swap(int *x, int *y)
{
int temp;
temp = *x;
*x = *y;
*y = temp;
}
void Transpose(int a[N][N], int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            Swap(&a[i][j],&a[j][i]);
        }
    }
}