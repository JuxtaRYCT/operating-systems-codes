#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
};

void calculateTimes(struct Process proc[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    int queue[n];
    int front = 0, rear = 0;
    int inQueue[n];
    
    for (int i = 0; i < n; i++) {
        inQueue[i] = 0;
    }

    queue[rear++] = 0;  // Start with the first process
    inQueue[0] = 1;

    while (completed < n) {
        if (front == rear) {
            // Queue is empty
            break;
        }
        
        int processIndex = queue[front++];
        
        if (processIndex < 0 || processIndex >= n) {
            continue; // Skip invalid process index
        }
        
        if (proc[processIndex].remainingTime > timeQuantum) {
            currentTime += timeQuantum;
            proc[processIndex].remainingTime -= timeQuantum;
        } else {
            currentTime += proc[processIndex].remainingTime;
            proc[processIndex].turnAroundTime = currentTime - proc[processIndex].arrivalTime;
            proc[processIndex].waitingTime = proc[processIndex].turnAroundTime - proc[processIndex].burstTime;
            proc[processIndex].remainingTime = 0;
            completed++;
        }

        // Enqueue processes that have arrived by currentTime and are not yet in queue
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && inQueue[i] == 0) {
                if (rear < n) {  // Prevent array overflow
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
        }

        // Re-enqueue the current process if it's not yet completed
        if (proc[processIndex].remainingTime > 0) {
            if (rear < n) {  // Prevent array overflow
                queue[rear++] = processIndex;
            }
        }
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnAroundTime);
    }
}

int main() {
    int n, timeQuantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d\n", i + 1);
        proc[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].waitingTime = 0;
        proc[i].turnAroundTime = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    calculateTimes(proc, n, timeQuantum);

    printf("\nProcess scheduling based on Round Robin:\n");
    printProcesses(proc, n);

    return 0;
}
