#include <stdio.h>

struct Process {
    int id, arrival, burst, remaining, priority, completion, waiting, turnaround;
};

void priority_preemptive(struct Process processes[], int n) {
    int completed = 0, currentTime = 0, minPriority, selected;
    
    for (int i = 0; i < n; i++)
        processes[i].remaining = processes[i].burst;

    while (completed < n) {
        minPriority = 9999;
        selected = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0 && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                selected = i;
            }
        }

        if (selected == -1) {
            currentTime++;
        } else {
            processes[selected].remaining--;
            currentTime++;

            if (processes[selected].remaining == 0) {
                processes[selected].completion = currentTime;
                processes[selected].turnaround = processes[selected].completion - processes[selected].arrival;
                processes[selected].waiting = processes[selected].turnaround - processes[selected].burst;
                completed++;
            }
        }
    }
}

void printProcessDetails(struct Process processes[], int n) {
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].id, processes[i].arrival, processes[i].burst, processes[i].priority,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
    }

    priority_preemptive(processes, n);
    printProcessDetails(processes, n);

    return 0;
}
