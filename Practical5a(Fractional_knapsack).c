#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct Item
{
    int itemId;
    int weight;
    int profit;
    float pByw; // profit/weight
    float frac;   // fraction taken
} Item;

int compare(const void *a, const void *b) {
    Item *i1 = (Item *)a;
    Item *i2 = (Item *)b;
    if (i1->pByw < i2->pByw) return 1;   // descending
    else if (i1->pByw > i2->pByw) return -1;
    else return 0;
}


float fractionalknapsack(Item *items, int n, int capacity)
{
    qsort(items, n, sizeof(Item), compare);
    float profit = 0;
    int i = 0;
    int takenWeight = 0;

    for (i = 0; i < n; i++)
    {
        items[i].frac = 0; 
    }

    for (i = 0; i < n; i++)
    {
        if (takenWeight + items[i].weight <= capacity)
        {
            profit += items[i].profit;
            takenWeight += items[i].weight;
            items[i].frac = 1.0; 
        }
        else
        {
            items[i].frac = ((float)capacity - takenWeight) / items[i].weight;
            takenWeight += items[i].frac * items[i].weight;
            profit += items[i].frac * items[i].profit;
            break;
        }
    }

    return profit;
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    int n = atoi(argv[1]);
    int capacity = atoi(argv[2]);

    srand(time(NULL));
    Item *items = malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        items[i].weight = rand() % 100 + 1;
        items[i].profit = rand() % 200 + 10;
        items[i].pByw = (float)items[i].profit / items[i].weight;
    }

    clock_t start = clock();
    fractionalknapsack(items, n, capacity);
    clock_t end = clock();

    double time_us = ((double)(end - start) / CLOCKS_PER_SEC) * 1e6;
    printf("%.2f\n", time_us); // print time in microseconds

    free(items);
    return 0;
}