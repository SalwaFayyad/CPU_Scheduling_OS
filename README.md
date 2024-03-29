# CPU_Scheduling_OS
This project implements various CPU scheduling algorithms in C for the Linux environment for ENCS3390 course in BZU.

### Project Description
- The project allows users to input the number of processes and their arrival time, burst time, and priority (if applicable). It then simulates each scheduling algorithm, calculates metrics such as turnaround time, waiting time, and response time for each process, and finally compares the performance of the algorithms based on these metrics.
- At the end of the simulation, the project identifies the best algorithm for both turnaround time and waiting time based on the calculated averages.
- The project focuses on implementing and comparing different CPU scheduling algorithms to manage processes efficiently in a Linux environment. The implemented algorithms include:

1. **Round Robin (RR):**
   - This algorithm executes processes in a circular manner, where each process gets a fixed time slice (time quantum) to execute before being preempted and moved to the back of the ready queue.

2. **Shortest Job First (SJF):**
   - SJF scheduling selects the process with the smallest burst time next. This algorithm aims to minimize the average waiting time for processes.

3. **Priority Scheduling:**
   - Priority scheduling assigns priority levels to processes, and the process with the highest priority (lowest priority number) is selected for execution first. Preemptive priority scheduling allows higher-priority processes to interrupt lower-priority ones.

4. **Shortest Remaining Time First (SRTF):**
   - SRTF is a preemptive version of SJF, where the scheduler selects the process with the smallest remaining burst time to execute next. If a new process arrives with a smaller burst time than the currently executing process, it preempts the current one.

5. **First-Come, First-Served (FCFS):**
   - FCFS scheduling executes processes based on their arrival time, with the process that arrives first being executed first. It is a non-preemptive algorithm.

#### some photos :)
![image 1](https://github.com/SalwaFayyad/CPU_Scheduling_OS/assets/104863637/e8013e0d-17d3-4f5d-a504-409337cff2c0)
![image 3](https://github.com/SalwaFayyad/CPU_Scheduling_OS/assets/104863637/e3854793-8377-407e-932c-fe00ccb5557c)
![image 4](https://github.com/SalwaFayyad/CPU_Scheduling_OS/assets/104863637/3e28b3df-2ed2-495a-902a-b376169509c5)
![image 5](https://github.com/SalwaFayyad/CPU_Scheduling_OS/assets/104863637/dc825b68-c4eb-4822-8f96-d59eee2002cd)



