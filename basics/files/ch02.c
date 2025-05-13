#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }

    if (ftruncate(fd, 4096) == -1)
    {
        perror("resize");
        exit(1);
    }

    void *mapped = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    sprintf((char *) mapped, "Hello from the other side\n");
    printf("%s\n", (char *) mmap);

    if (munmap(mapped, 4096) == -1)
    {
        perror("mapping failed");
    }
    close(fd);

    return 0;
}
