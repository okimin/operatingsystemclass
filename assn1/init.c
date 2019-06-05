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
        if (child2 == 0)
        {
            printf("Child Two is created\n");
            //printf(argv[1]);
            execl("./scheduler.py", argv[1], NULL);
        }
        else
        {
            execl("./cpu_emulator.py", argv[1], NULL);
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