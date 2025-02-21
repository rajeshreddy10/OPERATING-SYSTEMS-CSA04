#include <stdio.h>
struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};
void fcfs_preemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;
    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                selected = i;
                break;
            }
        }
        if (selected == -1) {
            currentTime++;
        } else {
            processes[selected].remaining--;
            if (processes[selected].remaining == 0) {
                processes[selected].completion = currentTime + 1;
                processes[selected].turnaround = processes[selected].completion - processes[selected].arrival;
                processes[selected].waiting = processes[selected].turnaround - processes[selected].burst;
                completed++;
            }
            currentTime++;
        }
    }
}
void printProcessDetails(struct Process processes[], int n) {
    printf("\nProcess Table:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround,
               processes[i].waiting);
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
        processes[i].remaining = processes[i].burst;
    }
    fcfs_preemptive(processes, n);
    printProcessDetails(processes, n);
    return 0;
}