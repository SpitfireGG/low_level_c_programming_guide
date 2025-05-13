#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include "bits/time.h"

void updatePtrs(size_t *ptrA, size_t *ptrB, size_t *val)
{
    *ptrA += *val;
    *ptrB += *val;
    printf("unrestricted : %ld + %ld = %ld\n", *ptrA, *ptrB, *ptrA + *ptrB);
}

void updatePtrsRestrict(size_t *restrict ptrA,
                        size_t *restrict ptrB,
                        size_t *restrict val)
{
    *ptrA += *val;
    *ptrB += *val;
    printf("restricted : %ld + %ld = %ld\n", *ptrA, *ptrB, *ptrA + *ptrB);
}

double get_elapsed_time(struct timespec start, struct timespec end)
{
    return ((end.tv_sec - start.tv_sec) * 1e3)
           + ((end.tv_nsec - start.tv_nsec) / 1e-9);
}

void benchmark()
{
    struct timespec start, end;

    // init vars
    size_t a   = 10;
    size_t b   = 30;
    size_t val = 40;

    printf("running unrestricted !!!!\n\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    updatePtrs(&a, &b, &val);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double unrestricted_elapsed = get_elapsed_time(start, end);

    clock_gettime(CLOCK_MONOTONIC, &start);
    updatePtrsRestrict(&a, &b, &val);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double resticted_elapsed = get_elapsed_time(start, end);

    if (resticted_elapsed < unrestricted_elapsed)
    {
        printf("\n............benchmark...........\n\n");
        printf("unrestricted took:  %.2fms\n", unrestricted_elapsed);
        printf("restricted took: %.2fms\n", resticted_elapsed);
    }
    else
    {
        printf("restricted took more time than unrestricted??\n\n");
        perror("benchmark");
    }
}

int main()
{
    benchmark();
    return 0;
}
