#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
using namespace std;

int main()
{
    char *process;
    int estimated_time_left;
    int pcb_current_time;

    cout << "CPU Emulator" << endl;

    estimated_time_left = pcb_current_time - 200;
    if (estimated_time_left <= pcb_current_time)
    {
        cout << "The process is finished" << endl;
    }

    return 0;
}