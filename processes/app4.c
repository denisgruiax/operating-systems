#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    pid_t processes_id = fork();

    if (processes_id < 0)
    {
        fprintf(stderr, "Can't create fork.\n");

        return EXIT_FAILURE;
    }
    else if (!processes_id)
    {
        printf("Child process: My PID is %i\n", getpid());
        kill(getppid(), SIGKILL);

        return EXIT_SUCCESS;
    }
    else
    {
        int status;

        wait(&status);

        printf("Parent process: My PID is %i, status is %i\n", getpid(), status);
    }

    return EXIT_SUCCESS;
}