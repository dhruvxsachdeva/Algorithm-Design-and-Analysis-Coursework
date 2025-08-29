#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[],int low,int high)
{
    int pivot=arr[high];
   int i=low-1;
   for (int j=low;j<high;j++)
   {
        if(arr[j]<pivot)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
   return i+1;
}
void quicksort(int arr[],int low,int high)
{
    if (low<high)
    {
        int p=partition(arr,low,high);
    
    quicksort(arr,low,p-1);
    quicksort(arr,p+1,high);
}
}

void generateRandomArray(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%100000;//generate random integers
    }
}


int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // read n from command-line argument

    int* arr=(int*)malloc(n*sizeof(int));
    if(arr==NULL)
    {
        printf("Memory alloation failed!\n");
        return 1;
    }
    clock_t start=clock();
    for(int i=0;i<1000;i++)
    {
        generateRandomArray(arr,n);
        quicksort(arr,0,n-1);
    }
    clock_t end=clock();
    double time_taken=((double)(end-start))/CLOCKS_PER_SEC/1000.0;//time for one iteration
    printf("%f\n",time_taken);
    free(arr);

    return 0;
}

