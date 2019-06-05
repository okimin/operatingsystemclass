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

    int destOne = open("destination1.txt", O_RDWR | O_CREAT, 0700);
    int destTwo = open("destination2.txt", O_RDWR | O_CREAT, 0700);

    if (-1 == destOne || -1 == destTwo)
    {
        perror("ERROR: ");
        return 1;
    }

    else
    {
        printf("Print Success.\n");
    }

    return 0;
}