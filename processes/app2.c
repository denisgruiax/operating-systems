#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t processes_id = fork();
    int value = 19;

    if (processes_id < 0)
    {
        fprintf(stderr, "Can't create fork.\n");

        return EXIT_FAILURE;
    }
    else if (!processes_id)
    {
        value = 25;
        
        printf("Child process: My PID is %i\n", getpid());
        
        printf("value = %i\n", value);

        return EXIT_SUCCESS;
    }
    else
    {
        int status;
        
        wait(&status);

        printf("Parent process: My PID is %i, status is %i\n", getpid(), status);
        
        printf("value = %i\n", value);
    }

    return EXIT_SUCCESS;
}