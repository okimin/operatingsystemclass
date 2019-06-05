#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// pid_t printAndFork()
// {
//     pid_t k;
//     k = fork();
//     printf("my PID is: %d\n my Parent PID is: %d\n", getpid(), getppid());
//     return k;
// }

int main()
{

    int x = 0;
    if (fork() || (x++))
    {
        printf("x=%d\n", x);
    }
    else
    {
        printf("x= %d\n", x);
    }
}