#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <queue>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class PCB
{
public:
  char *process_name;
  int PID;
  char *state;
  int priority;
  int interruptable;
  int est_total_run_time;
  int est_remaining_run_time;
};

int main()
{
  queue<PCB> processes;

  cout << "Scheduling" << endl;
  string processDesc;
  ifstream file("process.txt");

  if (file.is_open())
  {
    while (getline(file, processDesc))
    { // get a whole line
      string seperate = processDesc;
      string delimit = ",";

      size_t pos = seperate.find(delimit);
      string procName = seperate.substr(0, pos);
      seperate.erase(0, pos + delimit.length());

      pos = seperate.find(delimit);
      int procName = seperate.substr(0, pos);
      seperate.erase(0, pos + delimit.length());

      processes.append(new PCB());
      while (getline(seperate, processDesc, ','))
      {
      }
    }

    return 0;
  }