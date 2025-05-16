#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sys/types.h"

int main()
{
    pid_t goten;  // goten is the child process fo the parent goku
    int status;   // store the childs status

    printf("about to fork the parent process ( pid : %d)\n", getpid());

    goten = fork();
    if (goten < 0)
    {
        perror("fork  failed\n");
        exit(1);
    }
    else if (goten == 0)
    {
        printf("child: pid %d is about to run ls -la\n", getpid());
        printf("uuid of the cureent process is %d\n", getuid());
        char *args[] = {"ls", "-la", "/tmp", NULL};
        sleep(3);
        execvp(args[0], args);
        perror("execv failed\n");
        exit(1);
    }
    else
    {
        // parent process -> Goku

        printf("parent forked successfully, parent pid is %d, child process is "
               "%d. waiting for child process to finish\n",
               getppid(),
               getpid());
    }

    pid_t killed_gotens_pid = wait(&status);

    if (killed_gotens_pid == -1)
    {
        perror("kill child process goten\n");
    }
    else
    {
        printf("goten { pid %d } has been eliminated \n", killed_gotens_pid);
        printf("goten { pid %d } has been eliminated \n", getpid());
        printf("uuid of the cureent process is %d\n", getuid());
    }
    // decode the status
    if (WIFEXITED(status))
    {
        printf("goku: goten exited successfully with status %d\n",
               WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("goku: goten was killed explicitly by signal %d",
               WTERMSIG(status));
    }
    else
    {
        printf("goten exited abnormally, check for more\n");
    }

    return 0;
}
