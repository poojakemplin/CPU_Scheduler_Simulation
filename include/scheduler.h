#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 10
#define MAX_QUEUE 100

// Process structure
typedef struct {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // CPU burst time
    int priority;       // Priority (lower number means higher priority)
    int remaining_time; // Remaining burst time (for RR)
    int completion_time;// Time when process completes
    int turnaround_time;// Turnaround time
    int waiting_time;   // Waiting time
    int executed;       // Flag to check if process has been executed (for Priority)
} Process;

// Function declarations
void fcfs(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);
void priority_scheduling(Process processes[], int n);
void print_results(Process processes[], int n, const char* algorithm);

// Helper functions
void sort_by_arrival(Process processes[], int n);
void calculate_times(Process processes[], int n);
void print_gantt_chart(Process processes[], int n, const char* algorithm);

#endif /* SCHEDULER_H */
