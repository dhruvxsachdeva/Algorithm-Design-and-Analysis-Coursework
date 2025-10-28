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

// Function to perform activity selection using the Greedy method
void activitySelection(Activity activities[], int n) {
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

int main() {
    int n, i;

    printf("Enter the number of activities: ");
    scanf("%d", &n);

    Activity activities[n];

    printf("Enter start and finish times of each activity:\n");
    for (i = 0; i < n; i++) {
        printf("Activity %d Start Time: ", i + 1);
        scanf("%d", &activities[i].start);
        printf("Activity %d Finish Time: ", i + 1);
        scanf("%d", &activities[i].finish);
    }

    
    sortActivities(activities, n);

   
    activitySelection(activities, n);

    return 0;
}
