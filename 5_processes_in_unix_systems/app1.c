/*
    In a for loop calling the fork() function will create 2 at power of number of iterations.
    This is happening because fork is creating a child from the caller process.
    At every iteration the the child process will inherit the data and code from the parent process. It will go like this

    Iteration 1
    Process 0 -> Process 1

    Iteration 2
    Process 0 -> Process 2
    Process 1 -> Process 3

    Iteration 3
    Process 0 -> Process 4
    Process 1 -> Process 5
    Process 2 -> Process 6
    Process 3 -> Process 7

    ...
    Iteration N
    From mathematical induction we can coclude that the pattern is

    2^N
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    for (size_t i = 0; i < 5; i++)
        fork();
}