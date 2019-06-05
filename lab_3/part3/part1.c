
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int child = fork();
    if (child == 0)
    {
        printf("PID: %d\n", getpid());
        execl("/bin/date", argv[0], NULL);
        printf("EXECVP Failed\n");
        /* The above line will be printed only on error and not otherwise */
    }
}