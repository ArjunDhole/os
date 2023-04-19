#include <stdio.h>

#define MAX_PROCESSES 100

struct process {
    int pid;  // process ID
    int burst_time;  // burst time of the process
    int arrival_time;  // arrival time of the process
    int completion_time;  // completion time of the process
    int turnaround_time;  // turnaround time of the process
    int waiting_time;  // waiting time of the process
};

int main() {
    int n;
    struct process processes[MAX_PROCESSES];

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Get the details of each process from the user
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].arrival_time);

        processes[i].pid = i + 1;
    }

    // Sort the processes by burst time (shortest job first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                struct process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Run the SJF scheduling algorithm
    int current_time = 0;

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        printf("%d--P%d--", current_time, processes[i].pid);

        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        current_time = processes[i].completion_time;
    }

    printf("%d\n", current_time);

    // Print the completion time, turnaround time, and waiting time for each process
    printf("\nProcess\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    return 0;
}
