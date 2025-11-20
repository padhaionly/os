/*
    TOPIC: Inter-Process Communication using PIPE in Linux

    WHAT IS A PIPE?
    - A pipe is a unidirectional communication channel.
    - It allows one process to send data to another process.
    - It has two ends:
        fd[0] → Read end
        fd[1] → Write end

    WHAT DOES THIS PROGRAM DO?
    - This program demonstrates communication between a child process and a parent process.
    - The child process writes "Hello Parent!" into the pipe.
    - The parent process reads the message from the pipe and prints it on the screen.
*/

#include<stdio.h>      // For printf()
#include<unistd.h>     // For pipe(), fork(), read(), write(), close()
#include<string.h>     // For strlen()

int main()
{
    int fd[2];         // fd[0] = read end, fd[1] = write end of the pipe

    pipe(fd);          // Create a pipe for communication

    int pid = fork();  // Create a new process (child)

    if(pid == 0){      // Child process code
        close(fd[0]);                  // Close unused read end in child
        char msg[] = "Hello Parent!";  // Message to send to parent
        write(fd[1], msg, strlen(msg)+1); // Write message to pipe (+1 for null terminator)
        close(fd[1]);                  // Close write end after sending
    }
    else{              // Parent process code
        close(fd[1]);                  // Close unused write end in parent
        char buffer[50];               // Buffer to store received message
        read(fd[0], buffer, sizeof(buffer)); // Read message from pipe
        printf("Parent received : %s\n", buffer); // Display the received message
        close(fd[0]);                  // Close read end
    }
}
