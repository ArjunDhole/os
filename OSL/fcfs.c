#include <stdio.h>

#define MAX_PROCESSES 10

struct process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int num_processes, i, j, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    struct process processes[MAX_PROCESSES];

    // Read input
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].id = i + 1;
    }

    // Sort processes by arrival time
    for (i = 0; i < num_processes - 1; i++) {
        for (j = i + 1; j < num_processes; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Run FCFS algorithm and create Gantt chart
    printf("\nGantt Chart:\n");
    printf("-----------\n");
    for (i = 0; i < num_processes; i++) {
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time += processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("| P%d (%d) ", processes[i].id, current_time);
    }
    printf("|\n");

    // Calculate and print statistics
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("\nAverage waiting time: %.2f\n", total_waiting_time / num_processes);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / num_processes);

    return 0;
}
