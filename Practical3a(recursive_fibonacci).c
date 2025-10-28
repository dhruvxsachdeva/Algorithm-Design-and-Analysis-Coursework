#include <stdio.h>
# include<time.h>
int fib(int n)
{
    if(n<=1)
    {
        return n;
    }
    return fib(n-1)+fib(n-2);
}
int main(){
    int n;
    printf("Enter number \n");
    scanf("%d",&n);
    clock_t start=clock();
    for (int i=0;i<n;i++){
    printf("%d ",fib(i));
}
    printf("\n");
    clock_t end=clock();
    double time_taken=((double)(end-start)/CLOCKS_PER_SEC);
    printf("Time taken for %d values is %f", n, time_taken );
    
    return 0;
}