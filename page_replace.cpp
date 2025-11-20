/*
    TOPIC: Page Replacement Algorithms (Virtual Memory)

    WHAT IS PAGE REPLACEMENT?
    - Page replacement algorithms decide which memory page to evict when a new page
      must be loaded into a limited number of physical frames.
    - Common algorithms: FIFO (First-In-First-Out), LRU (Least Recently Used), Optimal.
    - This program simulates these algorithms on a given reference string and frame count,
      and reports the total page faults for the chosen algorithm.

    WHAT DOES THIS PROGRAM DO?
    - Accepts number of frames, number of references, and the reference string.
    - Implements FIFO, LRU, and Optimal page replacement policies.
    - Prints the total number of page faults for the selected algorithm.
*/

#include <iostream>     // For cout, cin
using namespace std;    // Use the standard namespace to avoid prefixing std::

class VirtualMemory {
public:
    int frames[20];        // physical memory frames (holds pages)
    int fsize;             // number of frames actually used
    int ref[50];           // reference string (sequence of page requests)
    int n;                 // length of reference string
    int pageFaults;        // counter for page faults

    VirtualMemory() {                      // Constructor to initialize frames and faults
        for (int i = 0; i < 20; i++)       // Initialize all frame slots
            frames[i] = -1;               // -1 indicates empty frame
        pageFaults = 0;                   // Initialize page fault count to 0
    }

    void enterInput() {                    // Function to take input from user
        cout << "\nEnter number of frames: "; // Prompt for number of frames
        cin >> fsize;                      // Read frame count

        cout << "Enter number of references: "; // Prompt for length of reference string
        cin >> n;                          // Read length

        cout << "Enter reference string:\n"; // Prompt for actual reference string values
        for (int i = 0; i < n; i++)        // Loop to read n page numbers
            cin >> ref[i];                 // Read each page reference into array
    }

    // Check if page exists in frames; return index if found, -1 if not
    int search(int page) {
        for (int i = 0; i < fsize; i++)    // Check all used frames
            if (frames[i] == page)         // If page matches frame content
                return i;                  // Return frame index
        return -1;                         // Page not present in frames
    }

    // ------------------------------------------
    // FIFO (First-In-First-Out)
    // ------------------------------------------
    void FIFO() {
        cout << "\n--- FIFO Page Replacement ---\n"; // Header
        int index = 0;                      // Points to next frame to replace (circular)
        pageFaults = 0;                    // Reset fault counter

        for (int i = 0; i < n; i++) {      // For each page reference in the string
            int page = ref[i];             // Current requested page

            if (search(page) == -1) {      // If page not present (page fault)
                frames[index] = page;      // Place page into frame at 'index'
                index = (index + 1) % fsize; // Advance index circularly
                pageFaults++;              // Increment page fault count
            }
            // if page is present, nothing to do (no fault)
        }

        cout << "Total Page Faults (FIFO): " << pageFaults << "\n"; // Print result
    }

    // ------------------------------------------
    // LRU (Least Recently Used)
    // ------------------------------------------
    void LRU() {
        cout << "\n--- LRU Page Replacement ---\n"; // Header
        pageFaults = 0;                    // Reset fault count
        int time[20];                      // Array to store last used time (logical clock) per frame
        int t = 0;                         // Logical time counter

        for (int i = 0; i < fsize; i++)    // Initialize time array
            time[i] = -1;                  // -1 indicates frame not yet used

        for (int i = 0; i < n; i++) {      // For each reference
            int page = ref[i];             // Requested page
            int pos = search(page);        // Check if page exists in frames

            if (pos != -1) {               // If page is found (hit)
                time[pos] = t++;           // Update its last-used time to current time then increment time
            }
            else {                         // Page fault: need to replace LRU page
                int lruIndex = 0;          // Assume frame 0 is LRU initially
                for (int j = 1; j < fsize; j++) // Find frame with smallest time value
                    if (time[j] < time[lruIndex]) lruIndex = j; // Update lruIndex if a smaller last-used time found

                frames[lruIndex] = page;  // Replace the LRU frame with the new page
                time[lruIndex] = t++;     // Set its last-used time to current time then increment
                pageFaults++;             // Increment page fault count
            }
        }

        cout << "Total Page Faults (LRU): " << pageFaults << "\n"; // Print result
    }

    // ------------------------------------------
    // Optimal Page Replacement
    // ------------------------------------------
    void Optimal() {
        cout << "\n--- Optimal Page Replacement ---\n"; // Header
        pageFaults = 0;                    // Reset fault count

        for (int i = 0; i < fsize; i++)    // Reinitialize frames to empty
            frames[i] = -1;

        for (int i = 0; i < n; i++) {      // For each reference position i
            int page = ref[i];             // Current requested page

            if (search(page) != -1)        // If page already present, continue (no fault)
                continue;

            int empty = -1;                // Check if any empty frame exists
            for (int j = 0; j < fsize; j++) {
                if (frames[j] == -1) {    // Found empty frame
                    empty = j;            // Store index and break
                    break;
                }
            }

            if (empty != -1) {            // If empty frame found
                frames[empty] = page;     // Place page there
                pageFaults++;             // Count page fault
                continue;                 // Move to next reference
            }

            // No empty frame: choose a frame to replace optimally
            int pos = -1;                 // Position to replace
            int farthest = i;             // Farthest next use index found so far (start at current i)

            for (int j = 0; j < fsize; j++) { // For each frame, search when its page is next used
                int k;
                for (k = i + 1; k < n; k++) { // Look ahead from next reference
                    if (frames[j] == ref[k]) { // If frame's page appears at ref[k]
                        if (k > farthest) {   // If this occurrence is later than previous farthest
                            farthest = k;     // Update farthest
                            pos = j;          // Candidate frame to replace
                        }
                        break;               // Stop searching for this frame since we found its next use
                    }
                }

                if (k == n) {               // If inner loop finished without finding the page in future
                    pos = j;                // This frame's page is not used again; best to replace it
                    break;                  // Break out early since this is optimal choice
                }
            }

            if (pos == -1) pos = 0;        // Fallback (shouldn't usually happen): choose frame 0

            frames[pos] = page;            // Replace chosen frame with requested page
            pageFaults++;                  // Increment fault count
        }

        cout << "Total Page Faults (Optimal): " << pageFaults << "\n"; // Print result
    }
};


int main() {
    VirtualMemory vm;                     // Create VirtualMemory object

    vm.enterInput();                      // Get user input for frames and reference string

    cout << "\nChoose Algorithm:\n1 FIFO\n2 LRU\n3 Optimal\nEnter: "; // Prompt for algorithm choice
    int ch;                               // Variable to store user choice
    cin >> ch;                            // Read choice

    if (ch == 1) vm.FIFO();               // Run FIFO if chosen
    if (ch == 2) vm.LRU();                // Run LRU if chosen
    if (ch == 3) vm.Optimal();            // Run Optimal if chosen

    return 0;                             // Exit program
}
