/*
    App 2
    The program will copy the data from an existing file and will create a new file and will copy the data inside it. If the file is already created,
    the O_EXCL flag will prevent overwritting the existing file. Th program is not optimized for performance, just a simple example.

    I can excute the program as below:
        ./app2.exe file.txt file2.txt

    S_IRWXU: Grants read, write, and execute permissions to the owner of the file
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 100

void check_arguments_size(int argc);
int *get_descriptors(char *argv[]);
void copy_data(int *fds);

int main(int argc, char *argv[])
{
    int *fds = NULL;

    check_arguments_size(argc);
    fds = get_descriptors(argv);
    copy_data(fds);

    free(fds);

    exit(EXIT_SUCCESS);
}

void check_arguments_size(int argc)
{
    if (argc != 3)
    {
        fprintf(stderr, "Error: Wrong argument size. %i\n", __LINE__);
        exit(EXIT_FAILURE);
    }
}

int *get_descriptors(char *argv[])
{
    int *fds = calloc(2, sizeof(int));
    if (!fds)
    {
        fprintf(stderr, "Allocating memory for opening files have failed. %i\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    if ((fds[0] = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Allocating memory for opening source file have failed. %i\n", __LINE__);
        close(fds[0]);
        free(fds);
        exit(EXIT_FAILURE);
    }

    if ((fds[1] = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRWXU)) == -1)
    {
        fprintf(stderr, "Allocating memory for opening destination file have failed. %i\n", __LINE__);
        close(fds[0]);
        close(fds[1]);
        free(fds);
        exit(EXIT_FAILURE);
    }

    return fds;
}

void copy_data(int *fds)
{
    int bytes_read = 0;
    char buffer[BUFFER_SIZE] = {};

    while ((bytes_read = read(fds[0], buffer, BUFFER_SIZE)) > 0)
    {
        write(fds[1], buffer, bytes_read);
    }

    if (bytes_read == -1)
    {
        fprintf(stderr, "Reading the file have failed. %i\n", __LINE__);
    }

    close(fds[0]);
    close(fds[1]);
}