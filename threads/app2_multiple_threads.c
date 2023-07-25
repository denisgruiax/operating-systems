#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 5

unsigned long long fibonacci(int n)
{
    if (n <= 1)
        return n;

    unsigned long long a = 0;
    unsigned long long b = 1;
    unsigned long long result;

    for (int i = 2; i <= n; i++)
    {
        result = a + b;
        a = b;
        b = result;
    }

    return result;
}

void *thread_function(void *arg)
{
    int thread_id = *(int *)arg;
    int n = 250; // Fibonacci number to compute
    for (size_t i = 0; i < 2000000; i++)
        fibonacci(n);
    // printf("Thread %d: Fibonacci(%d) = %llu\n", thread_id, n, fib_result);
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

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int result = pthread_join(threads[i], NULL);
        if (result != 0)
        {
            fprintf(stderr, "Error joining thread %d\n", i);
            return -1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    printf("All threads have finished.\n");

    return 0;
}
