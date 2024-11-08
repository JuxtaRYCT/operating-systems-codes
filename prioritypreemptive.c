#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    int completed;
};

void calculateTimes(struct Process proc[], int n) {
    int completed = 0, currentTime = 0, minPriority, processIndex;
    while (completed != n) {
        minPriority = INT_MAX;
        processIndex = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].completed == 0 && proc[i].priority < minPriority) {
                minPriority = proc[i].priority;
                processIndex = i;
            }
        }

        if (processIndex == -1) {
            currentTime++;
            continue;
        }

        proc[processIndex].remainingTime--;

        if (proc[processIndex].remainingTime == 0) {
            proc[processIndex].completed = 1;
            completed++;
            proc[processIndex].turnAroundTime = currentTime + 1 - proc[processIndex].arrivalTime;
            proc[processIndex].waitingTime = proc[processIndex].turnAroundTime - proc[processIndex].burstTime;
        }
        currentTime++;
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].priority, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnAroundTime);
    }
}

int main() {
    int n;
    
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
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].completed = 0;
    }

    calculateTimes(proc, n);

    printf("\nProcess scheduling based on preemptive priority:\n");
    printProcesses(proc, n);

    return 0;
}
