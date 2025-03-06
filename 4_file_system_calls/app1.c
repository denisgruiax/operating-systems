/*
    Opening a file printing the content until end of the file in a fixed buffer and display its content every iteration.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 10

int main(int argc, char *argv[])
{
    int bytes_read = 0;
    int file_descriptor = open("file.txt", O_RDONLY);
    char buffer[BUFFER_SIZE] = {};

    printf("content:\n");

    while ((bytes_read = read(file_descriptor, buffer, BUFFER_SIZE)) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1)
    {
        perror("Reading the file have failed");
    }

    close(file_descriptor);
}