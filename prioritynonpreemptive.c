#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
};

void sortProcessesByPriority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority || 
               (proc[i].priority == proc[j].priority && proc[i].arrivalTime > proc[j].arrivalTime)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waitingTime = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waitingTime = proc[i - 1].waitingTime + proc[i - 1].burstTime;
    }
}

void calculateTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnAroundTime = proc[i].waitingTime + proc[i].burstTime;
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
    }

    sortProcessesByPriority(proc, n);
    calculateWaitingTime(proc, n);
    calculateTurnAroundTime(proc, n);

    printf("\nProcess scheduling based on non-preemptive priority:\n");
    printProcesses(proc, n);

    return 0;
}
