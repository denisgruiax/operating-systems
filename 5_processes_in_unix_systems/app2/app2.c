/*
Write a program that creates three processes, as follows:
    The first process (parent) reads a string of characters from a file named data.txt, up to the end of the file, and sends them through a pipe to the first child
    The first child receives the characters from the parent and selects the lowercase letters from them, which it sends through a pipe to the second child.
    The second child creates a file called statistics.txt, in which it will store, on one line, each distinct letter encountered and the number of times it appears in the received data stream. Finally, it will send to the parent, through an additional pipe, the number of distinct letters encountered.
    The parent displays the result received from the second child on the screen.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define NUMBER_OF_PIPES 3
#define BUFFER_SIZE 1024
#define MAX_TEXT_SIZE 4098

void init_pipes(int pipes[][2], unsigned size);
void check_pipes(int pipes[][2], unsigned size);
void close_pipes(int pipes[][2], unsigned size);
void check_process_creation(pid_t id);
void check_fd(int fd);

int main(int argc, char *argv[])
{
    int pipes[3][2] = {0};
    int child1 = 0, child2 = 0;

    init_pipes(pipes, NUMBER_OF_PIPES);
    check_pipes(pipes, NUMBER_OF_PIPES);

    child1 = fork();
    check_process_creation(child1);

    if (!child1)
    {
        close(pipes[0][1]);

        char data_from_parent[MAX_TEXT_SIZE] = {};
        
        while (read(pipes[0][0], data_from_parent, BUFFER_SIZE) > 0)
            ;
        printf("Data from parent: %s\n", data_from_parent);

        close_pipes(pipes, NUMBER_OF_PIPES);
    }
    else
    {
        child2 = fork();
        check_process_creation(child2);

        if (!child2)
        {
            /* code */
        }
        else
        {
            char data[MAX_TEXT_SIZE] = {};
            int data_fd = open("data.txt", O_RDONLY);

            check_fd(data_fd);

            while (read(data_fd, data, BUFFER_SIZE) > 0)
                ;

            int write_buffer = strlen(data);
            while (write(pipes[0][1], data, write_buffer) < write_buffer)
                ;

            close_pipes(pipes, NUMBER_OF_PIPES);

            return EXIT_SUCCESS;
        }
    }
}

void init_pipes(int pipes[][2], unsigned size)
{

    for (int i = 0; i < size; i++)
        pipe(pipes[i]);
}

void check_pipes(int pipes[][2], unsigned size)
{
    for (int i = 0; i < size; i++)
        if (pipes[i][0] == -1 || pipes[i][1] == -1)
        {
            fprintf(stderr, "Failed to create pipe at position: %u\n", i);
            exit(EXIT_FAILURE);
        }
}

void close_pipes(int pipes[][2], unsigned size)
{
    for (size_t i = 0; i < size; i++)
        close(pipes[i][0]), close(pipes[i][0]);
}

void check_process_creation(pid_t id)
{
    if (id == -1)
    {
        perror("Failed to create new process with fork.");
        exit(EXIT_FAILURE);
    }
}

void check_fd(int fd)
{
    if (fd ==-1)
    {
        perror("Failed opening the file.\n");
        exit(EXIT_FAILURE);
    }
}