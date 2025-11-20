/*
    TOPIC: Non-Preemptive Priority Scheduling (CPU Scheduling)

    WHAT IS PRIORITY SCHEDULING?
    - It's a CPU scheduling algorithm where each process is assigned a priority.
    - The CPU is allocated to the process with the highest priority (here, lower numeric value = higher priority).
    - This implementation is non-preemptive: once a process starts, it runs to completion.

    WHAT DOES THIS PROGRAM DO?
    - Reads n processes with Arrival Time (AT), Burst Time (BT), and Priority (PR).
    - Simulates non-preemptive priority scheduling (chooses the ready process with smallest PR).
    - Computes Completion Time (CT), Turn-Around Time (TAT), Waiting Time (WT).
    - Prints per-process times and average WT and TAT.
*/

#include <iostream>     // For cin, cout
using namespace std;    // Use the standard namespace to avoid prefixing std::

int main()
{
    int n;                                 // Number of processes
    cout << "Enter number of processes : "; // Prompt user
    cin >> n;                              // Read number of processes

    int pid[50], art[50], bt[50], pr[50];  // pid = process id, art = arrival time, bt = burst time, pr = priority
    int ct[50], tat[50], wt[50], done[50] = {0}; // ct = completion time, tat = turnaround, wt = waiting, done = finished flag

    for(int i = 0; i < n; i++){            // Loop to read process data
        pid[i] = i + 1;                    // Assign process ID (P1, P2, ...)
        cout << "P" << pid[i] << " At BT Priority : "; // Prompt for AT, BT, PR
        cin >> art[i] >> bt[i] >> pr[i];   // Read arrival time, burst time, and priority
    }

    int time = 0, completed = 0;           // time = current time, completed = number of finished processes

    while (completed < n) {                // Loop until all processes are completed
        int idx = -1;                      // idx = index of chosen process to run next
        int best = 999;                    // best = best priority found (lower is better); initialize large

        for (int i = 0; i < n; i++) {      // Search among all processes for ready and not-done ones
            if (!done[i] && art[i] <= time) { // Consider only processes that have arrived and not finished
                if (pr[i] < best) {        // If this process has a higher priority (smaller number)
                    best = pr[i];          // Update best priority
                    idx = i;               // Update chosen process index
                }
            }
        }

        if (idx == -1) {                   // If no process is ready at current time
            time++;                        // Advance time (CPU idle)
            continue;                      // Retry finding a process
        }

        time += bt[idx];                    // Execute chosen process non-preemptively: advance time by its burst time
        ct[idx] = time;                     // Completion time for chosen process
        tat[idx] = ct[idx] - art[idx];      // Turn-Around Time = CT - Arrival Time
        wt[idx] = tat[idx] - bt[idx];       // Waiting Time = TAT - Burst Time
        done[idx] = 1;                      // Mark this process as finished
        completed++;                        // Increment finished count
    }

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n"; // Print header for results
    for (int i = 0; i < n; i++) {            // Print per-process values
        cout << "P" << pid[i] << "\t" << art[i] << "\t" << bt[i] << "\t" << pr[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    float total_wt = 0, total_tat = 0;       // Accumulators for averages
    for (int i = 0; i < n; i++) {            // Sum waiting and turnaround times
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "\nAverage Waiting Time     : " << total_wt / n << endl;      // Print average waiting time
    cout << "Average Turn-Around Time : " << total_tat / n << endl;      // Print average TAT

    return 0;                                // Normal program termination
}
