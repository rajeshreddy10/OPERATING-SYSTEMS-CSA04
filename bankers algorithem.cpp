#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES] = {3, 3, 2};
int max[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; i++)
        for (int j = 0; j < MAX_RESOURCES; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

int isSafe() {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0}, safeSeq[MAX_PROCESSES], count = 0;
    for (int i = 0; i < MAX_RESOURCES; i++) work[i] = available[i];

    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++)
                    if (need[i][j] > work[j]) break;

                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }

    printf("Safe sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++) printf("%d ", safeSeq[i]);
    printf("\n");
    return 1;
}

int main() {
    calculateNeed();
    if (isSafe()) printf("System is in a safe state.\n");
    else printf("System is in an unsafe state (deadlock may occur).\n");
    return 0;
}
