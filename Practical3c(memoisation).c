#include<time.h>
#include <stdio.h>
# define MAX 1000
int memo[MAX];
int fib(int n)
{
    if(n<=1){
        return n;
    }
    if (memo[n]!=-1) return memo[n];
    memo[n] = fib(n-1) + fib(n-2);
    return memo[n];
}
int main(){
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);
    for (int i = 0; i < MAX; i++)
    {
        memo[i] = -1;
    }
        clock_t start=clock();
        for (int i = 0; i < n; i++)
    {
        printf("%d ", fib(i));
    }
    clock_t end=clock();
    double time_taken=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken for %d values is %f",n,time_taken);
    printf("\n");
    return 0;
}