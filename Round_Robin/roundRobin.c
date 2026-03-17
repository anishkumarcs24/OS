#include <stdio.h>

#define MAX 20

void roundRobin(int n, int at[], int bt[], int quantum)
{
    int rt_bt[MAX], ct[MAX], wt[MAX], tat[MAX], rt[MAX];
    int queue[100], front = 0, rear = 0;
    int visited[MAX] = {0};

    for(int i = 0; i < n; i++)
    {
        rt_bt[i] = bt[i];
        rt[i] = -1;
    }

    int time = 0, completed = 0;

    int gantt_p[100], gantt_t[100], g = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while(completed < n)
    {
        int i = queue[front++];

        if(rt[i] == -1)
            rt[i] = time - at[i];

        int exec = (rt_bt[i] > quantum) ? quantum : rt_bt[i];

        gantt_p[g] = i;
        gantt_t[g++] = time;

        time += exec;
        rt_bt[i] -= exec;

        for(int j = 0; j < n; j++)
        {
            if(at[j] <= time && visited[j] == 0)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rt_bt[i] > 0)
        {
            queue[rear++] = i;
        }
        else
        {
            ct[i] = time;
            completed++;
        }

        if(front == rear)
        {
            for(int j = 0; j < n; j++)
            {
                if(visited[j] == 0)
                {
                    queue[rear++] = j;
                    visited[j] = 1;
                    time = at[j];
                    break;
                }
            }
        }
    }

    gantt_t[g] = time;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage RT = %.2f\n", total_rt / n);
    printf("\nGantt Chart:\n");

    for(int i = 0; i < g; i++)
        printf("| P%d ", gantt_p[i] + 1);

    printf("|\n");

    for(int i = 0; i <= g; i++)
        printf("%d   ", gantt_t[i]);

    printf("\n");
}

int main()
{
    int n, quantum;
    int at[MAX], bt[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    roundRobin(n, at, bt, quantum);

    return 0;
}
