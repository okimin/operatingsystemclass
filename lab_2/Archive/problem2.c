#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    //parent P
    int a = 10, b = 25, fq = 0, fr = 0;
    fq = fork(); // fork a child - call it Process Q
    if (fq == 0)
    {
        a = a + b;
        printf("A is %d B is %d Process PID is %d and Parent is %d\n", a, b, getpid(), getppid());
        // values of a, b, and process_id
        fr = fork(); // fork another child - call it Process R
        if (fr != 0)
        {
            b = b + 20;
            printf("A is %d B is %d Process PID is %d and Parent is %d\n", a, b, getpid(), getppid());
            // print values of a,b, and process_id
        }
        else
        {
            a = (a * b) + 30;
            printf("A is %d B is %d Process PID is %d and Parent is %d\n", a, b, getpid(), getppid());
            //print values of a, b, and process_id
        }
    }
    else
    {
        b = a + b - 5;
        printf("A is %d B is %d Process PID is %d and Parent is %d\n", a, b, getpid(), getppid());
    } // Child successfully forked
}