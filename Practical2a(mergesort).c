#include <stdlib.h>
#include <stdio.h>
# include<time.h>// return clock ticks one clock tick in 1000
void merge(int arr[],int low, int mid, int high)
{
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    int *L=(int*)malloc(n1*sizeof(int));
    int *R=(int*)malloc(n2*sizeof(int));
    for(i=0;i<n1;i++)
    {
        L[i]=arr[low+i];
    }
    for(j=0;j<n2;j++)
    {
        R[j]=arr[mid+1+j];
    }
    i=0;
    j=0;
    k=low;
    while(i<n1 && j<n2)
    {
        if(L[i]<R[j])
        {
            arr[k]=L[i];
            i++;
        }
        else
        {
            arr[k]=R[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        arr[k]=L[i];
        k++;i++;
    }
    while(j<n2)
    {
        arr[k]=R[j];
        k++;j++;
    }
    free(L);
    free(R);
}

void mergesort(int arr[],int low,int high)
{
    if(low<high)
    {
        int mid=low+(high-low)/2; // to not exceed the integer limit of system in case the number is too big
        mergesort(arr,low,mid);
        mergesort(arr,mid+1,high);
        merge(arr,low,mid,high);
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
    generateRandomArray(arr,n);
    clock_t start=clock();
    for(int i=0;i<1000;i++)
    {
        mergesort(arr,0,n-1);
    }
    clock_t end=clock();
    double time_taken=((double)(end-start))/CLOCKS_PER_SEC/1000.0;//time for one iteration
    printf("%f", time_taken);
    free(arr);

    return 0;
}