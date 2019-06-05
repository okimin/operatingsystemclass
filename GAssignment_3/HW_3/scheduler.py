#! /usr/local/bin/python3

'''
    Client - calls server, opens file, nexts server data line by line.
'''

from collections import deque
import socket
import queue
import time
import sys


class PCB:
    def __init__(self, arrivalTime, procName, PID, state, priority, interruptable, est_total_run_time, est_remaining_run_time):
        self.arrivalTime = arrivalTime
        self.procName = procName
        self.PID = PID
        self.state = state
        self.priority = priority
        self.interruptable = interruptable
        self.est_total_run_time = est_total_run_time
        self.est_remaining_run_time = est_remaining_run_time


# def print_procs_at_arrival_time():

#     with open('processes.txt', 'rt') as infile:
#         lines = infile.read().split('\n')

#     # list of processes (not including the header line).
#     process_list = [line.split(',') for line in lines[0:]]

#     current_time = 0
#     current_proc = process_list.pop(0)

#     while process_list:

#         if int(current_proc[0]) == current_time:
#             print(','.join(current_proc))
#             current_proc = process_list.pop(0)

#         # Purely optional - delay, just so effect can be seen:
#         time.sleep(0.1)
#         current_time += 1

def sortPriority(val):
    return int(val[4])


def sortSJN(val):
    return int(val[-1])


def connect(host, port, mode, timeQuantum):
    contSwitch = 0
    arrival = 0
    service_time = 0
    wait_time = 0
    amount_proc = 0
    start_avg = 0
    end_avg = 0
    n = 0
    start = 0
    readyToSend = 1
    readyToReceive = 0
    noMoreProcs = 0

    if timeQuantum == 0:
        timeQuantum = 9999

    with open('processes.txt', 'rt') as infile:
        lines = infile.read().split('\n')
        processes = deque()
        process_list = [line.split(',') for line in lines[0:]]
        readyQ = []

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((host, port))
        print('Connected to %s:%s' % (host, port))
        currentTime = 0
        totalTime = 0
        procsRemaining = 0
        currentRun = " "

        for line in lines[:]:
            procsRemaining += 1
            processes.append(line)

        amount_proc = len(processes)
        next = processes.popleft().split(',')

        print(next[1])

        while(procsRemaining > 0):

            if not noMoreProcs:
                if (currentTime < int(next[0])):
                    #print("No New Process Arrived")
                    n = 0
                else:
                    print("Process", next[1], "has arrived")
                    readyQ.append(next)
                    start_avg += currentTime
                    # print(readyQ)
                    if processes:
                        next = processes.popleft().split(",")
                    else:
                        noMoreProcs = 1
            start_avg = start_avg/amount_proc
            if readyQ and readyToSend == 1:
                if mode == "priority":
                    readyQ.sort(key=sortPriority)
                    print("Doing priority")
                elif mode == "sjn" or mode == "srtn":
                    readyQ.sort(key=sortSJN)

                # print(readyQ)
                currentRun = readyQ.pop(0)

                print('\n Sending:\t%s' % currentRun)
                readyToSend = 0
                readyToReceive = 1
                sock.send(str(','.join(currentRun)).encode('utf-8'))

                if (timeQuantum >= int(currentRun[-1])):
                    service_time = currentTime + int(currentRun[-1])

                else:
                    service_time = currentTime + timeQuantum

            elif readyToReceive == 1 and currentTime == service_time:

                data = sock.recv(1024)
                print('\n Received:\t%s' % data.decode())
                check = data.decode().split(',')[-1]

                if not int(check) <= 0:
                    currentTime += 2  # ContextSwitch
                    contSwitch += 1
                    readyQ.append(data.decode().split(","))
                else:  # One Process Done
                    procsRemaining -= 1
                    contSwitch += 1
                    end_avg += currentTime
                    print("Processes remaining : ")
                    for row in readyQ:
                        print(' '.join(row[1]))

                readyToSend = 1
                readyToReceive = 0
            # time.sleep(0.01)
            currentTime += 1

            wait_time += len(readyQ)

    end_avg = end_avg/amount_proc
    avg_time_stuff = end_avg - start_avg
    print("Time done :", currentTime-1)
    print("Context Switches :", contSwitch)
    print("Total Average Waiting Time :", wait_time/14)
    print("Average Turnaround Time: ", avg_time_stuff, " seconds")


if __name__ == '__main__':

    host = '127.0.0.1'
    port = 9000

    mode = " "
    timeQuantum = 0

    if len(sys.argv) == 3:
        if sys.argv[1] == "fcfs" or sys.argv[1] == "sjn" or sys.argv[1] == "priority" or sys.argv[1] == "srtn":
            mode = sys.argv[1]
        else:
            mode = "fcfs"
        if sys.argv[2].isdigit():
            timeQuantum = int(sys.argv[2])

    elif len(sys.argv) == 2:
        if sys.argv[1] == "fcfs" or sys.argv[1] == "sjn" or sys.argv[1] == "priority" or sys.argv[1] == "srtn":
            mode = sys.argv[1]
        else:
            mode = "fcfs"
        print(" Executing mode ", mode)
    else:
        print("No Inputs So Doing Default FCFS")
        mode = "fcfs"
    connect(host, port, mode, timeQuantum)
