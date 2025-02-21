#include <stdio.h>
void roundRobinScheduling(int processes[], int n, int burst_time[], int quantum) {
    int waiting_time[n], turnaround_time[n], remaining_time[n];
    int time = 0; 
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }
    int done;
    do {
        done = 1; 
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) { 
                done = 0; 
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i];
                    remaining_time[i] = 0; 
                }
            }
        }
    } while (!done);
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}
int main() {
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n], quantum;
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; 
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    roundRobinScheduling(processes, n, burst_time, quantum);
    return 0;
}