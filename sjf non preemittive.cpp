#include <stdio.h>

struct Process {
    int pid; 
    int bt;  
    int at;  
    int wt;  
    int tat; 
};

void sortByBurstTime(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].bt > p[j].bt) { 
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt; 
        p[i].tat = p[i].wt + p[i].bt;       
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    sortByBurstTime(p, n);

    calculateTimes(p, n);

    return 0;
}
