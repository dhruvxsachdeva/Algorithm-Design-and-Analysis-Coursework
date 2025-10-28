#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **alloc_matrix(int n) {
    int **M = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        M[i] = calloc(n, sizeof(int));
    return M;
}

void free_matrix(int n, int **M) {
    for (int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

void fill_matrix(int n, int **M) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % 10;
}

void iterative_mul(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void recursive_mul(int n, int **A, int **B, int **C) {
    if (n == 1) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int **A11 = alloc_matrix(k), **A12 = alloc_matrix(k);
    int **A21 = alloc_matrix(k), **A22 = alloc_matrix(k);
    int **B11 = alloc_matrix(k), **B12 = alloc_matrix(k);
    int **B21 = alloc_matrix(k), **B22 = alloc_matrix(k);
    int **C11 = alloc_matrix(k), **C12 = alloc_matrix(k);
    int **C21 = alloc_matrix(k), **C22 = alloc_matrix(k);
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
    recursive_mul(k, A11, B11, C11);
    recursive_mul(k, A12, B21, C11);
    recursive_mul(k, A11, B12, C12);
    recursive_mul(k, A12, B22, C12);
    recursive_mul(k, A21, B11, C21);
    recursive_mul(k, A22, B21, C21);
    recursive_mul(k, A21, B12, C22);
    recursive_mul(k, A22, B22, C22);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    free_matrix(k, A11); free_matrix(k, A12); free_matrix(k, A21); free_matrix(k, A22);
    free_matrix(k, B11); free_matrix(k, B12); free_matrix(k, B21); free_matrix(k, B22);
    free_matrix(k, C11); free_matrix(k, C12); free_matrix(k, C21); free_matrix(k, C22);
}

void add_matrix(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void naive_mul(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void strassen(int n, int **A, int **B, int **C) {
    if (n <= 2) {
        naive_mul(n, A, B, C);
        return;
    }
    int k = n / 2;
    int **A11 = alloc_matrix(k), **A12 = alloc_matrix(k);
    int **A21 = alloc_matrix(k), **A22 = alloc_matrix(k);
    int **B11 = alloc_matrix(k), **B12 = alloc_matrix(k);
    int **B21 = alloc_matrix(k), **B22 = alloc_matrix(k);
    int **C11 = alloc_matrix(k), **C12 = alloc_matrix(k);
    int **C21 = alloc_matrix(k), **C22 = alloc_matrix(k);
    int **M1 = alloc_matrix(k), **M2 = alloc_matrix(k), **M3 = alloc_matrix(k);
    int **M4 = alloc_matrix(k), **M5 = alloc_matrix(k), **M6 = alloc_matrix(k), **M7 = alloc_matrix(k);
    int **T1 = alloc_matrix(k), **T2 = alloc_matrix(k);
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
    add_matrix(k, A11, A22, T1);
    add_matrix(k, B11, B22, T2);
    strassen(k, T1, T2, M1);
    add_matrix(k, A21, A22, T1);
    strassen(k, T1, B11, M2);
    sub_matrix(k, B12, B22, T2);
    strassen(k, A11, T2, M3);
    sub_matrix(k, B21, B11, T2);
    strassen(k, A22, T2, M4);
    add_matrix(k, A11, A12, T1);
    strassen(k, T1, B22, M5);
    sub_matrix(k, A21, A11, T1);
    add_matrix(k, B11, B12, T2);
    strassen(k, T1, T2, M6);
    sub_matrix(k, A12, A22, T1);
    add_matrix(k, B21, B22, T2);
    strassen(k, T1, T2, M7);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = M3[i][j] + M5[i][j];
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = M2[i][j] + M4[i][j];
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    free_matrix(k, A11); free_matrix(k, A12); free_matrix(k, A21); free_matrix(k, A22);
    free_matrix(k, B11); free_matrix(k, B12); free_matrix(k, B21); free_matrix(k, B22);
    free_matrix(k, C11); free_matrix(k, C12); free_matrix(k, C21); free_matrix(k, C22);
    free_matrix(k, M1); free_matrix(k, M2); free_matrix(k, M3); free_matrix(k, M4);
    free_matrix(k, M5); free_matrix(k, M6); free_matrix(k, M7);
    free_matrix(k, T1); free_matrix(k, T2);
}

int main() {
    int sizes[] = {128, 256, 512, 1024};
    int num = sizeof(sizes) / sizeof(sizes[0]);
    printf("%10s %15s %15s %15s\n", "n", "Iterative", "Recursive", "Strassen");
    for (int i = 0; i < num; i++) {
        int n = sizes[i];
        int **A = alloc_matrix(n);
        int **B = alloc_matrix(n);
        int **C = alloc_matrix(n);
        fill_matrix(n, A);
        fill_matrix(n, B);
        
        clock_t start, end;
        double t_iter, t_rec, t_strassen;
        start = clock();
        iterative_mul(n, A, B, C);
        end = clock();
        t_iter = (double)(end - start) / CLOCKS_PER_SEC; 

        start = clock();
        recursive_mul(n, A, B, C);
        end = clock();
        t_rec = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        strassen(n, A, B, C);
        end = clock();
        t_strassen = (double)(end - start) / CLOCKS_PER_SEC;
        
        printf("%10d %15.6f %15.6f %15.6f\n", n, t_iter, t_rec, t_strassen);
        free_matrix(n, A);
        free_matrix(n, B);
        free_matrix(n, C);
    }
    return 0;
}
