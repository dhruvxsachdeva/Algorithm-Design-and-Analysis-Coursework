#include <stdio.h>

typedef struct {
    int start;
    int finish;
} Activity;

// Function to sort activities by their finish time using bubble sort
void sortActivities(Activity activities[], int n) {
    int i, j;
    Activity temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (activities[i].finish > activities[j].finish) {
                temp = activities[i];
                activities[i] = activities[j];
                activities[j] = temp;
            }
        }
    }
}

void asp(Activity activities[], int n) {
    int i, j;

    printf("Following activities are selected:\n");

    // The first activity always gets selected
    i = 0;
    printf("Activity %d (Start: %d, Finish: %d)\n", i + 1, activities[i].start, activities[i].finish);

    
    for (j = 1; j < n; j++) {
        
        if (activities[j].start >= activities[i].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", j + 1, activities[j].start, activities[j].finish);
            i = j;  
        }
    }
}
void rec_asp(Activity activities[], int i, int n) {
    int m = i + 1;

    // Find the next activity that starts after or at finish of current one
    while (m < n && activities[m].start < activities[i].finish)
        m++;

    if (m < n) {
        printf("Activity %d (Start: %d, Finish: %d)\n", m + 1, activities[m].start, activities[m].finish);
        rec_asp(activities, m, n);
    }
}

int main() {
    int n, i;

    printf("Enter the number of activities: ");
    scanf("%d", &n);

    Activity activities[n + 1]; // +1 for dummy activity

    // Dummy activity
    activities[0].start = 0;
    activities[0].finish = 0;

    printf("Enter start and finish times of each activity:\n");
    for (i = 1; i <= n; i++) {
        printf("Activity %d Start Time: ", i);
        scanf("%d", &activities[i].start);
        printf("Activity %d Finish Time: ", i);
        scanf("%d", &activities[i].finish);

        if (activities[i].start > activities[i].finish) {
            printf("Invalid time entry for Activity %d! Exiting.\n", i);
            return 1;
        }
    }

    sortActivities(activities + 1, n);

    asp(activities + 1, n);

    printf("\nRecursive Activity Selection:\n");
    rec_asp(activities, 0, n + 1);

    return 0;
}


