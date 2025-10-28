#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_matrix(int n, int **M) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % 10;
}

void print_matrix(int n, int **M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}

int **alloc_matrix(int n) {
    int **M = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        M[i] = calloc(n, sizeof(int));   // initialise to 0
    return M;
}

void free_matrix(int n, int **M) {
    for (int i = 0; i < n; i++) 
    free(M[i]);
    free(M);
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
    if (n <= 2) {  // base case: use naive multiplication
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

    int **P = alloc_matrix(k), **Q = alloc_matrix(k), **R = alloc_matrix(k);
    int **S = alloc_matrix(k), **T = alloc_matrix(k), **U = alloc_matrix(k), **V = alloc_matrix(k);
    int **T1 = alloc_matrix(k), **T2 = alloc_matrix(k);

    // split A and B into 4 parts
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

    // P = (A11 + A22) * (B11 + B22)
    add_matrix(k, A11, A22, T1);
    add_matrix(k, B11, B22, T2);
    strassen(k, T1, T2, P);

    // Q = (A21 + A22) * B11
    add_matrix(k, A21, A22, T1);
    strassen(k, T1, B11, Q);

    // R = A11 * (B12 - B22)
    sub_matrix(k, B12, B22, T2);
    strassen(k, A11, T2, R);

    // S = A22 * (B21 - B11)
    sub_matrix(k, B21, B11, T2);
    strassen(k, A22, T2, S);

    // T = (A11 + A12) * B22
    add_matrix(k, A11, A12, T1);
    strassen(k, T1, B22, T);

    // U = (A21 - A11) * (B11 + B12)
    sub_matrix(k, A21, A11, T1);
    add_matrix(k, B11, B12, T2);
    strassen(k, T1, T2, U);

    // V = (A12 - A22) * (B21 + B22)
    sub_matrix(k, A12, A22, T1);
    add_matrix(k, B21, B22, T2);
    strassen(k, T1, T2, V);

    // C11 = P + S - T + V
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = P[i][j] + S[i][j] - T[i][j] + V[i][j];

    // C12 = R + T
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = R[i][j] + T[i][j];

    // C21 = Q + S
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = Q[i][j] + S[i][j];

    // C22 = P - Q + R + U
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C22[i][j] = P[i][j] - Q[i][j] + R[i][j] + U[i][j];

    // join C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]       = C11[i][j];
            C[i][j + k]   = C12[i][j];
            C[i + k][j]   = C21[i][j];
            C[i + k][j+k] = C22[i][j];
        }
    }

    // free memory
    free_matrix(k, A11); free_matrix(k, A12); free_matrix(k, A21); free_matrix(k, A22);
    free_matrix(k, B11); free_matrix(k, B12); free_matrix(k, B21); free_matrix(k, B22);
    free_matrix(k, C11); free_matrix(k, C12); free_matrix(k, C21); free_matrix(k, C22);
    free_matrix(k, P);  free_matrix(k, Q);  free_matrix(k, R);  free_matrix(k, S);
    free_matrix(k, T);  free_matrix(k, U);  free_matrix(k, V);
    free_matrix(k, T1);  free_matrix(k, T2);
}


int main() {
    int size[] = {128, 256, 512, 1024,2048};
    int num = sizeof(size) / sizeof(size[0]);
    for (int i = 0; i < num; i++)
    {
    srand(time(NULL));
    int n= size[i];

    int **A = alloc_matrix(n);
    int **B = alloc_matrix(n);
    int **C = alloc_matrix(n);

    fill_matrix(n, A);
    fill_matrix(n, B);

    clock_t start = clock();
    strassen(n, A, B, C);
    clock_t end = clock();

    double secs = (double)(end - start) / CLOCKS_PER_SEC;
    printf(" %d : %f seconds\n", n, secs);

    // print_matrix(n, C); 

    free_matrix(n, A);
    free_matrix(n, B);
    free_matrix(n, C);
}
    return 0;
}