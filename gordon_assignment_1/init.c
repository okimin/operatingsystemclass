#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int status;
    int child = 0, child2 = 0, pid;
    child = fork();
    if (child == 0)
    {
        printf("Child One is created\n");
        child2 = fork();
        if (child2 = 0)
        {
            printf("Child Two is created\n");
        }
        else
        {
            /* code */
        }
    }
    else
    {
        /* code */
        pid = wait(&status);
        pid = wait(&status);
        printf("Everything is done\n");
    }

    return 0;
}