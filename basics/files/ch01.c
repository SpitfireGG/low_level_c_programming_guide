#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define ERR(msg) fprintf(stderr, "[ERROR %s:%d] %s\n", __FILE__, __LINE__, msg)

#define MANUAL_BUFFER_SIZE (1024 * 4)
#define NUM_RUNS 5
#define FILENAME "somefile.txt"
#define TOTAL_BYTES_TO_WRITE (1024LL * 10LL)

// NOTE: the unbuffered does far better when writing a very large byte to the
// buffer, but buffered doesnot because the buffered I/O has to perform due to
// factors like function calls , but fputs does not perform system calls when
// wirting , here syscall by buffered is ~= 10Million times where unbuffered
// does ~= > 2000 sys calls

void perform_unbuffered_writes_(const char *filename, long long total_bytes)
{
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror(" Unbuffered open");
        ERR("Could not create/open file for  unbuffered write.");
        exit(EXIT_FAILURE);
    }

    char manual_buffer[MANUAL_BUFFER_SIZE];
    memset(manual_buffer, 'S', MANUAL_BUFFER_SIZE);

    long long bytes_actually_written = 0;

    while (bytes_actually_written < total_bytes)
    {
        long long bytes_to_write_this_chunk = MANUAL_BUFFER_SIZE;

        ssize_t written_now =
            write(fd, manual_buffer, bytes_to_write_this_chunk);

        if (written_now == -1)
        {
            perror(" Unbuffered write");
            ERR("Write failed during  unbuffered operation.");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (written_now == 0 && bytes_to_write_this_chunk > 0)
        {
            ERR(" Unbuffered: Wrote 0 bytes when expecting more. "
                "Disk full?");
            break;
        }

        bytes_actually_written += written_now;
    }

    if (fsync(fd) == -1)
    {
        perror(" Unbuffered fsync failed");
    }
    close(fd);
}

void perform_buffered_writes(const char *filename, long long size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Buffered open");
        ERR("Opening buffered failed");
        exit(EXIT_FAILURE);
    }
    for (long long i = 0; i < size; i++)
    {
        if (fputc('B', file) == EOF)
        {
            ERR("Buffered writing failed (fputc)");
            if (ferror(file))
            {
                perror("fputc stream error");
            }
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }
    if (fflush(file) == EOF)
    {
        perror("Buffered fflush failed");
    }
    fclose(file);
}

double get_elapsed_seconds(struct timespec start, struct timespec end)

{
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void run_benchmark()
{
    struct timespec start_time, end_time;
    double total_time_unbuffered = 0.0;
    double total_time_buffered   = 0.0;

    printf("Starting benchmark: %d runs, %lld bytes target per run, manual "
           "buffer %d bytes.\n\n",
           NUM_RUNS,
           TOTAL_BYTES_TO_WRITE,
           MANUAL_BUFFER_SIZE);

    printf("Running  Unbuffered tests...\n");
    for (int i = 0; i < NUM_RUNS; ++i)
    {
        remove(FILENAME);
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        perform_unbuffered_writes_(FILENAME, TOTAL_BYTES_TO_WRITE);
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        double elapsed = get_elapsed_seconds(start_time, end_time);
        total_time_unbuffered += elapsed;
        printf("  Run %d (unbuffered): %.4f seconds\n", i + 1, elapsed);
    }
    double time_unbuffered_avg = total_time_unbuffered / NUM_RUNS;
    printf("Average time for  unbuffered I/O: %.4f seconds\n\n",
           time_unbuffered_avg);

    printf("Running Buffered tests (fputc)...\n");
    for (int i = 0; i < NUM_RUNS; ++i)
    {
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        perform_buffered_writes(FILENAME, TOTAL_BYTES_TO_WRITE);
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        double elapsed = get_elapsed_seconds(start_time, end_time);
        total_time_buffered += elapsed;
        printf("  Run %d (buffered):   %.4f seconds\n", i + 1, elapsed);
    }
    double time_buffered_avg = total_time_buffered / NUM_RUNS;
    printf("Average time for buffered I/O (fputc): %.4f seconds\n",
           time_buffered_avg);

    printf("\n---------------- Final Evaluation ---------------\n");
    printf("Average  Unbuffered Time: %.4f seconds\n", time_unbuffered_avg);
    printf("Average Buffered Time (fputc):    %.4f seconds\n",
           time_buffered_avg);

    if (time_unbuffered_avg > 0.000001 && time_buffered_avg > 0.000001)
    {
        if (time_buffered_avg < time_unbuffered_avg)
        {
            printf("Buffered I/O was %.2fx faster than  unbuffered "
                   "I/O.\n",
                   time_unbuffered_avg / time_buffered_avg);
        }
        else if (time_unbuffered_avg < time_buffered_avg)
        {
            printf(" Unbuffered I/O was %.2fx faster than buffered "
                   "I/O.\n",
                   time_buffered_avg / time_unbuffered_avg);
        }
        else
        {
            printf("Buffered and  Unbuffered I/O took approximately "
                   "the same time.\n");
        }
        printf("Buffered I/O took %.2f%% of the time  unbuffered I/O "
               "took.\n",
               (time_buffered_avg / time_unbuffered_avg) * 100.0);
    }
    else
    {
        printf("Could not perform calculation"
               "small or zero times.\n");
    }
    remove(FILENAME);
}

int main()
{
    run_benchmark();
    return 0;
}
