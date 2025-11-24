# CPU Scheduling Simulator

A simple CPU scheduling simulator that demonstrates three different CPU scheduling algorithms:
1. First-Come-First-Serve (FCFS)
2. Round Robin (RR)
3. Priority Scheduling (Non-preemptive)

## Algorithms Overview

### 1. FCFS (First Come First Serve)
- Processes are executed in the order they arrive
- No preemption
- Simple but can lead to long waiting times for short processes

### 2. Round Robin
- Each process gets a small unit of CPU time (time quantum)
- If a process doesn't complete within its time quantum, it's moved to the end of the queue
- Preemptive scheduling algorithm

### 3. Priority Scheduling (Non-preemptive)
- Each process has a priority
- The process with the highest priority is executed first
- If two processes have same priority, FCFS is used
- Non-preemptive: once a process starts, it runs to completion

## Compilation

```bash
make
```

## Usage

```bash
./cpu_scheduler
```

## Example Input

```
Number of processes: 4

Process 1:
Arrival Time: 0
Burst Time: 5
Priority: 2

Process 2:
Arrival Time: 1
Burst Time: 3
Priority: 1

Process 3:
Arrival Time: 2
Burst Time: 8
Priority: 4

Process 4:
Arrival Time: 3
Burst Time: 6
Priority: 3

Time Quantum (for Round Robin): 2
```

## Expected Output

### FCFS Scheduling
```
FCFS Execution Order: P1 -> P2 -> P3 -> P4

Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time
P1\t\t0\t\t5\t\t5\t\t\t5\t\t\t0
P2\t\t1\t\t3\t\t8\t\t\t7\t\t\t4
P3\t\t2\t\t8\t\t16\t\t\t14\t\t\t6
P4\t\t3\t\t6\t\t22\t\t\t19\t\t\t13

Average Turnaround Time: 11.25
Average Waiting Time: 5.75
```

(Similar sections for Round Robin and Priority Scheduling)

## Note
This is a simulation and doesn't use actual system threads or processes. It's designed for educational purposes to understand how different CPU scheduling algorithms work.
