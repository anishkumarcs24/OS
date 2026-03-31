#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int execution;
    int period;
    int deadline;
} Task;

void edf(Task t[], int n) {
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");

    int time = 0, completed = 0;
    int remaining[MAX], ct[MAX] = {0}, wt[MAX], tat[MAX];

    for (int i = 0; i < n; i++)
        remaining[i] = t[i].execution;

    while (completed < n) {
        int earliest = 9999, selected = -1;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && t[i].deadline < earliest) {
                earliest = t[i].deadline;
                selected = i;
            }
        }

        if (selected != -1) {
            remaining[selected]--;
            time++;

            if (remaining[selected] == 0) {
                ct[selected] = time;
                tat[selected] = ct[selected];
                wt[selected] = tat[selected] - t[selected].execution;
                completed++;
            }
        } else {
            time++;
        }
    }

    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               t[i].id, t[i].execution, t[i].deadline,
               ct[i], wt[i], tat[i]);
    }
}

void rms(Task t[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");

    int time = 0, completed = 0;
    int remaining[MAX], ct[MAX] = {0}, wt[MAX], tat[MAX];

    for (int i = 0; i < n; i++)
        remaining[i] = t[i].execution;

    while (completed < n) {
        int min_period = 9999, selected = -1;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && t[i].period < min_period) {
                min_period = t[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            remaining[selected]--;
            time++;

            if (remaining[selected] == 0) {
                ct[selected] = time;
                tat[selected] = ct[selected];
                wt[selected] = tat[selected] - t[selected].execution;
                completed++;
            }
        } else {
            time++;
        }
    }

    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               t[i].id, t[i].execution, t[i].period,
               ct[i], wt[i], tat[i]);
    }
}

int main() {
    int n;
    Task t[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);
        t[i].id = i + 1;

        printf("Burst Time: ");
        scanf("%d", &t[i].execution);

        printf("Deadline (for EDF): ");
        scanf("%d", &t[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &t[i].period);
    }

    edf(t, n);
    rms(t, n);

    return 0;
}
