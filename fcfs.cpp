/*
    TOPIC: First-Come, First-Served (FCFS) CPU Scheduling

    WHAT IS FCFS?
    - FCFS is a non-preemptive CPU scheduling algorithm.
    - The process that arrives first gets executed first.
    - Simple to implement but can suffer from the "convoy effect" (long jobs delay short ones).

    WHAT DOES THIS PROGRAM DO?
    - Reads number of processes and for each process reads Arrival Time (AT) and Burst Time (BT).
    - Sorts processes by arrival time.
    - Simulates FCFS to compute Completion Time (CT), Turn-Around Time (TAT), and Waiting Time (WT).
    - Prints per-process times and average WT and TAT.
*/

#include <iostream>     // For cout, cin
using namespace std;    // Use the standard namespace to avoid prefixing std::

int main()
{
    int n;                                 // n = number of processes
    cout << "Enter number of processes: "; // Prompt user for number of processes
    cin >> n;                              // Read number of processes into n

    int pid[100], art[100], bt[100];       // Arrays: pid = process id, art = arrival times, bt = burst times
    int ct[100], tat[100], wt[100];        // Arrays: ct = completion times, tat = turnaround times, wt = waiting times

    cout << "Enter Arrival Time & Burst Time for each process:\n"; // Prompt for process info
    for (int i = 0; i < n; i++) {          // Loop to read AT and BT for each process
        pid[i] = i + 1;                    // Assign process id (P1, P2, ...)
        cout << "P" << pid[i] << " AT: ";  // Prompt for Arrival Time of process i
        cin >> art[i];                     // Read Arrival Time into art[i]
        cout << "P" << pid[i] << " BT: ";  // Prompt for Burst Time of process i
        cin >> bt[i];                      // Read Burst Time into bt[i]
    }

    // Sort processes by Arrival Time (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {      // Outer loop for bubble sort passes
        for (int j = 0; j < n - i - 1; j++) { // Inner loop to compare adjacent pairs
            if (art[j] > art[j + 1]) {     // If arrival time of current > next, swap to order by AT
                swap(art[j], art[j + 1]);  // Swap arrival times
                swap(bt[j], bt[j + 1]);    // Swap corresponding burst times so rows stay aligned
                swap(pid[j], pid[j + 1]);  // Swap process IDs to keep association correct
            }
        }
    }

    int currtime = 0;                      // currtime keeps track of current time on CPU timeline
    for (int i = 0; i < n; i++) {          // Loop through processes in order of arrival
        if (currtime < art[i])             // If CPU is idle until this process arrives
            currtime = art[i];             // Advance current time to the arrival time

        ct[i] = currtime + bt[i];          // Completion time = start time (currtime) + burst time
        tat[i] = ct[i] - art[i];           // Turn-Around Time = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i];            // Waiting Time = Turn-Around Time - Burst Time

        currtime = ct[i];                  // Update current time to this process's completion time
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n"; // Header for table output
    for (int i = 0; i < n; i++) {          // Print computed values for each process
        cout << "P" << pid[i] << "\t" << art[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    float total_wt = 0, total_tat = 0;     // Totals for averages
    for (int i = 0; i < n; i++) {          // Sum up WT and TAT
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "\nAverage Waiting Time     : " << total_wt / n << endl;      // Print average waiting time
    cout << "Average Turn-Around Time : " << total_tat / n << endl;      // Print average TAT

    return 0;                              // Exit program successfully
}
