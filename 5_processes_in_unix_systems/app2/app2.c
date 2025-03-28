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
#include <ctype.h>

#define NUMBER_OF_PIPES 3
#define BUFFER_SIZE 1024
#define MAX_TEXT_SIZE 4098

void init_pipes(int pipes[][2], unsigned size);
void check_pipes(int pipes[][2], unsigned size);
void close_pipes(int pipes[][2], unsigned size);
void check_process_creation(pid_t id);
void check_fd(int fd);
char *filter(char *data, int (*f)(int));

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
        close(pipes[1][0]);

        char data_from_parent[MAX_TEXT_SIZE] = {};

        read(pipes[0][0], data_from_parent, MAX_TEXT_SIZE);

        char *data_filtered = filter(data_from_parent, islower);
        size_t write_buffer = strlen(data_filtered);
        while (write(pipes[1][1], data_filtered, write_buffer) < write_buffer)
            ;

            close_pipes(pipes, NUMBER_OF_PIPES);

        free(data_filtered);
    }
    else
    {
        child2 = fork();
        check_process_creation(child2);

        if (!child2)
        {
            close(pipes[1][1]);
            close(pipes[2][0]);

            char data_from_child1[MAX_TEXT_SIZE] = {};

            read(pipes[1][0], data_from_child1, MAX_TEXT_SIZE);

            size_t write_buffer = strlen(data_from_child1);
            while (write(pipes[2][1], data_from_child1, write_buffer) < write_buffer)
                ;

            close_pipes(pipes, NUMBER_OF_PIPES);
        }
        else
        {
            close(pipes[0][0]);
            close(pipes[2][1]);

            char data[MAX_TEXT_SIZE] = {};
            int data_fd = open("data.txt", O_RDONLY);

            char data_from_child2[MAX_TEXT_SIZE];

            check_fd(data_fd);

            read(data_fd, data, MAX_TEXT_SIZE);

            size_t write_buffer = strlen(data);
            while (write(pipes[0][1], data, write_buffer) < write_buffer)
                ;

            while (read(pipes[2][0], data_from_child2, BUFFER_SIZE) > 0)
                ;

            printf("Filtered data is:\n%s\n", data_from_child2);

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
    if (fd == -1)
    {
        perror("Failed opening the file.\n");
        exit(EXIT_FAILURE);
    }
}

char *filter(char *data, int (*f)(int))
{
    unsigned size = 0;
    char *buffer = malloc(1);
    char *start = buffer;

    while (*data != '\0')
    {
        if (f(*data))
        {
            char *new_buffer = realloc(start, size + 2);

            if (!new_buffer)
            {
                free(start);
                return NULL;
            }

            start = new_buffer;
            start[size++] = *data;
        }

        data++;
    }

    return buffer;
}