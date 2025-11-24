#include <stdio.h>
#include "../include/scheduler.h"

void fcfs(Process processes[], int n) {
    // Sort processes by arrival time
    sort_by_arrival(processes, n);
    
    int current_time = 0;
    
    // Calculate completion time for each process
    for (int i = 0; i < n; i++) {
        // If the process arrives after the current time, update current time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Set completion time
        processes[i].completion_time = current_time + processes[i].burst_time;
        
        // Calculate turnaround and waiting times
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        
        // Update current time
        current_time = processes[i].completion_time;
    }
    
    // Print results
    print_results(processes, n, "FCFS");
    print_gantt_chart(processes, n, "FCFS");
}

// Helper function to sort processes by arrival time
void sort_by_arrival(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                // Swap processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
