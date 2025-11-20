/*
    TOPIC: Inter-Process Communication (IPC) using SHARED MEMORY in Linux

    WHAT IS SHARED MEMORY?
    - Shared memory is an IPC mechanism that allows multiple processes to access the same region
      of memory. It is the fastest IPC method because processes can read/write the same memory directly.
    - System V shared memory uses keys and identifiers (shmget, shmat, shmdt, shmctl).

    WHAT DOES THIS PROGRAM DO?
    - The parent process creates a shared memory segment and writes a message into it.
    - The child process attaches to the same shared memory segment and reads the message.
    - After use, both processes detach; the parent removes the shared memory segment.
*/

#include <stdio.h>      // For printf()
#include <sys/ipc.h>    // For IPC_CREAT and IPC flags (System V IPC)
#include <sys/shm.h>    // For shmget(), shmat(), shmdt(), shmctl()
#include <string.h>     // For strcpy()
#include <unistd.h>     // For fork(), sleep()

int main() {
    int shmid = shmget(1234, 1024, 0666 | IPC_CREAT); // Create/get a shared memory segment:
                                                      // key = 1234, size = 1024 bytes,
                                                      // permissions = 0666 (read/write for all),
                                                      // IPC_CREAT -> create if it doesn't exist.

    int pid = fork(); // Create a child process. fork() returns:
                      // 0 in child, >0 (child PID) in parent, -1 on error.

    if (pid == 0) {
        // CHILD PROCESS: READ MESSAGE

        char *str = (char*) shmat(shmid, NULL, 0); // Attach the shared memory segment to child's
                                                  // address space. Returns pointer to shared memory.

        printf("Child: Reading from shared memory...\n"); // Informative print
        printf("Message: %s\n", str);                     // Print the string read from shared memory

        shmdt(str); // Detach the shared memory from child process address space.
    }
    else {
        // PARENT PROCESS: WRITE MESSAGE

        sleep(1);  // Small delay to give child time to attach (not strictly required, but helpful)

        char *str = (char*) shmat(shmid, NULL, 0); // Attach the shared memory to parent's address space.

        char msg[] = "Hello from Parent via Shared Memory!"; // Message to write into shared memory
        strcpy(str, msg); // Copy the message into the shared memory region pointed by str

        printf("Parent: Message written.\n"); // Informative print

        shmdt(str); // Detach the shared memory from parent process address space.

        shmctl(shmid, IPC_RMID, NULL); // Mark the shared memory segment to be destroyed (IPC_RMID).
                                       // This removes the segment identifier; memory is freed when
                                       // no process is attached.
    }

    return 0; // Exit program
}

//nano shared_mem.c
//paste code, then Ctrl+O, Enter, Ctrl+X to save & exit
//
//gcc shared_mem.c -o shared_mem
