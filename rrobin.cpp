/*
    TOPIC: Round Robin (RR) CPU Scheduling

    WHAT IS ROUND ROBIN?
    - Round Robin is a preemptive CPU scheduling algorithm.
    - Each process is given a fixed time slice called Time Quantum (TQ).
    - Processes are executed in a cyclic order; if a process doesn't finish within its quantum,
      it is preempted and placed at the back of the ready list.
    - Good for time-sharing systems; provides fairness but may increase context switches.

    WHAT DOES THIS PROGRAM DO?
    - Reads number of processes and the time quantum.
    - Reads burst times for each process.
    - Simulates Round Robin scheduling to compute Waiting Time (WT) and Turn-Around Time (TAT).
    - Prints per-process Burst Time, Waiting Time and Turn-Around Time.
*/

#include <iostream>     // For input/output (cin, cout)
using namespace std;    // Use the standard namespace to avoid std:: prefix

int main() {
    int n, tq;                          // n = number of processes, tq = time quantum
    cout << "Enter number of processes: "; // Prompt for number of processes
    cin >> n;                           // Read number of processes

    int pid[20], bt[20], rem[20], wt[20], tat[20]; // Arrays:
                                                   // pid - process IDs
                                                   // bt  - burst times
                                                   // rem - remaining burst times
                                                   // wt  - waiting times
                                                   // tat - turn-around times

    cout << "Enter Time Quantum: ";     // Prompt for time quantum
    cin >> tq;                          // Read time quantum

    for (int i = 0; i < n; i++) {       // Loop to get burst time for each process
        cout << "Enter Burst Time of P" << i+1 << ": "; // Prompt for burst time of Pi
        cin >> bt[i];                   // Read burst time into bt[i]
        pid[i] = i + 1;                 // Assign process id (1-based)
        rem[i] = bt[i];                 // Initialize remaining time to full burst time
        wt[i] = 0;                      // Initialize waiting time to 0
    }

    int time = 0;                       // time keeps track of the current global time

    // Round Robin logic: loop until all processes finish
    while (true) {
        bool done = true;               // Assume all processes are done; will set false if any rem > 0

        for (int i = 0; i < n; i++) {   // Iterate over each process in cyclic order
            if (rem[i] > 0) {           // If this process still needs CPU time
                done = false;           // At least one process still pending -> not done

                if (rem[i] > tq) {      // If remaining time is more than one quantum
                    time += tq;         // Execute for one quantum: advance time
                    rem[i] -= tq;       // Decrease remaining time by quantum
                }
                else {                  // If remaining time is <= quantum => process will finish now
                    time += rem[i];     // Advance time by remaining amount
                    wt[i] = time - bt[i]; // Waiting time = total time elapsed - its burst time
                    rem[i] = 0;         // Mark process as finished (no remaining time)
                }
            }
        }

        if (done) break;                // If no process needed CPU in this pass, exit the loop
    }

    // Calculate Turn-Around Time for each process
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];         // TAT = BT + WT
    }

    // Display results in a table
    cout << "\nPID\tBT\tWT\tTAT\n";      // Header: Process ID, Burst Time, Waiting Time, Turn-Around Time
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << "\n"; // Row per process
    }

    return 0;                           // Successful termination
}
