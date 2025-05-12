#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "unistd.h"
#include <time.h>

#define ERR(msg) fprintf(stderr, "[%s: %d]: %s\n", __FILE__, __LINE__, msg)
#define BUFFER_SIZE 1024

#define FILENAME "some.txt"

void unbuffered()
{
    // unbuffered

    int fd = open(FILENAME, O_CREAT | O_WRONLY, 0666);
    if (fd == -1)
    {
        ERR("could not be found or create file\n");
        exit(1);
    }
    else
    {
        printf("FIle created successfull\n");
    }

    for (int i = 0; i < 1000; i++)
    {
        write(fd, "H", 1);
    }
    close(fd);
}
void buffered()
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        ERR("file could not be opened or was never found\n");
        exit(1);
    }

    for (int i = 0; i < 1000; i++)
    {
        fputc('H', file);
    }
    fclose(file);
}

int main()
{
    clock_t start, end;

    start = clock();
    unbuffered();
    end = clock();

    double unbuffered = (double) (end - start) / CLOCKS_PER_SEC;

    printf("took :unbuffered [%.2f] seconds  to complete\n", unbuffered);

    start = clock();
    buffered();
    end = clock();

    double buffered = (double) (end - start) / CLOCKS_PER_SEC;
    printf("took :buffered [%.2f] seconds  to complete\n", buffered);

    printf("buffered is %.2fx faster than unbuffered", buffered / unbuffered);

    return 0;
}
