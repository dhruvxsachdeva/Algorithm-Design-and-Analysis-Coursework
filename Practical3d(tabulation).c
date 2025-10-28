#include<time.h>
#include <stdio.h>
#define MAX 1000
int dp[MAX];
int computed = 0; // tracks how much is computed

void fib(int n) {
    if (computed == 0) { // first time
        dp[0] = 0;
        dp[1] = 1;
        computed = 2;
    }
    for (int i = computed; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    computed = n + 1;
    for (int i = 0; i <= n; i++)
        printf("%d ", dp[i]);
    printf("\n");
}
int main(){
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);

        clock_t start=clock();
     
    
        fib(n);
    
    clock_t end=clock();
    double time_taken=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken for %d values is %f",n,time_taken);
    printf("\n");
    return 0;
}