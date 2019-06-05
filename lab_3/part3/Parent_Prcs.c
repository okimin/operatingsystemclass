#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    int childone = fork();
    if (childone == 0)
    {
        execl("Prcs_P1", argv[0], NULL);
    }
    else
    {
        sleep(5);
        int childtwo = fork();
        if (childtwo == 0)
        {
            execl("Prcs_P2", argv[0], NULL);
        }
    }

    return 0;
}