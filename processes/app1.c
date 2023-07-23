#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("Process id: %i\n", getpid());

    return EXIT_SUCCESS;
}