#include <stdio.h>
#define MAX_PROCESSES 100

struct process {
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

int main() {
    int num_processes, quantum, i, j, time = 0, num_completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    struct process processes[MAX_PROCESSES];

    // Read input
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Run Round Robin algorithm and create Gantt chart
    printf("\nGantt Chart:\n");
    printf("-----------\n");
    while (num_completed < num_processes) {
        for (i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= quantum) {
                    time += processes[i].remaining_time;
                    printf("| P%d (%d)", i + 1, time);
                    processes[i].remaining_time = 0;
                    num_completed++;
                    processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                } else {
                    time += quantum;
                    printf("| P%d (%d)", i + 1, time);
                    processes[i].remaining_time -= quantum;
                }
            } else {
                printf("|       ");
            }
        }
        printf("|\n");
    }

    // Calculate and print statistics
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < num_processes; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("\nAverage waiting time: %.2f\n", total_waiting_time / num_processes);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / num_processes);

    return 0;
}
