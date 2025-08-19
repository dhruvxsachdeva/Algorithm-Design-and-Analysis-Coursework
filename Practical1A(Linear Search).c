#include <stdio.h>
#include <stdlib.h>
# include<time.h>
void generateRandomArray(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%100000;//generate random integers
    }
}
int linearsearch(int arr[],int n,int x)
{
   int result=-1;
    for(int i=0;i<n;i++)
    {
        if(arr[i]==x)
        {
            result=i;
            break;
         }
        
    }
    return result;
}
int main(){
    int n,x;
    printf("Enter the number of Elements: ");
    scanf("%d",&n);
    int* arr=(int*)malloc(n*sizeof(int));
    if(arr==NULL)
    {
        printf("Memory alloation failed!\n");
        return 1;
    }
    
    generateRandomArray(arr, n);

    // printf("Enter the element to search: ");
    // scanf("%d", &x);

    clock_t start, end;
    double time_used;

    start = clock();   // Start 
    int result;

    for (int i = 0; i < 1000; i++) {
    result = linearsearch(arr, n, arr[rand() % n]);
}


    end = clock();     // End

    time_used = ((double)(end - start)) / CLOCKS_PER_SEC/1000.0;

    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    printf("Time taken for linear search: %f seconds\n", time_used);
    free(arr);
    return 0;
}