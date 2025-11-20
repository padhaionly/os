/*
    TOPIC: Banker's Algorithm for Deadlock Avoidance (Operating Systems)

    WHAT IS BANKER'S ALGORITHM?
    - It's a resource-allocation and deadlock-avoidance algorithm.
    - It checks if the system is in a safe state by simulating allocation of resources
      to processes and ensuring there's a sequence in which all processes can complete
      without causing deadlock.

    WHAT DOES THIS PROGRAM DO?
    - Reads number of processes (n) and resources (m).
    - Reads Allocation matrix (current allocation for each process).
    - Reads Max matrix (maximum demand of each process).
    - Reads total instances of each resource.
    - Computes Available = Total - sum(Allocated).
    - Computes Need = Max - Allocation.
    - Runs Banker's algorithm to determine if a safe sequence exists.
    - Prints whether the system is safe and the safe sequence if it exists.
*/

#include <iostream>     // For cin, cout
using namespace std;    // Use the standard namespace to avoid prefixing std::

int main() {                                   // Program starts here
    int n, m;                                   // n = number of processes, m = number of resource types
    cout << "Enter number of processes: ";      // Prompt for number of processes
    cin >> n;                                   // Read number of processes
    cout << "Enter number of resources: ";      // Prompt for number of resources
    cin >> m;                                   // Read number of resources

    int alloc[10][10], maxm[10][10], avail[10], total[10], need[10][10]; // Matrices/arrays for algorithm
    int finish[10] = {0}, safeSeq[10];          // finish[] to track completed processes, safeSeq[] to store sequence

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix (" << n << "x" << m << "):\n"; // Prompt allocation matrix input
    for (int i = 0; i < n; i++)                 // Loop over processes (rows)
        for (int j = 0; j < m; j++)             // Loop over resources (columns)
            cin >> alloc[i][j];                 // Read allocation for process i and resource j

    // Input Max Matrix
    cout << "\nEnter Max Matrix (" << n << "x" << m << "):\n"; // Prompt max matrix input
    for (int i = 0; i < n; i++)                 // Loop over processes (rows)
        for (int j = 0; j < m; j++)             // Loop over resources (columns)
            cin >> maxm[i][j];                  // Read maximum demand for process i and resource j

    // Input Total Resources
    cout << "\nEnter total instances of each resource (" << m << " values): "; // Prompt total resources
    for (int i = 0; i < m; i++)                 // Loop over each resource type
        cin >> total[i];                        // Read total instances for resource i

    // Calculate Available = Total - Allocated
    for (int j = 0; j < m; j++) {               // For each resource type j
        int sum = 0;                            // Sum of allocations for resource j across all processes
        for (int i = 0; i < n; i++)             // Loop over processes to sum allocations
            sum += alloc[i][j];                 // Add allocation of process i for resource j
        avail[j] = total[j] - sum;              // Available instances = total - sum allocated
    }

    // Calculate Need = Max - Allocation
    for (int i = 0; i < n; i++)                 // For each process i
        for (int j = 0; j < m; j++)             // For each resource j
            need[i][j] = maxm[i][j] - alloc[i][j]; // Need is max demand minus currently allocated

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";                  // Print header for Need matrix
    for (int i = 0; i < n; i++) {               // Loop over processes to display need row-wise
        for (int j = 0; j < m; j++)             // Loop over resources in the row
            cout << need[i][j] << " ";          // Print need value followed by space
        cout << endl;                           // Newline after each process row
    }

    // Banker's Algorithm to find Safe Sequence
    int count = 0;                              // Count of processes added to safe sequence
    while (count < n) {                         // Repeat until all processes are finished (or no progress)
        bool found = false;                     // Flag to check if a process could be satisfied in this pass
        for (int i = 0; i < n; i++) {           // Traverse all processes
            if (finish[i] == 0) {               // Consider only unfinished processes
                int j;                          // Iterator for resource types
                for (j = 0; j < m; j++) {       // Check if process i's needs can be satisfied
                    if (need[i][j] > avail[j])  // If need for any resource > available, cannot satisfy
                        break;                  // Break out; process i cannot be executed now
                }
                if (j == m) {                   // If loop completed without break, all needs <= avail
                    for (int k = 0; k < m; k++) // Release allocated resources of process i back to avail
                        avail[k] += alloc[i][k]; // Add allocation of process i to available resources
                    safeSeq[count++] = i;       // Add process i to safe sequence and increment count
                    finish[i] = 1;              // Mark process i as finished
                    found = true;               // Mark that we found at least one process this pass
                }
            }
        }
        if (!found) {                           // If no unfinished process could be satisfied in this pass
            cout << "\nSystem is not in a safe state!"; // No safe sequence exists
            return 0;                           // Exit program indicating unsafe state
        }
    }

    // Display Safe Sequence
    cout << "\nSystem is in a Safe State.\nSafe Sequence: "; // Print safe state message
    for (int i = 0; i < n; i++) {               // Loop over safe sequence array to print processes
        cout << "P" << safeSeq[i];              // Print process id in sequence (e.g., P0)
        if (i != n - 1) cout << " -> ";         // Print arrow between processes except after the last
    }
    cout << endl;                               // Newline after sequence

    return 0;                                   // Successful program termination
}
