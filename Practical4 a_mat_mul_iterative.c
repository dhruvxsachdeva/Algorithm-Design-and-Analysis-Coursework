#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int mat_mul(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void fill_mat(int n, int Mat[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Mat[i][j] = rand() % 10;
        }
    }
}
int main()
{
    srand(time(NULL));
    int size[] = {100, 200, 300, 400,500,2000};
    int num = sizeof(size) / sizeof(size[0]);
    for (int i = 0; i < num; i++)
    {
        int n = size[i];
        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));

        if (A == NULL || B == NULL || C == NULL)
        {
            printf("Memory allocation failed for size %d\n", n);
            return(1);
        }
        fill_mat(n, A);
        fill_mat(n, B);

        clock_t start = clock();
        mat_mul(n, A, B, C);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Matrix size: %d x %d | Execution time: %f seconds\n", n, n, time_taken);

        free(A);
        free(B);
        free(C);
    }

    return 0;
}