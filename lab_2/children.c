#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    //parent P
    pid_t fq = 0, fr = 0;
    int status;
    fq = fork();
    if (fq == 0)
    {
        printf("I am child one, my PID is: %d\n", getpid());

        fr = fork();
        if (fr == 0)
        {
            printf("I am child two, my PID is: %d\n", getpid());
        }
    }
    else
    {
        waitpid(fr, NULL, 0);
        waitpid(fq, NULL, 0);
        printf("Parent Process is done %d\n", getppid());
    }
}