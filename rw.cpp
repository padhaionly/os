/*
    TOPIC: Readers-Writers Synchronization (Simple Writer-Preference Variant)

    WHAT IS THE READERS-WRITERS PROBLEM?
    - It's a classic concurrency problem: multiple readers can read shared data concurrently,
      but writers require exclusive access.
    - The goal is to allow concurrency while preventing data races and ensuring correct results.

    WHAT DOES THIS PROGRAM DO?
    - Spawns a user-specified number of reader threads and writer threads.
    - Readers acquire a lock to increment/decrement a reader count and then read the shared array.
    - Writers wait (via a condition variable) until no readers are active, then update the array.
    - Finally, the program prints the final array contents.

    NOTE:
    - This is a simple demonstration. Real production code should handle more edge cases
      (e.g., starvation, spurious wakeups, robust error handling). The example uses a single
      mutex + condition variable for simplicity.
*/

#include <iostream>             // For cout, cin
#include <thread>               // For std::thread
#include <mutex>                // For std::mutex, std::unique_lock
#include <condition_variable>   // For std::condition_variable
using namespace std;            // Use std namespace for brevity

int dataArr[5] = {1, 2, 3, 4, 5}; // Shared data array initialized with 5 elements
int readCount = 0;                // Number of active readers (initially 0)

mutex mtx;                         // Mutex to protect readCount and synchronize access
condition_variable cv;             // Condition variable to notify writers when readers finish

// READER FUNCTION
void reader(int id) {
    unique_lock<mutex> lock(mtx);  // Acquire lock for modifying/reading shared bookkeeping

    readCount++;                    // A reader enters: increment active readers count

    // Perform reading while still holding lock in this simple demo (could release lock for longer reads)
    cout << "Reader " << id << " reads: ";
    for (int x : dataArr)          // Print all elements in the shared array
        cout << x << " ";
    cout << endl;

    readCount--;                    // Reader leaves: decrement active readers count

    if (readCount == 0)             // If this was the last active reader...
        cv.notify_one();            // ...wake up one waiting writer (if any)

    // unique_lock goes out of scope here and releases the mutex
}

// WRITER FUNCTION
void writer(int id) {
    unique_lock<mutex> lock(mtx);   // Acquire lock to examine reader count and wait if needed

    while (readCount > 0)           // If any readers are active...
        cv.wait(lock);              // ...wait until condition variable signals and mutex is reacquired

    // At this point no readers are active and we hold the mutex (exclusive access)
    cout << "\nWriter " << id << " writing values...\n";
    cout << "Enter 5 numbers: ";

    for (int i = 0; i < 5; i++)     // Read 5 numbers from stdin and update shared array
        cin >> dataArr[i];

    cout << "Writer " << id << " updated the array.\n\n";

    // unique_lock goes out of scope here and releases the mutex, allowing others to proceed
}

int main() {
    int r, w;                       // Number of reader and writer threads to create
    cout << "Enter number of readers: ";
    cin >> r;                       // Read number of readers from user
    cout << "Enter number of writers: ";
    cin >> w;                       // Read number of writers from user

    // Create arrays of threads. Note: using variable-length arrays of std::thread is a simple approach
    // for this demo; in portable C++ prefer vectors: vector<thread> readers(r), writers(w);
    thread readers[r], writers[w];

    // Start all reader threads
    for (int i = 0; i < r; i++)
        readers[i] = thread(reader, i + 1); // Launch reader with id = i+1

    // Start all writer threads
    for (int i = 0; i < w; i++)
        writers[i] = thread(writer, i + 1); // Launch writer with id = i+1

    // Join reader threads (wait for them to finish)
    for (int i = 0; i < r; i++) readers[i].join();

    // Join writer threads (wait for them to finish)
    for (int i = 0; i < w; i++) writers[i].join();

    // FINAL OUTPUT: print the final state of the shared array
    cout << "Final Array: ";
    for (int x : dataArr) cout << x << " ";
    cout << endl;

    return 0; // Program finished
}
