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

int main(int argc, char *argv[])
{
    printf("Test\n");
    return EXIT_SUCCESS;
}