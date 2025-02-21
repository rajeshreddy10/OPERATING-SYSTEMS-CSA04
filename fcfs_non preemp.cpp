#include <stdio.h>

struct Process {
    int id, arrival, burst, completion, waiting, turnaround;
};

void fcfs_non_preemptive(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival)
            currentTime = processes[i].arrival;
        
        processes[i].completion = currentTime + processes[i].burst;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        currentTime = processes[i].completion;
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
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
    }

    fcfs_non_preemptive(processes, n);
    printProcessDetails(processes, n);
    
    return 0;
}
