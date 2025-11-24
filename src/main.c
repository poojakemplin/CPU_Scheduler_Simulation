#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

// Function prototypes
void get_process_details(Process processes[], int n);
void print_results(Process processes[], int n, const char* algorithm);
void print_gantt_chart(Process processes[], int n, const char* algorithm);

int main() {
    int n, quantum;
    Process processes[MAX_PROCESSES];
    
    printf("\n=== CPU Scheduling Simulator ===\n\n");
    
    // Get number of processes
    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Please enter a value between 1 and %d.\n", MAX_PROCESSES);
        return 1;
    }
    
    // Get process details
    get_process_details(processes, n);
    
    // Get time quantum for Round Robin
    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", &quantum);
    
    if (quantum <= 0) {
        printf("Invalid time quantum. Using default value of 2.\n");
        quantum = 2;
    }
    
    // Make copies of the processes for each algorithm
    Process fcfs_processes[MAX_PROCESSES];
    Process rr_processes[MAX_PROCESSES];
    Process priority_processes[MAX_PROCESSES];
    
    for (int i = 0; i < n; i++) {
        fcfs_processes[i] = processes[i];
        rr_processes[i] = processes[i];
        priority_processes[i] = processes[i];
    }
    
    // Execute each scheduling algorithm
    printf("\n=== FCFS Scheduling ===\n");
    fcfs(fcfs_processes, n);
    
    printf("\n\n=== Round Robin Scheduling (Quantum = %d) ===\n", quantum);
    round_robin(rr_processes, n, quantum);
    
    printf("\n\n=== Priority Scheduling (Non-preemptive) ===\n");
    priority_scheduling(priority_processes, n);
    
    return 0;
}

void get_process_details(Process processes[], int n) {
    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        processes[i].pid = i + 1;
        
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        
        printf("  Priority (lower number = higher priority): ");
        scanf("%d", &processes[i].priority);
        
        // Initialize other fields
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].executed = 0;
    }
}

void print_results(Process processes[], int n, const char* algorithm) {
    float avg_tat = 0, avg_wt = 0;
    
    printf("\n%s Results:\n", algorithm);
    printf("+-----+--------------+------------+----------+------------------+-----------------+--------------+\n");
    printf("| PID | Arrival Time | Burst Time | Priority | Completion Time  | Turnaround Time | Waiting Time |\n");
    printf("+-----+--------------+------------+----------+------------------+-----------------+--------------+\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %3d |      %3d     |     %3d    |    %3d   |        %3d       |       %3d       |      %3d     |\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].priority, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
        
        avg_tat += processes[i].turnaround_time;
        avg_wt += processes[i].waiting_time;
    }
    
    printf("+-----+--------------+------------+----------+------------------+-----------------+--------------+\n");
    
    avg_tat /= n;
    avg_wt /= n;
    
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

void print_gantt_chart(Process processes[], int n, const char* algorithm) {
    printf("\nGantt Chart (%s):\n", algorithm);
    printf("+");
    
    // Print top border
    for (int i = 0; i < n; i++) {
        printf("--------+");
    }
    
    printf("\n|");
    
    // Print process IDs
    for (int i = 0; i < n; i++) {
        printf("   P%d   |", processes[i].pid);
    }
    
    printf("\n+");
    
    // Print bottom border
    for (int i = 0; i < n; i++) {
        printf("--------+");
    }
    
    // Print timeline
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("      %2d", processes[i].completion_time);
    }
    
    printf("\n\n");
}
