/*
    TOPIC: Preemptive Priority Scheduling (CPU Scheduling - Priority, Preemptive)

    WHAT IS PREEMPTIVE PRIORITY SCHEDULING?
    - Each process has a priority value; lower numeric value = higher priority in this program.
    - The CPU is always assigned to the ready process with the highest priority.
    - Preemptive means a running process can be interrupted if a higher-priority process arrives.

    WHAT DOES THIS PROGRAM DO?
    - Reads n processes with Arrival Time (AT), Burst Time (BT), and Priority (PR).
    - Simulates preemptive priority scheduling using a unit-time simulation loop.
    - Computes Completion Time (CT), Turn-Around Time (TAT), Waiting Time (WT).
    - Prints per-process times and average WT and TAT.
*/

#include <iostream>     // for cin, cout
using namespace std;    // bring std names into global namespace

int main() {
    int n;                                     // number of processes
    cout << "Enter number of processes : ";    // prompt user
    cin >> n;                                  // read number of processes

    int pid[50], art[50], bt[50], pr[50];      // pid: process id, art: arrival times, bt: burst times, pr: priorities
    int ct[50], tat[50], wt[50];               // ct: completion times, tat: turnaround times, wt: waiting times
    int rem[50];                               // rem: remaining burst time for each process

    // Input block: read AT, BT, PR for each process and initialize remaining time
    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;                        // assign process id P1..Pn
        cout << "P" << pid[i] << " AT BT Priority : "; // prompt for AT, BT, PR of process i
        cin >> art[i] >> bt[i] >> pr[i];      // read arrival time, burst time, priority
        rem[i] = bt[i];                       // initially remaining time equals burst time
    }

    int time = 0, completed = 0;              // time: current simulation time, completed: number of finished processes
    float sumwt = 0, sumtat = 0;              // accumulators for average waiting and turnaround times

    // Main simulation loop: run until all processes are completed
    while (completed < n) {

        int idx = -1;                         // index of selected process to run in this time unit
        int bestPriority = 9999;              // bestPriority holds the smallest priority value seen (smaller = better)

        // Find the ready process with the highest priority (smallest pr[]) and rem>0
        for (int i = 0; i < n; i++) {
            if (art[i] <= time && rem[i] > 0) {   // process has arrived and still needs CPU
                if (pr[i] < bestPriority) {      // if this process has higher priority than previous best
                    bestPriority = pr[i];        // update bestPriority
                    idx = i;                     // update index of chosen process
                }
            }
        }

        if (idx == -1) {                       // if no process is ready at this time (CPU idle)
            time++;                            // advance time by 1 unit and continue
            continue;
        }

        // Run selected process for one time unit (preemptive simulation)
        rem[idx]--;                            // decrease remaining burst time by 1
        time++;                                // advance the current time by 1

        // If process completes (remaining becomes 0), calculate its metrics
        if (rem[idx] == 0) {
            ct[idx] = time;                    // completion time is current time
            tat[idx] = ct[idx] - art[idx];     // turnaround time = completion - arrival
            wt[idx] = tat[idx] - bt[idx];      // waiting time = turnaround - burst
            completed++;                       // one more process finished

            sumwt += wt[idx];                  // add to total waiting time accumulator
            sumtat += tat[idx];                // add to total turnaround time accumulator
        }
    }

    // Print table header and results for each process
    cout << "\nPID\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++){
        cout << "P" << pid[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Print average waiting time and average turnaround time
    cout << "\nAverage Waiting Time     : " << sumwt / n << endl;
    cout << "Average Turn-Around Time : " << sumtat / n << endl;

    return 0;                                // successful termination
}
