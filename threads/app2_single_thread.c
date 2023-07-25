#include <stdio.h>
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

int main()
{
    int n = 250; // Fibonacci number to compute

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (size_t i = 0; i < 10000000; i++)
       fibonacci(n);

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    return 0;
}
