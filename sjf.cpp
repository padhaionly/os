/*
    TOPIC: Shortest Job First (SJF) Scheduling - Non-preemptive

    WHAT IS SJF (Non-preemptive)?
    - SJF selects the waiting process with the smallest burst time and runs it to completion.
    - Non-preemptive means once a process starts execution it runs till it finishes.
    - Good average waiting time for many workloads, but can starve long jobs.

    WHAT DOES THIS PROGRAM DO?
    - Reads number of processes and for each process reads Arrival Time (AT) and Burst Time (BT).
    - Simulates non-preemptive SJF: at each time, picks the arrived process with smallest BT.
    - Computes Completion Time (CT), Turn-Around Time (TAT) and Waiting Time (WT).
    - Prints per-process times and average WT and TAT.
*/

#include <iostream>     // For cin, cout
using namespace std;    // Avoid writing std:: repeatedly

int main()
{
    int n;                                 // number of processes
    cout << "Enter number of processes : "; // prompt user
    cin >> n;                              // read number of processes

    int pid[50], art[50], bt[50];          // pid: process id, art: arrival time, bt: burst time
    int ct[50], tat[50], wt[50], done[50] = {0}; // ct: completion time, tat: turnaround, wt: waiting, done: finished flag

    // Read input for each process
    for(int i = 0; i < n; i++){
        pid[i] = i + 1;                    // assign process id (P1, P2, ...)
        cout << "P" << pid[i] << " At BT : "; // prompt for arrival time and burst time
        cin >> art[i] >> bt[i];            // read arrival time and burst time
    }

    int time = 0, completed = 0;           // time: current time, completed: count of finished processes

    // Main loop: continue until all processes are completed
    while (completed < n) {
        int idx = -1;                      // index of process selected to run next
        int shortest = INT_MAX;           // hold shortest burst time found (initialize large)

        // Find the arrived, not-yet-done process with smallest burst time
        for (int i = 0; i < n; i++) {
            if (!done[i] && art[i] <= time) {   // process has arrived and not finished
                if (bt[i] < shortest) {        // if this process has smaller burst time
                    shortest = bt[i];          // update shortest
                    idx = i;                   // update selected index
                }
            }
        }

        if (idx == -1) {                    // no process is ready at current time
            time++;                         // CPU idle: advance time
            continue;                       // retry selection
        }

        // Execute selected process non-preemptively
        time += bt[idx];                    // advance current time by its burst time
        ct[idx] = time;                     // completion time for selected process
        tat[idx] = ct[idx] - art[idx];      // turnaround time = completion - arrival
        wt[idx] = tat[idx] - bt[idx];       // waiting time = turnaround - burst
        done[idx] = 1;                      // mark process as finished
        completed++;                        // increment completed count
    }

    // Print results table
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << art[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Compute and print averages
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];                 // accumulate waiting times
        total_tat += tat[i];               // accumulate turnaround times
    }

    cout << "\nAverage Waiting Time     : " << total_wt / n << endl;
    cout << "Average Turn-Around Time : " << total_tat / n << endl;

    return 0;                              // successful termination
}
