#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum)
{
    printf("caught signal (%d) sigint, press ctrl + c to exit the process\n",
           signum);
    signal(SIGINT, SIG_DFL);
}
int main(void)
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        perror("signal error\n");
        return 1;
    }
    printf("Press Ctrl+C to trigger the handler. (PID: %d)\n", getpid());
    while (1)
    // keeps executing over and over again
    {
        for (int i = 0; i < 10; i++)
        {
            printf("%d\n", i);
            sleep(3);
        }
    }
    return 0;
}
