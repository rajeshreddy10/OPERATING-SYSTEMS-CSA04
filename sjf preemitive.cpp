#include <stdio.h>
#include <limits.h> 
struct Process {
    int id;        
    int arrival;    
    int burst;      
    int remaining;  
    int completion; 
    int turnaround; 
    int waiting;   
};
void sjfPreemptive(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int selected;
    int minTime;
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
    }
    while (completed < n) {
        minTime = INT_MAX; 
        selected = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0 &&
                processes[i].remaining < minTime) {
                minTime = processes[i].remaining;
                selected = i;
            }
        }
        if (selected == -1) {
            currentTime++;
        } else {
            processes[selected].remaining--;
            if (processes[selected].remaining == 0) {
                completed++;
                processes[selected].completion = currentTime + 1;
                processes[selected].turnaround = processes[selected].completion - processes[selected].arrival;
                processes[selected].waiting = processes[selected].turnaround - processes[selected].burst;
            }
            currentTime++;
        }
    }
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }
    float totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += processes[i].waiting;
        totalTurnaround += processes[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
    }
    sjfPreemptive(processes, n);
    return 0;
}