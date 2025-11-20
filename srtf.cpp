/*
    TOPIC: Shortest Remaining Time First (SRTF) Scheduling - Preemptive SJF

    WHAT IS SRTF?
    - Shortest Remaining Time First (SRTF) is the preemptive version of Shortest Job First.
    - At every time unit, the scheduler picks the process with the smallest remaining CPU burst.
    - If a new process arrives with a smaller remaining time than the running process, preemption occurs.

    WHAT DOES THIS PROGRAM DO?
    - Reads n processes with Arrival Time (AT) and Burst Time (BT).
    - Simulates SRTF with a unit-time loop (preemptive).
    - Computes Completion Time (CT), Turn-Around Time (TAT), and Waiting Time (WT).
    - Prints per-process times and average WT and TAT.
*/

#include <iostream>     // For cin, cout
using namespace std;    // Avoid writing std:: repeatedly

int main()
{
    int n;                                 // number of processes
    cout << "Enter number of processes : "; // prompt user
    cin >> n;                              // read number of processes

    int pid[50], art[50], bt[50], rt[50];  // pid: process id, art: arrival time, bt: burst time, rt: remaining time
    int ct[50], tat[50], wt[50];           // ct: completion time, tat: turnaround time, wt: waiting time

    // Input block: read Arrival Time and Burst Time, initialize remaining time
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;                    // assign process id P1..Pn
        cout << "P" << pid[i] << " AT BT : "; // prompt for AT and BT of process i
        cin >> art[i] >> bt[i];            // read arrival time and burst time
        rt[i] = bt[i];                     // remaining time initially equals burst time
    }

    int completed = 0;                     // number of completed processes
    int time = 0;                          // current time in simulation

    // Main loop: continue until all processes are completed
    while (completed < n) {

        int idx = -1;                      // index of selected process to run at this time unit
        int minrt = 999999;                // holds the minimum remaining time found (initialize very large)

        // Find the process with smallest remaining time which has arrived
        for (int i = 0; i < n; i++) {
            if (art[i] <= time && rt[i] > 0) { // process has arrived and still needs CPU
                if (rt[i] < minrt) {          // if remaining time is smaller than current minimum
                    minrt = rt[i];            // update minimum remaining time
                    idx = i;                  // update selected index
                }
            }
        }

        // If no process has arrived yet or all arrived processes are finished -> CPU idle
        if (idx == -1) {
            time++;                          // advance time by 1 unit and retry
            continue;
        }

        // Run the selected process for 1 time unit (preemptive simulation)
        rt[idx]--;                           // decrement remaining time of selected process
        time++;                              // advance current time by 1

        // If process finished now
        if (rt[idx] == 0) {
            ct[idx] = time;                  // completion time is current time
            tat[idx] = ct[idx] - art[idx];   // turnaround time = completion - arrival
            wt[idx] = tat[idx] - bt[idx];    // waiting time = turnaround - burst
            completed++;                     // increment number of completed processes
        }
    }

    // Print table header and per-process results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << art[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Compute and display average waiting time and average turnaround time
    float total_wt = 0, total_tat = 0;     // accumulators for totals
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];                 // sum waiting times
        total_tat += tat[i];               // sum turnaround times
    }

    cout << "\nAverage Waiting Time     : " << total_wt / n << endl;    // print average WT
    cout << "Average Turn-Around Time : " << total_tat / n << endl;    // print average TAT

    return 0;                              // normal program termination
}
