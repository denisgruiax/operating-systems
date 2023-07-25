#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *thread_function(void *arg)
{
    int thread_id = *(int *)arg;
    printf("Hello from thread %d\n", thread_id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_args[i] = i;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (result != 0)
        {
            fprintf(stderr, "Error creating thread %d\n", i);
            return -1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int result = pthread_join(threads[i], NULL);
        if (result != 0)
        {
            fprintf(stderr, "Error joining thread %d\n", i);
            return -1;
        }
    }

    printf("All threads have finished.\n");

    return 0;
}
