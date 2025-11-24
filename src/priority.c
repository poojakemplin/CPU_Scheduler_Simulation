#include <stdio.h>
#include <limits.h>
#include "../include/scheduler.h"

void priority_scheduling(Process processes[], int n) {
    // Make a copy of processes to avoid modifying original
    Process* temp_processes = (Process*)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        temp_processes[i] = processes[i];
        temp_processes[i].executed = 0;
    }
    
    int current_time = 0, completed = 0;
    int execution_order[MAX_PROCESSES * 2]; // To store execution order for Gantt chart
    int time_stamps[MAX_PROCESSES * 2];
    int order_index = 0;
    
    printf("\nPriority Scheduling (Non-preemptive):\n");
    printf("Execution Order: ");
    
    while (completed != n) {
        int highest_priority = -1;
        int selected = -1;
        
        // Find the process with highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!temp_processes[i].executed && temp_processes[i].arrival_time <= current_time) {
                if (selected == -1 || temp_processes[i].priority < highest_priority) {
                    highest_priority = temp_processes[i].priority;
                    selected = i;
                }
            }
        }
        
        if (selected == -1) {
            // No process available, move time forward
            current_time++;
            continue;
        }
        
        // Execute the selected process
        printf("P%d ", temp_processes[selected].pid);
        
        // Record execution start time for Gantt chart
        if (order_index == 0 || execution_order[order_index-1] != temp_processes[selected].pid) {
            execution_order[order_index] = temp_processes[selected].pid;
            time_stamps[order_index] = current_time;
            order_index++;
        }
        
        // Update current time and process completion
        current_time += temp_processes[selected].burst_time;
        temp_processes[selected].completion_time = current_time;
        temp_processes[selected].turnaround_time = temp_processes[selected].completion_time - temp_processes[selected].arrival_time;
        temp_processes[selected].waiting_time = temp_processes[selected].turnaround_time - temp_processes[selected].burst_time;
        temp_processes[selected].executed = 1;
        completed++;
    }
    
    // Record completion time for Gantt chart
    time_stamps[order_index] = current_time;
    
    printf("\n\n");
    
    // Copy results back to original array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (processes[i].pid == temp_processes[j].pid) {
                processes[i].completion_time = temp_processes[j].completion_time;
                processes[i].turnaround_time = temp_processes[j].turnaround_time;
                processes[i].waiting_time = temp_processes[j].waiting_time;
                break;
            }
        }
    }
    
    // Print results
    print_results(processes, n, "Priority Scheduling");
    
    // Print Gantt chart
    printf("\nGantt Chart:\n");
    printf("+");
    for (int i = 0; i < order_index; i++) {
        printf("--------+");
    }
    printf("\n|");
    
    for (int i = 0; i < order_index; i++) {
        printf("   P%d   |", execution_order[i]);
    }
    
    printf("\n+");
    for (int i = 0; i < order_index; i++) {
        printf("--------+");
    }
    
    printf("\n%d", time_stamps[0]);
    for (int i = 1; i <= order_index; i++) {
        printf("      %2d", time_stamps[i]);
    }
    printf("\n\n");
    
    free(temp_processes);
}
