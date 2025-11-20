/*
    TOPIC: FCFS Scheduling (No Arrival Time Case)

    WHAT IS THIS PROGRAM?
    - This is First-Come, First-Served (FCFS) CPU scheduling.
    - In this version, there is **no arrival time**.
    - All processes are assumed to arrive at time 0.
    - Processes execute in the order they are entered.

    WHAT DOES THIS PROGRAM CALCULATE?
    - Completion Time (CT)
    - Turn-Around Time (TAT = CT)
    - Waiting Time (WT = TAT – BT)
    - Average WT and TAT
*/

#include<iostream>       // For input-output operations
using namespace std;    // Avoid writing std:: repeatedly

int main()
{
    int n;                                  // Number of processes
    cout << "Enter number of processes : ";  // Prompt
    cin >> n;                                // Read number of processes

    int pid[100], bt[100];                  // pid = process IDs, bt = burst times
    int ct[100], tat[100], wt[100] = {0};   // Arrays for completion, turnaround & waiting time

    // Input Burst Times
    cout << "Enter Burst Time for each process : " << endl;
    for(int i = 0; i < n; i++){
        pid[i] = i + 1;                     // Assign process IDs P1, P2, ...
        cout << "P" << pid[i] << " BT: ";   // Prompt for burst time of each process
        cin >> bt[i];                       // Read burst time
    }

    int time = 0;                           // Tracks current time in FCFS execution
    float sumwt = 0;                        // For average waiting time
    float sumtat = 0;                       // For average turnaround time

    // Calculate CT, TAT, WT for each process
    for(int i = 0; i < n; i++){
        ct[i] = time + bt[i];               // Completion time = previous time + burst time
        tat[i] = ct[i];                     // Turn-around time = CT (since AT = 0)
        wt[i] = tat[i] - bt[i];             // Waiting time = TAT - BT

        time = ct[i];                       // Update current time for next process

        sumwt += wt[i];                     // Accumulate waiting times
        sumtat += tat[i];                   // Accumulate turnaround times
    }

    // Display table
    cout << "\nPID\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++){
        cout << "P" << pid[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Display averages
    cout << "\nAverage Waiting Time     : " << sumwt / n << endl;
    cout << "Average Turn-Around Time : " << sumtat / n << endl;

    return 0;                               // Program ends successfully
}
