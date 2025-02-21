#include <stdio.h>
void bestfit(int mp[], int p[], int m, int n) {
    int j;
    for (int i = 0; i < m; i++) {
        int best_idx = -1;
        for (j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (best_idx == -1 || mp[best_idx] > mp[j]) {
                    best_idx = j;
                }
            }
        }
        if (best_idx != -1) {
            printf("Process %d of size %d fits in partition %d\n", i + 1, p[i], mp[best_idx]);
            mp[best_idx] -= p[i];
        } else {
            printf("Process %d must wait for its process\n", i + 1);
        }
    }
}
void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}
void firstfit(int mp[], int p[], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                printf("Process %d of size %d fits in partition %d\n", i + 1, p[i], mp[j]);
                mp[j] -= p[i];
                break;
            }
        }
    }
}
void worstfit(int mp[], int p[], int m, int n) {
    for (int i = 0; i < m; i++) {
        int worst_idx = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (worst_idx == -1 || mp[worst_idx] < mp[j]) {
                    worst_idx = j;
                }
            }
        }
        if (worst_idx != -1) {
            printf("Process %d of size %d fits in partition %d\n", i + 1, p[i], mp[worst_idx]);
            mp[worst_idx] -= p[i];
        } else {
            printf("Process %d must wait for its process\n", i + 1);
        }
    }
}
int main() {
    int m, n, mp[20], p[20], ch;
    printf("Number of memory partitions: ");
    scanf("%d", &n);
    printf("Number of processes: ");
    scanf("%d", &m);
    printf("Enter the memory partitions:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }
    printf("Enter the process sizes:\n");  
    for (int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }
    printf("1. First fit\n2. Best fit\n3. Worst fit\nEnter your choice: ");
    scanf("%d", &ch);
    switch (ch) {
        case 1:	
            firstfit(mp, p, m, n);
            break;
        case 2:
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    return 0;
}
