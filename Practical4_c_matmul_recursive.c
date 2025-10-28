#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void mat_mul(int n,int A[n][n],int B[n][n], int C[n][n])
{
   if (n < 2) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int (*A11)[k] = malloc(sizeof(int[k][k]));
    int (*A12)[k] = malloc(sizeof(int[k][k]));
    int (*A21)[k] = malloc(sizeof(int[k][k]));
    int (*A22)[k] = malloc(sizeof(int[k][k]));

    int (*B11)[k] = malloc(sizeof(int[k][k]));
    int (*B12)[k] = malloc(sizeof(int[k][k]));
    int (*B21)[k] = malloc(sizeof(int[k][k]));
    int (*B22)[k] = malloc(sizeof(int[k][k]));

    int (*C11)[k] = malloc(sizeof(int[k][k]));
    int (*C12)[k] = malloc(sizeof(int[k][k]));
    int (*C21)[k] = malloc(sizeof(int[k][k]));
    int (*C22)[k] = malloc(sizeof(int[k][k]));


    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C11[i][j] = 0;
            C12[i][j] = 0;
            C21[i][j] = 0;
            C22[i][j] = 0;
        }

    // Divide A and B into 4 parts
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }


    mat_mul(k, A11, B11, C11);
    mat_mul(k, A12, B21, C11);

    mat_mul(k, A11, B12, C12);
    mat_mul(k, A12, B22, C12);

    mat_mul(k, A21, B11, C21);
    mat_mul(k, A22, B21, C21);

    mat_mul(k, A21, B12, C22);
    mat_mul(k, A22, B22, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
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