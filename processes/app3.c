#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t processes_id;
    int value = 19;
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("Pipe creation failed");
        return EXIT_FAILURE;
    }

    processes_id = fork();

    if (processes_id < 0)
    {
        fprintf(stderr, "Can't create fork.\n");
        return EXIT_FAILURE;
    }
    else if (!processes_id)
    {
        close(pipefd[0]); // Close the read end of the pipe in the child

        value = 25;

        printf("Child process: My PID is %i\n", getpid());

        printf("Child process: value = %i\n", value);

        // Write the new value to the pipe
        write(pipefd[1], &value, sizeof(value));
        close(pipefd[1]); // Close the write end of the pipe in the child

        return EXIT_SUCCESS;
    }
    else
    {
        close(pipefd[1]); // Close the write end of the pipe in the parent

        int status;
        wait(&status);

        // Read the new value from the pipe
        read(pipefd[0], &value, sizeof(value));
        close(pipefd[0]); // Close the read end of the pipe in the parent

        printf("Parent process: My PID is %i, status is %i\n", getpid(), status);

        printf("Parent process: value = %i\n", value);
    }

    return EXIT_SUCCESS;
}
