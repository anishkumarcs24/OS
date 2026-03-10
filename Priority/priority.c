#include <stdio.h>
#define MAX 20

void priority_np(int n, int at[], int bt[], int pr[])
{
    int wt[MAX] = {0}, tat[MAX], rt[MAX], ct[MAX], done[MAX] = {0};
    int time = 0, count = 0;

    while (count < n)
    {
        int idx = -1, min = 9999;

        for (int i = 0; i < n; i++)
            if (at[i] <= time && !done[i] && pr[i] < min)
            {
                min = pr[i];
                idx = i;
            }

        if (idx != -1)
        {
            rt[idx] = time - at[idx];
            wt[idx] = time - at[idx];

            time += bt[idx];

            ct[idx] = time;           
            tat[idx] = ct[idx] - at[idx];

            done[idx] = 1;
            count++;
        }
        else
            time++;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ct[i], wt[i], tat[i], rt[i]);
}



void priority_p(int n, int at[], int bt[], int pr[])
{
    int rt_bt[MAX], wt[MAX] = {0}, tat[MAX], rt[MAX], ct[MAX];

    for (int i = 0; i < n; i++)
    {
        rt_bt[i] = bt[i];
        rt[i] = -1;
    }

    int time = 0, complete = 0;

    while (complete < n)
    {
        int idx = -1, min = 9999;

        for (int i = 0; i < n; i++)
            if (at[i] <= time && rt_bt[i] > 0 && pr[i] < min)
            {
                min = pr[i];
                idx = i;
            }

        if (idx != -1)
        {
            if (rt[idx] == -1)
                rt[idx] = time - at[idx];

            rt_bt[idx]--;
            time++;

            if (rt_bt[idx] == 0)
            {
                complete++;

                ct[idx] = time;            // Completion Time
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
            }
        }
        else
            time++;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ct[i], wt[i], tat[i], rt[i]);
}



int main()
{
    int n, choice;
    int at[MAX], bt[MAX], pr[MAX];

    printf("Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("AT BT PR for P%d: ", i + 1);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
    }

    printf("\n1. Priority Non-Preemptive");
    printf("\n2. Priority Preemptive");
    printf("\nChoice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        priority_np(n, at, bt, pr);
        break;

    case 2:
        priority_p(n, at, bt, pr);
        break;
    }

    return 0;
}
