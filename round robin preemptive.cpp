#include <stdio.h>

struct Process {
    int id, arrival, burst, remaining, completion, waiting, turnaround;
};

void round_robin(struct Process processes[], int n, int quantum) {
    int completed = 0, currentTime = 0, i = 0;

    for (int i = 0; i < n; i++)
        processes[i].remaining = processes[i].burst;

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining > 0 && processes[i].arrival <= currentTime) {
                if (processes[i].remaining > quantum) {
                    currentTime += quantum;
                    processes[i].remaining -= quantum;
                } else {
                    currentTime += processes[i].remaining;
                    processes[i].completion = currentTime;
                    processes[i].turnaround = processes[i].completion - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                    processes[i].remaining = 0;
                    completed++;
                }
                executed = 1;
            }
        }
        if (!executed) currentTime++;
    }
}

void printProcessDetails(struct Process processes[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    round_robin(processes, n, quantum);
    printProcessDetails(processes, n);
    
    return 0;
}
