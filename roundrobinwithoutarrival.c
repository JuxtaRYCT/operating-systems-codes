#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
};

void calculateTimes(struct Process proc[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                if (proc[i].remainingTime > timeQuantum) {
                    currentTime += timeQuantum;
                    proc[i].remainingTime -= timeQuantum;
                } else {
                    currentTime += proc[i].remainingTime;
                    proc[i].turnAroundTime = currentTime;
                    proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;
                    proc[i].remainingTime = 0;
                    completed++;
                }
            }
        }
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].waitingTime, proc[i].turnAroundTime);
    }
}

int main() {
    int n, timeQuantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
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
