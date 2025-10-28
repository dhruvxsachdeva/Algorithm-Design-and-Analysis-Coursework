#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int W, int wt[], int val[], int id[], int n) {
    int dp[n+1][W+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

   // printf("\nMaximum profit = %d\n", dp[n][W]);

    //printf("Items chosen :\n");
    int w = W, totalWeight = 0;
    for (int i = n; i > 0 && dp[i][w] > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
     //       printf("ID: %d  Weight: %d  Value: %d\n", id[i-1], wt[i-1], val[i-1]);
            totalWeight += wt[i-1];
            w -= wt[i-1];
        }
    }

   // printf("Total weight of chosen items = %d\n", totalWeight);

    return dp[n][W];
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    int n = atoi(argv[1]);
    int capacity = atoi(argv[2]);

    srand(time(NULL));
    int *wt = malloc(n * sizeof(int));
    int *val = malloc(n * sizeof(int));
    int *id = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        wt[i] = rand() % 100 + 1;
        val[i] = rand() % 200 + 10;
        id[i] = i + 1;
    }

    clock_t start = clock();
    knapSack(capacity, wt, val, id, n);  // correct order
    clock_t end = clock();

    double time_us = ((double)(end - start) / CLOCKS_PER_SEC) * 1e6;
    printf("%.2f\n", time_us); // microseconds

    free(wt);
    free(val);
    free(id);
    return 0;
}
