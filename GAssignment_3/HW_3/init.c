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
        child2 = fork();

        // Will only take up to 3 arguments
        //List of arguments are ./scheduler.py, Mode, and Time Quantum.
        //No TQ for Process to be done in One Go. No Arguments Or Wrong Arguments for Automatic FCFS
        //Only Putting TQ as argument Will Count as Wrong Argument
        if (child2 == 0)
        {
            //Mode argument goes to here
            execl("./scheduler.py", argv[1], argv[1], argv[2], NULL);
        }
        else
        {
            //Time Quantum Goes Here.
            execl("./cpu_emulator.py", argv[1], argv[2], NULL);
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