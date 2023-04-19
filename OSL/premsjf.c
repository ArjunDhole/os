#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

struct process {
    int pid;  // process ID
    int burst_time;  // burst time of the process
    int arrival_time;  // arrival time of the process
    int completion_time;  // completion time of the process
    int turnaround_time;  // turnaround time of the process
    int waiting_time;  // waiting time of the process
    bool finished;  // whether the process has finished executing
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
        processes[i].finished = false;
    }

    // Run the Preemptive SJF scheduling algorithm
    int current_time = 0;
    int remaining_processes = n;
    int shortest_job_index = -1;

    printf("\nGantt Chart:\n");

    while (remaining_processes > 0) {
        shortest_job_index = -1;

        for (int i = 0; i < n; i++) {
            if (!processes[i].finished && processes[i].arrival_time <= current_time) {
                if (shortest_job_index == -1 || processes[i].burst_time < processes[shortest_job_index].burst_time) {
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1) {
            current_time++;
            continue;
        }

        printf("%d--P%d--", current_time, processes[shortest_job_index].pid);

        processes[shortest_job_index].burst_time--;
        current_time++;

        if (processes[shortest_job_index].burst_time == 0) {
            processes[shortest_job_index].completion_time = current_time;
            processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            processes[shortest_job_index].finished = true;
            remaining_processes--;
        }
    }

    printf("%d\n", current_time);

    // Print the completion time, turnaround time, and waiting time for each process
    printf("\nProcess\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    return 0;
}
