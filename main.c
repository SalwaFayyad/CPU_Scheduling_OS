
//Salwa Fayyad 1200430 
//Sondos Ashraf 1200905
//Katya Kobari 1201478

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int priority;
    int responseTime;
    int waitingTime;
};
struct SchedulerQueue {
    int currentTime;
    int timeQuantum;
    struct Process* readyQueue;
    int readyQueueSize;
    struct Process* Processes;
    struct Process* copyQueue;
    struct Process* copyQueue2;
    struct Process* copyQueue3;
    struct Process* copyQueue4;
    struct Process* copyQueue5;

    int ProcessesSize;
    int copyQueueSize;
    int copyQueueSize2;
    int copyQueueSize3;
    int copyQueueSize4;
    int copyQueueSize5;


};
double turn [4];
double waiting[4];

void RoundRobin(struct SchedulerQueue* scheduler) {
    int start = 0;
    struct Process temp;
    printf("\nRound Robin Scheduler\n");
    for (int i = 0; i < scheduler->readyQueueSize - 1; i++) {
        for (int j = 0; j < scheduler->readyQueueSize - i - 1; j++) {
            if (scheduler->readyQueue[j].arrivalTime > scheduler->readyQueue[j + 1].arrivalTime) {
                // Swap
                temp = scheduler->readyQueue[j];
                scheduler->readyQueue[j] = scheduler->readyQueue[j + 1];
                scheduler->readyQueue[j + 1] = temp;
            }
        }
    }
    // Run the scheduler
    while (scheduler->readyQueueSize > 0) {
        struct Process currentProcess = scheduler->readyQueue[0];

        if (scheduler->currentTime < currentProcess.arrivalTime) {
            printf("idle from %d to %d\n", scheduler->currentTime, currentProcess.arrivalTime);
            scheduler->currentTime = currentProcess.arrivalTime;
        }

        if (currentProcess.remainingTime >= scheduler->timeQuantum) {
            if(currentProcess.responseTime==-1){
                scheduler->copyQueue[currentProcess.processId - 1].responseTime= scheduler->currentTime;
            }
            currentProcess.remainingTime -= scheduler->timeQuantum;
            start = scheduler->currentTime;
            if(currentProcess.responseTime!=-1){

            }
            scheduler->currentTime += scheduler->timeQuantum;

            int end = scheduler->currentTime;
            printf("Process %d executed from %d to %d\n", currentProcess.processId, start, end);

            if (currentProcess.responseTime == -1) {
                currentProcess.responseTime = start - currentProcess.arrivalTime;
            }

            if (currentProcess.remainingTime == 0) {
                scheduler->copyQueue[currentProcess.processId - 1].completionTime = scheduler->currentTime;
                scheduler->copyQueue[currentProcess.processId - 1].turnaroundTime = scheduler->currentTime - currentProcess.arrivalTime;
            } else {
                scheduler->readyQueue[scheduler->readyQueueSize++] = currentProcess;
            }
        } else {
            start = scheduler->currentTime;
            scheduler->currentTime += currentProcess.remainingTime;

            int end = scheduler->currentTime;
            printf("Process %d executed from %d to %d\n", currentProcess.processId, start, end);

            if (currentProcess.responseTime == -1) {
                currentProcess.responseTime = start - currentProcess.arrivalTime;
            }

            currentProcess.remainingTime = 0;
            scheduler->copyQueue[currentProcess.processId - 1].completionTime = scheduler->currentTime;
            scheduler->copyQueue[currentProcess.processId - 1].turnaroundTime = scheduler->currentTime - currentProcess.arrivalTime;
        }

        // Shift the ready queue
        for (int i = 0; i < scheduler->readyQueueSize - 1; i++) {
            scheduler->readyQueue[i] = scheduler->readyQueue[i + 1];
        }
        scheduler->readyQueueSize--;
    }
    for (int i = 0; i < scheduler->copyQueueSize ; i++) {
        scheduler->copyQueue[i].waitingTime=scheduler->copyQueue[i].completionTime-scheduler->copyQueue[i].arrivalTime-scheduler->copyQueue[i].burstTime;
    }

    // Display completion time, turnaround time, waiting time, and response time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\t Waiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < scheduler->ProcessesSize; i++) {
        int responseTime = scheduler->copyQueue[i].responseTime != -1 ? scheduler->copyQueue[i].responseTime : 0;
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d\t\t %d\t\t %d\n", scheduler->Processes[i].processId, scheduler->Processes[i].arrivalTime,
               scheduler->Processes[i].burstTime, scheduler->Processes[i].priority, scheduler->copyQueue[i].completionTime,
               scheduler->copyQueue[i].waitingTime, scheduler->copyQueue[i].turnaroundTime, responseTime);
    }

    int sum_turnaround = 0;
    int sum_waiting = 0;
    int sum_response = 0;

    for (int i = 0; i < scheduler->copyQueueSize; i++) {
        sum_turnaround += scheduler->copyQueue[i].turnaroundTime;
        sum_waiting += scheduler->copyQueue[i].waitingTime;

        //int responseTime = scheduler->copyQueue[i].responseTime != -1 ? scheduler->copyQueue[i].responseTime : 0;
        scheduler->copyQueue[i].responseTime= scheduler->copyQueue[i].responseTime-scheduler->copyQueue[i].arrivalTime;
        sum_response += scheduler->copyQueue[i].responseTime;
    }

    float avg_turnaround_time = (float)sum_turnaround / scheduler->copyQueueSize;
    turn[0]=avg_turnaround_time;
    float avg_waiting_time = (float)sum_waiting / scheduler->copyQueueSize;
    waiting[0]=avg_waiting_time;
    float avg_response_time = (float)sum_response / scheduler->copyQueueSize;

    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Response Time = %.2f\n", avg_response_time);
    printf("\n******************************************\n");
}



void SJF(struct SchedulerQueue* scheduler) {
    scheduler->currentTime = 0; // Reset the current time to 0
    printf("\nSJF Scheduler\n");
    struct Process temp;

    struct Process temp1;

    // Sort the processes based on burst time using Bubble Sort
    for (int i = 0; i < scheduler->copyQueueSize2 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize2 - i - 1; j++) {
            if (scheduler->copyQueue2[j].burstTime > scheduler->copyQueue2[j + 1].burstTime) {
                // Swap
                temp = scheduler->copyQueue2[j];
                scheduler->copyQueue2[j] = scheduler->copyQueue2[j + 1];
                scheduler->copyQueue2[j + 1] = temp;
            }
        }
    }

    int start = 0; // Start from time 0

    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        struct Process currentProcess = scheduler->copyQueue2[i];
        scheduler->currentTime = start;
        int end = scheduler->currentTime + currentProcess.burstTime;

        // Calculate and print the response time
        printf("Process %d executed for %d units (start at %d end at %d) \n",
               currentProcess.processId, currentProcess.burstTime, start, end);

        scheduler->copyQueue2[i].completionTime = end;
        scheduler->copyQueue2[i].waitingTime = start ;
        scheduler->copyQueue2[i].turnaroundTime = scheduler->copyQueue2[i].waitingTime +scheduler->copyQueue2[i].burstTime;

        start = end;
    }
// Sort the processes based on id using Bubble Sort
    for (int i = 0; i < scheduler->copyQueueSize2 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize2 - i - 1; j++) {
            if (scheduler->copyQueue2[j].processId > scheduler->copyQueue2[j + 1].processId) {
                // Swap
                temp = scheduler->copyQueue2[j];
                scheduler->copyQueue2[j] = scheduler->copyQueue2[j + 1];
                scheduler->copyQueue2[j + 1] = temp;
            }
        }
    }
    // Display completion time, turnaround time, and waiting time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\t Waiting Time\tTurnaround Time   \n");
    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d\t\t %d\t\t  \n", scheduler->copyQueue2[i].processId, scheduler->copyQueue2[i].arrivalTime,
               scheduler->copyQueue2[i].burstTime, scheduler->copyQueue2[i].priority, scheduler->copyQueue2[i].completionTime,
               scheduler->copyQueue2[i].waitingTime, scheduler->copyQueue2[i].turnaroundTime);
    }


    int sum_turnaround_time = 0;
    int sum_waiting_time = 0;

    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        sum_turnaround_time += scheduler->copyQueue2[i].turnaroundTime;
        sum_waiting_time += scheduler->copyQueue2[i].waitingTime;
    }

    float avg_turnaround_time = (float)sum_turnaround_time / scheduler->copyQueueSize2;
    turn[1]=avg_turnaround_time;
    float avg_waiting_time = (float)sum_waiting_time / scheduler->copyQueueSize2;
    waiting[1]=avg_waiting_time;

    printf("Average Turnaround Time = %.2f\n",avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("\n******************************************\n");
}

void Priority(struct SchedulerQueue* scheduler) {
    struct Process *currentProcess;
    int x=0,y=0,z=0;
    printf("\nPriority Scheduler\n");
    struct Process temp;
    // Sort the processes based on arrival time (ascending order)
    for (int i = 0; i < scheduler->copyQueueSize3 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize3 - i - 1; j++) {
            if (scheduler->copyQueue3[j].arrivalTime > scheduler->copyQueue3[j + 1].arrivalTime) {
                // Swap
                temp = scheduler->copyQueue3[j];
                scheduler->copyQueue3[j] = scheduler->copyQueue3[j + 1];
                scheduler->copyQueue3[j + 1] = temp;
            }
        }
    }
    scheduler->currentTime = scheduler->copyQueue3[0].arrivalTime;
    int completedProcesses = 0;

    while (completedProcesses < scheduler->copyQueueSize3) {
        int highestPriority = 9999;
        int highestPriorityIndex = -1;
        // Find the process with the highest priority
        for (int i = 0; i < scheduler->copyQueueSize3; i++) {
            if (scheduler->copyQueue3[i].arrivalTime <= scheduler->currentTime &&
                scheduler->copyQueue3[i].priority < highestPriority && scheduler->copyQueue3[i].remainingTime > 0) {
                highestPriority = scheduler->copyQueue3[i].priority;
                highestPriorityIndex = i;
            }
        }
        if (highestPriorityIndex == -1) {
            scheduler->currentTime++;
            continue;
        }
        currentProcess = &scheduler->copyQueue3[highestPriorityIndex];
        x=scheduler->currentTime;
        y=currentProcess->arrivalTime;
        if(currentProcess->responseTime==-1){
            scheduler->copyQueue3[highestPriorityIndex].responseTime= scheduler->currentTime;
        }
        if(z<x){
            printf("idle from %d to %d\n",z,x);
            scheduler->currentTime=x;
        }
        printf("Process %d executed from %d to ", currentProcess->processId, scheduler->currentTime);

        if (currentProcess->remainingTime > 1) {
            scheduler->currentTime++;
            currentProcess->remainingTime--;
        } else {
            scheduler->currentTime += currentProcess->remainingTime;
            currentProcess->remainingTime = 0;
            completedProcesses++;
            currentProcess->completionTime = scheduler->currentTime;
            currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
            currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
        }

        printf("%d\n", scheduler->currentTime);
        z= scheduler->currentTime;
    }

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\t Waiting Time\tTurnaround Time\t Responce \n");
    for (int i = 0; i < scheduler->ProcessesSize; i++) {
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d\t\t %d\t\t %d \n", scheduler->Processes[i].processId, scheduler->Processes[i].arrivalTime,
               scheduler->Processes[i].burstTime, scheduler->Processes[i].priority,scheduler->copyQueue3[i].completionTime,scheduler->copyQueue3[i].waitingTime,scheduler->copyQueue3[i].turnaroundTime,scheduler->copyQueue3[i].responseTime-scheduler->copyQueue3[i].arrivalTime);
    }

    int sum=0;
    // Calculate Average turnaround time for each process
    for (int i = 0; i < scheduler->copyQueueSize3 ; i++) {
        sum+=scheduler->copyQueue3[i].turnaroundTime;
    }

    printf("Average Turnaround Time = %0.2f\n",(1.0)*sum/scheduler->copyQueueSize3);
    turn[2]=(1.0)*sum/scheduler->copyQueueSize3;
    sum=0;
    // Calculate waiting time for each process
    for (int i = 0; i < scheduler->copyQueueSize3 ; i++) {
        sum+=scheduler->copyQueue3[i].turnaroundTime-scheduler->copyQueue3[i].burstTime;
    }
    printf("Average Waiting Time = %0.2f\n",(1.0)*sum/scheduler->copyQueueSize3);
    waiting[2]=(1.0)*sum/scheduler->copyQueueSize3;
    sum=0;
    // Calculate Response time for each process
    for (int i = 0; i < scheduler->copyQueueSize3 ; i++) {
        sum+=scheduler->copyQueue3[i].responseTime-scheduler->copyQueue3[i].arrivalTime;
    }
    printf("Average Responce Time = %0.2f",(1.0)*sum/scheduler->copyQueueSize3);

    printf("\n******************************************\n");
}

//Shortest Remaining Time First
void SRTF(struct SchedulerQueue* scheduler) {
    printf("\nSRTF Scheduler\n");
    // Initialize variables
    int completedProcesses = 0;
    int currentTime = 0;
    int *responseTimes = malloc(scheduler->copyQueueSize4 * sizeof(int));
    memset(responseTimes, -1, scheduler->copyQueueSize4 * sizeof(int)); // Initialize responseTimes array with -1

    while (completedProcesses < scheduler->copyQueueSize4) {
        int start=currentTime;
        int shortestBurstIndex = -1;
        int shortestBurstTime = INT_MAX;

        // Find the process with the shortest remaining burst time among the arrived processes
        for (int i = 0; i < scheduler->copyQueueSize4; i++) {
            if (scheduler->copyQueue4[i].arrivalTime <= currentTime && scheduler->copyQueue4[i].remainingTime > 0) {
                if (scheduler->copyQueue4[i].remainingTime < shortestBurstTime) {
                    shortestBurstIndex = i;
                    shortestBurstTime = scheduler->copyQueue4[i].remainingTime;
                }
            }
        }

        if (shortestBurstIndex == -1) {
            printf(" idle from %d to ",currentTime);
            currentTime++;
            printf(" %d\n",currentTime);

            continue;
        }

        if (responseTimes[shortestBurstIndex] == -1) {
            responseTimes[shortestBurstIndex] = currentTime - scheduler->copyQueue4[shortestBurstIndex].arrivalTime;
        }

        // Execute the process for 1 unit
        scheduler->copyQueue4[shortestBurstIndex].remainingTime--;
        currentTime++;

        printf("Process %d executed from %d to ",scheduler->copyQueue4[shortestBurstIndex].processId,start);

        // Check if the process has completed
        if (scheduler->copyQueue4[shortestBurstIndex].remainingTime == 0) {
            completedProcesses++;
            scheduler->copyQueue4[shortestBurstIndex].completionTime = currentTime;
            scheduler->copyQueue4[shortestBurstIndex].turnaroundTime = scheduler->copyQueue4[shortestBurstIndex].completionTime - scheduler->copyQueue4[shortestBurstIndex].arrivalTime;
            scheduler->copyQueue4[shortestBurstIndex].waitingTime = scheduler->copyQueue4[shortestBurstIndex].turnaroundTime - scheduler->copyQueue4[shortestBurstIndex].burstTime;
        }
        printf(" %d \n",currentTime);
    }


    // Calculate average turnaround time, average waiting time, and average response time
    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;
    double avgResponseTime = 0;

    // Display completion time, turnaround time, waiting time, and response time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < scheduler->copyQueueSize4; i++) {
        avgTurnaroundTime += scheduler->copyQueue4[i].turnaroundTime;
        avgWaitingTime += scheduler->copyQueue4[i].waitingTime;
        avgResponseTime += responseTimes[i];

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", scheduler->Processes[i].processId, scheduler->Processes[i].arrivalTime,
               scheduler->Processes[i].burstTime, scheduler->Processes[i].priority, scheduler->copyQueue4[i].completionTime, scheduler->copyQueue4[i].waitingTime,
               scheduler->copyQueue4[i].turnaroundTime, responseTimes[i]);
    }

    avgTurnaroundTime /= scheduler->copyQueueSize4;
    avgWaitingTime /= scheduler->copyQueueSize4;
    avgResponseTime /= scheduler->copyQueueSize4;

    printf("\nAverage Turnaround Time = %.2f\n", avgTurnaroundTime);
    turn[3] = avgTurnaroundTime;

    printf("Average Waiting Time = %.2f\n", avgWaitingTime);
    waiting[3] = avgWaitingTime;

    printf("Average Response Time = %.2f\n", avgResponseTime);
    //response[3] = avgResponseTime;

    printf("\n******************************************\n");

    // Free dynamically allocated memory
    free(responseTimes);
}

void FCFS(struct SchedulerQueue* scheduler){
    printf("\nFCFS Algorithm \n");
    int currenttime = 0;
    int start = 0, end = 0;
    struct Process temp;
    int sum_response = 0; // Variable to calculate sum of response times

    for (int i = 0; i < scheduler->copyQueueSize5 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize5 - i - 1; j++) {
            if (scheduler->copyQueue5[j].arrivalTime > scheduler->copyQueue5[j + 1].arrivalTime) {
                // Swap
                temp = scheduler->copyQueue5[j];
                scheduler->copyQueue5[j] = scheduler->copyQueue5[j + 1];
                scheduler->copyQueue5[j + 1] = temp;
            }
        }
    }



    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        start = currenttime;
        end = currenttime;
        if (scheduler->copyQueue5[i].arrivalTime > currenttime) {
            printf("idle from %d to %d \n", currenttime, scheduler->copyQueue5[i].arrivalTime);
            currenttime = scheduler->copyQueue5[i].arrivalTime;
        }
        if (scheduler->copyQueue5[i].arrivalTime <= currenttime) {
            printf("Process %d executed from %d to %d \n", scheduler->copyQueue5[i].processId, currenttime, scheduler->copyQueue5[i].burstTime + currenttime);
            currenttime += scheduler->copyQueue5[i].burstTime;
            scheduler->copyQueue5[i].completionTime = currenttime;
            scheduler->copyQueue5[i].turnaroundTime = currenttime - scheduler->copyQueue5[i].arrivalTime;
            scheduler->copyQueue5[i].waitingTime = scheduler->copyQueue5[i].turnaroundTime - scheduler->copyQueue5[i].burstTime;

            scheduler->copyQueue5[i].responseTime= start - scheduler->copyQueue5[i].arrivalTime;
//            printf("Process %d Response Time: %d\n", scheduler->copyQueue5[i].processId, responseTime);
            sum_response += scheduler->copyQueue5[i].responseTime;
        }
    }
// Sort the processes based on id using Bubble Sort
    for (int i = 0; i < scheduler->copyQueueSize5 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize5 - i - 1; j++) {
            if (scheduler->copyQueue5[j].processId > scheduler->copyQueue5[j + 1].processId) {
                // Swap
                temp = scheduler->copyQueue5[j];
                scheduler->copyQueue5[j] = scheduler->copyQueue5[j + 1];
                scheduler->copyQueue5[j + 1] = temp;
            }
        }
    }

    // Display completion time, turnaround time, and waiting time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\t Waiting Time\tTurnaround Time  Response \n");
    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d\t\t %d\t\t %d \n", scheduler->copyQueue5[i].processId, scheduler->copyQueue5[i].arrivalTime,
               scheduler->copyQueue5[i].burstTime, scheduler->copyQueue5[i].priority, scheduler->copyQueue5[i].completionTime,
               scheduler->copyQueue5[i].waitingTime, scheduler->copyQueue5[i].turnaroundTime,scheduler->copyQueue5[i].responseTime);
    }

    int sum_turnaround = 0;
    int sum_waiting = 0;
    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        sum_turnaround += scheduler->copyQueue5[i].turnaroundTime;
        sum_waiting += scheduler->copyQueue5[i].waitingTime;
    }
    float avg_turnaround_time = (float)sum_turnaround / scheduler->copyQueueSize5;
    turn[4]=avg_turnaround_time;
    float avg_waiting_time = (float)sum_waiting / scheduler->copyQueueSize5;
    waiting[4]=avg_waiting_time;
    float avg_response_time = (float)sum_response / scheduler->copyQueueSize5;

    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Response Time = %.2f\n", avg_response_time);
}



int main() {
    struct SchedulerQueue scheduler;
    scheduler.currentTime = 0;
    scheduler.readyQueueSize = 0;
    scheduler.copyQueueSize = 0;
    scheduler.copyQueueSize2 = 0;
    scheduler.copyQueueSize3 = 0;
    scheduler.copyQueueSize4 = 0;
    scheduler.copyQueueSize5 = 0;
    scheduler.ProcessesSize=0;


    // Add processes to the scheduler
    int numP;
    printf("Enter number of Processes: ");
    scanf("%d", &numP);
    while(numP<1){
        printf("Number of Processes must be more than 0!!!\n");
        printf("Enter number of Processes: ");
        scanf("%d", &numP);
    }
    printf("Enter Time Quantum For RoundRobin Algorithm: ");
    scanf("%d", &scheduler.timeQuantum);
    while(scheduler.timeQuantum<1){
        printf("Time Quantum must be more than 0!!!\n");
        printf("Enter Time Quantum: ");
        scanf("%d", &scheduler.timeQuantum);
    }
    printf("*********************\n");
    scheduler.Processes = malloc(sizeof(struct Process) * 10);
    scheduler.readyQueue = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue2 = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue3 = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue4 = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue5 = malloc(sizeof(struct Process) * 10);




    for (int i = 1; i <= numP; i++) {
        int tA, Bt, pri;
        printf("\nEnter Arrival Time for Process[%d]: ", i);
        scanf("%d", &tA);
        printf("Enter Burst Time for Process [%d]: ", i);
        scanf("%d", &Bt);
        while(Bt<1){
            printf("Burst Time must be more than 0!!!\n");
            printf("Enter Burst Time for Process [%d]: ", i);
            scanf("%d", &Bt);
        }
        printf("Enter Priority for Process [%d]: ", i);
        scanf("%d", &pri);

        scheduler.Processes[scheduler.ProcessesSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.readyQueue[scheduler.readyQueueSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue[scheduler.copyQueueSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue2[scheduler.copyQueueSize2++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue3[scheduler.copyQueueSize3++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue4[scheduler.copyQueueSize4++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue5[scheduler.copyQueueSize5++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};

    }

    printf("\n*****************************************************************************\n");


    // Print the process details
    printf("Process ID\tArrival Time\tBurst Time\tPriority\t\n");
    for (int i = 0; i < numP; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\n", scheduler.readyQueue[i].processId, scheduler.readyQueue[i].arrivalTime,
               scheduler.readyQueue[i].burstTime, scheduler.readyQueue[i].priority);
    }
    printf("\n*****************************************************************************\n");


    RoundRobin(&scheduler);
    Priority(&scheduler);
    SJF(&scheduler);
    SRTF(&scheduler);
    FCFS(&scheduler);


    // Find the best Algorithm for Turnaround time :
    int BestTurn=turn[0];
    int algorithm=-1;
    for (int i = 0; i <= 4; i++) {
        if (turn[i] < BestTurn) {
            BestTurn = turn[i];
            algorithm=i;
        }
    }
    printf("*****************************************************************************************\n");
    if(algorithm==0){
        printf("The Best Algorithm For Turnarround Time is RoundRobin with average turnarround time = %0.2f\n",turn[0]);

    }
    if(algorithm==1){
        printf("The Best Algorithm For Turnarround Time is SJF with average turnarround time = %0.2f\n",turn[1]);

    }
    if(algorithm==2){
        printf("The Best Algorithm For Turnarround Time is Priority Preemptive with average turnarround time = %0.2f\n",turn[2]);

    }
    if(algorithm==3){
        printf("The Best Algorithm For Turnarround Time is SRTF with average turnarround time = %0.2f\n",turn[3]);

    }
    if(algorithm==4){
        printf("The Best Algorithm For Turnarround Time is FCFS with average turnarround time = %0.2f\n",turn[4]);

    }
    // Find the best Algorithm for Waiting time :
    int BestWait=waiting[0];
    int algorithm2=-1;

    for (int i = 0; i <= 4; i++) {
        if (waiting[i] < BestWait) {
            BestWait = waiting[i];
            algorithm2=i;
        }
    }
    if(algorithm2==0){
        printf("The Best Algorithm For Waiting Time is RoundRobin with average turnarround time = %0.2f\n",waiting[0]);

    }
    if(algorithm2==1){
        printf("The Best Algorithm For Waiting Time is SJF with average turnarround time = %0.2f\n",waiting[1]);

    }
    if(algorithm2==2){
        printf("The Best Algorithm For Waiting Time is Priority Preemptive with average turnarround time = %0.2f\n",waiting[2]);

    }
    if(algorithm2==3){
        printf("The Best Algorithm For Waiting Time is SRTF with average turnarround time = %0.2f\n",waiting[3]);

    }
    if(algorithm2==4){
        printf("The Best Algorithm For Waiting Time is FCFS with average turnarround time = %0.2f\n",waiting[4]);

    }
    free(scheduler.Processes);
    free(scheduler.readyQueue);
    free(scheduler.copyQueue);
    free(scheduler.copyQueue2);
    free(scheduler.copyQueue3);
    free(scheduler.copyQueue4);
    free(scheduler.copyQueue5);

    return 0;
}
