
#include<time.h>
#include <stdio.h>
void fib(int n)
{
    int t1=1,t0=0;
    int next;
    for(int i=0;i<=n;i++)
    {
        printf("%d ", t0);
        next=t0+t1;
        t0=t1;
        t1=next;
    }
    printf("\n");
}
int main(){
    int n;
    printf("Enter the number:\n");
    scanf("%d",&n);
    clock_t start=clock();
    fib(n);
    printf("\n");
    clock_t end=clock();
    double time_taken=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken for %d values is %f", n, time_taken);
    
    return 0;
}