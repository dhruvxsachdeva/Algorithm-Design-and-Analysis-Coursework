#include <stdlib.h>
#include <stdio.h>
#include<time.h>
// i will use inbuilt qsort so here is my definition of compare 
int compare(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

void generateRandomArray(int arr[],int n)
{
        for(int i=0;i<n;i++)
        {
            arr[i]=rand()%10000;
        }
}
int binary(int arr[],int n,int x)// n is len of arr and x is the required element
{
int low =0;
int high=n-1;
while(low<=high)
{
    int mid=low+(high-low)/2;
    if (arr[mid]==x) return mid;
    if (arr[mid]<x) low =mid+1;
    if(arr[mid]>x) high=mid-1;
}
return-1;
}

int main(){
    int n;
    printf("Enter the number of elements:\n");
    scanf("%d",&n);
    int * arr=(int*)malloc(n*sizeof(int));
    if(arr==NULL)
    {
        printf("Memory allocation failed\n");
        return 0;
    }
    srand(time(0));
    generateRandomArray(arr,n);
    qsort(arr, n, sizeof(int), compare);

    clock_t start,end;
    double time;
    int result;
    int reps=100000.0;
    start=clock();
    for (int i = 0; i < reps; i++) 
    {
    result = binary(arr, n, arr[rand() % n]);
    }
    end=clock();
    time=((double)(end-start))/CLOCKS_PER_SEC/reps;
    if(result==-1) printf("Element not found!");
    else printf("Element is at index %d\n",result);
    printf("Time taken is %f nano-seconds\n",time*1e9);
    free(arr);
    return 0;
}