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

void init_pipes(int pipes[][2], unsigned size);
void check_pipes(int pipes[][2], unsigned size);
void close_pipes(int pipes[][2], unsigned size);

int main(int argc, char *argv[])
{
    int pipes[3][2];

    init_pipes(pipes, 3);
    check_pipes(pipes, 3);

    return EXIT_SUCCESS;
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