#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_PROCESSES 100

struct process {
    int pid;  // process ID
    int burst_time;  // burst time of the process
    int arrival_time;  // arrival time of the process
    int completion_time;  // completion time of the process
    int turnaround_time;  // turnaround time of the process
    int waiting_time;  // waiting time of the process
    int priority;  // priority of the process
    bool finished;  // whether the process has finished executing
};

int findHighestPriorityProcess(struct process processes[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!processes[i].finished && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
            highest_priority = processes[i].priority;
            highest_priority_index = i;
        }
    }

    return highest_priority_index;
}

void runPriorityScheduling(struct process processes[], int n) {
    int current_time = 0;
    int remaining_processes = n;
     float total_waiting_time = 0, total_turnaround_time = 0;
    printf("\nGantt Chart:\n");

    while (remaining_processes > 0) {
        int highest_priority_index = findHighestPriorityProcess(processes, n, current_time);

        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }

        printf("%d--P%d--", current_time, processes[highest_priority_index].pid);

        current_time += processes[highest_priority_index].burst_time;

        processes[highest_priority_index].completion_time = current_time;
        processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
        processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
        processes[highest_priority_index].finished = true;
        remaining_processes--;
         total_waiting_time += processes[highest_priority_index].waiting_time;
        total_turnaround_time += processes[highest_priority_index].turnaround_time;
    }

    printf("%d\n", current_time);

    // Print the completion time, turnaround time, and waiting time for each process
    printf("\nProcess\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
     printf("\nAverage waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

void runFCFS(struct process processes[], int n) {
    int current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    printf("\nGantt Chart:\n");
    printf("-----------\n");
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time += processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("| P%d (%d) ", processes[i].pid, current_time);
    }
    printf("|\n");

    // Calculate and print statistics
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("\nAverage waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int choice, n;
    struct process processes[MAX_PROCESSES];

    // Get the scheduling algorithm choice from the user
    printf("Select the scheduling algorithm:\n");
    printf("1. Priority Scheduling\n");
    printf("2. First-Come, First-Served (FCFS)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Get the details of each process from the user
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].arrival_time);

        processes[i].pid = i + 1;
        processes[i].finished = false;

        if (choice == 1) {
            printf("Enter the priority for process %d: ", i + 1);
            scanf("%d", &processes[i].priority);
        }
    }

    // Run the selected scheduling algorithm
    switch (choice) {
        case 1:
            runPriorityScheduling(processes, n);
            break;
        case 2:
            runFCFS(processes, n);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}