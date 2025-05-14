#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 1000
#define ARRAY_SIZE 10000

double no_restrict(size_t n, double *x, double *y, double *result)
{
    double sum = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        result[i] = x[i] + y[i];
        sum += result[i];
    }
    return sum;
}

double use_restrict(size_t n,
                    double *restrict x,
                    double *restrict y,
                    double *restrict result)
{
    double sum = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        result[i] = x[i] + y[i];
        sum += result[i];
    }
    return sum;
}

double elapsed_time(struct timespec start, struct timespec end)
{
    double sec_diff = (end.tv_sec - start.tv_sec) * 1e3;

    double nsec_diff = (end.tv_nsec - start.tv_nsec) / 1e6;

    // check if time_nsec is negative , if negative we add 1 milisecond to
    // time_sec
    if (end.tv_nsec < start.tv_nsec)
    {
        sec_diff -= 1.0;
        nsec_diff += 1000.00;
    }
    return sec_diff + nsec_diff;
}
void get_benchmark()
{
    struct timespec start, end;
    double unrestricted_total = 0.0;
    double restricted_total   = 0.0;

    // allocate memory
    double *x    = malloc(ARRAY_SIZE * sizeof(double));
    double *y    = malloc(ARRAY_SIZE * sizeof(double));
    double *res1 = malloc(ARRAY_SIZE * sizeof(double));
    double *res2 = malloc(ARRAY_SIZE * sizeof(double));

    if (!x || !y || !res1 || !res2)
    {
        perror("allocation failed\n");
        exit(1);
    }

    // init the array with some data
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        x[i]    = (double) i;
        y[i]    = (double) (ARRAY_SIZE - i);
        res1[i] = 0.0;
        res2[i] = 0.0;
    }

    printf("running the benchmark on [ %d iterations ] on [ %d array "
           "size ].....\n\n",
           ITERATIONS,
           ARRAY_SIZE);

    printf("runnning the benchmark on  unrestricted...\n");

    // for unrestricted
    for (int i = 0; i < ITERATIONS; i++)
    {
        memset(res1, 0, sizeof(double) * ARRAY_SIZE);

        clock_gettime(CLOCK_MONOTONIC, &start);
        no_restrict(ARRAY_SIZE, x, y, res1);
        clock_gettime(CLOCK_MONOTONIC, &end);
        unrestricted_total += elapsed_time(start, end);
    }
    double unrestricted_avg = (unrestricted_total / ITERATIONS);
    printf("average time by unrestricted : %.6fms\n", unrestricted_avg);

    // for restricted
    printf("\nrunnning the benchmark on restricted...\n");

    // for unrestricted
    for (int i = 0; i < ITERATIONS; i++)
    {
        // use the same variable for each iterations
        memset(res2, 0, sizeof(double) * ARRAY_SIZE);

        clock_gettime(CLOCK_MONOTONIC, &start);
        use_restrict(ARRAY_SIZE, x, y, res2);
        clock_gettime(CLOCK_MONOTONIC, &end);

        restricted_total += elapsed_time(start, end);
    }

    // get the average time diff of both of them

    double restricted_avg = (restricted_total / ITERATIONS);
    printf("average time by restricted : %.6fms\n", restricted_avg);

    // check if one of them has higher time diff

    if (restricted_avg < unrestricted_avg)
    {
        double time_diff  = unrestricted_avg - restricted_avg;
        double diff_ratio = unrestricted_avg / restricted_avg;

        printf("for [ %d iterations ] restricted performed better by diff: "
               "%.6fms (%2.fx speedup)\n",
               ITERATIONS,
               time_diff,
               diff_ratio);
    }
    else if (unrestricted_avg < restricted_avg)
    {
        double time_diff  = restricted_avg - unrestricted_avg;
        double diff_ratio = restricted_avg / unrestricted_avg;
        printf("for [ %d iterations ] unrestricted performed better by diff: "
               "%.6fms\nratio diff: %.6fms",
               ITERATIONS,
               time_diff,
               diff_ratio);
    }
    else
    {
        printf("both of them took the same time for %d\n", ITERATIONS);
    }
    free(x);
    free(y);
    free(res1);
    free(res2);
}

int main()
{
    get_benchmark();
    return 0;
}
