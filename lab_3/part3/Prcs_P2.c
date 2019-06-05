#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

int ParentProc()
{
    int rd;
    int fd = open("source.txt", O_RDONLY);
    int destOne = open("destination1.txt", O_RDWR | O_CREAT);
    int destTwo = open("destination2.txt", O_RDWR | O_CREAT);
    bool isDestOne = true;
    char buff[100];

    if (-1 == fd)
    {
        perror("ERROR: ");
        return 1;
    }
    else if (-1 == destOne)
    {
        perror("ERRORR: ");
        return 1;
    }
    else if (-1 == destTwo)
    {
        perror("ERRORRR: ");
        return 1;
    }
    else
    {
        rd = 1;
        while (rd != 0)
        {

            if (isDestOne)
            {
                rd = read(fd, buff, 100);
                // if (rd == 0)
                // {
                //     continue;
                // }
                for (int x = 0; x < sizeof(buff) / sizeof(char); x++)
                {
                    if (buff[x] == '1')
                        buff[x] = 'A';
                }
                write(destOne, &buff, rd);

                isDestOne = false;
            }
            else
            {
                rd = read(fd, buff, 50);
                // if (rd == 0)
                // {
                //     continue;
                // }
                for (int x = 0; x < sizeof(buff) / sizeof(char); x++)
                {
                    if (buff[x] == '2')
                        buff[x] = 'B';
                }
                write(destTwo, &buff, rd);

                isDestOne = true;
            }
        }
        close(fd);
        close(destOne);
        close(destTwo);
    }
    return 0;
}
int main(int argc, char *argv[])
{
    return ParentProc();
}