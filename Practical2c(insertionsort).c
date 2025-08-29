#include <stdlib.h>
#include <stdio.h>
#include<time.h>
void insertionsort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
         int key = arr[i];
         int j = i - 1;
    
     while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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
    for(int i=0;i<10;i++)
    {
        generateRandomArray(arr,n);
        insertionsort(arr,n);
    }
    clock_t end=clock();
    double time_taken=((double)(end-start))/CLOCKS_PER_SEC/10.0;//time for one iteration
    printf("%f\n",time_taken);
    free(arr);
    return 0;
}