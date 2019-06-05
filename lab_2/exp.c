#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

pid_t printAndFork()
{
    pid_t k;
    k = fork();
    printf("my PID is: %d\n my Parent PID is: %d\n", getpid(), getppid());
    return k;
}

int main()
{

    if (fork() && fork())
    {
        printf("1\n");
        fork();
    }
}