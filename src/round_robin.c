#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

// Queue implementation for Round Robin
typedef struct {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void round_robin(Process processes[], int n, int quantum) {
    // Make a copy of processes to avoid modifying original
    Process* temp_processes = (Process*)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        temp_processes[i] = processes[i];
        temp_processes[i].remaining_time = processes[i].burst_time;
    }
    
    Queue* queue = createQueue(MAX_QUEUE);
    int current_time = 0, completed = 0, idx;
    int* is_in_queue = (int*)calloc(n, sizeof(int));
    
    // Add first process to queue if it has arrived
    if (temp_processes[0].arrival_time <= current_time) {
        enqueue(queue, 0);
        is_in_queue[0] = 1;
    }
    
    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Execution Order: ");
    
    while (completed != n) {
        if (isEmpty(queue)) {
            // Find next arriving process
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (!is_in_queue[i] && temp_processes[i].arrival_time > current_time) {
                    if (next_arrival == -1 || temp_processes[i].arrival_time < temp_processes[next_arrival].arrival_time) {
                        next_arrival = i;
                    }
                }
            }
            
            if (next_arrival != -1) {
                current_time = temp_processes[next_arrival].arrival_time;
                enqueue(queue, next_arrival);
                is_in_queue[next_arrival] = 1;
            } else {
                current_time++;
                continue;
            }
        }
        
        idx = dequeue(queue);
        is_in_queue[idx] = 0;
        
        printf("P%d ", temp_processes[idx].pid);
        
        if (temp_processes[idx].remaining_time > quantum) {
            current_time += quantum;
            temp_processes[idx].remaining_time -= quantum;
            
            // Add newly arrived processes to queue
            for (int i = 0; i < n; i++) {
                if (!is_in_queue[i] && temp_processes[i].arrival_time <= current_time && 
                    temp_processes[i].remaining_time > 0 && i != idx) {
                    enqueue(queue, i);
                    is_in_queue[i] = 1;
                }
            }
            
            // Add current process back to queue if it still has remaining time
            enqueue(queue, idx);
            is_in_queue[idx] = 1;
        } else {
            current_time += temp_processes[idx].remaining_time;
            temp_processes[idx].remaining_time = 0;
            completed++;
            
            // Update process completion time
            temp_processes[idx].completion_time = current_time;
            temp_processes[idx].turnaround_time = temp_processes[idx].completion_time - temp_processes[idx].arrival_time;
            temp_processes[idx].waiting_time = temp_processes[idx].turnaround_time - temp_processes[idx].burst_time;
            
            // Add newly arrived processes to queue
            for (int i = 0; i < n; i++) {
                if (!is_in_queue[i] && temp_processes[i].arrival_time <= current_time && 
                    temp_processes[i].remaining_time > 0) {
                    enqueue(queue, i);
                    is_in_queue[i] = 1;
                }
            }
        }
    }
    
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
    print_results(processes, n, "Round Robin");
    
    // Free allocated memory
    free(temp_processes);
    free(queue->array);
    free(queue);
    free(is_in_queue);
}
