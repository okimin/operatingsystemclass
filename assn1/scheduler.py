#! /usr/local/bin/python3

'''
    Client - calls server, opens file, sends server data line by line.
'''


import socket
import queue

class PCB:
  def __init__(self, procName, PID, state, priority,interruptable, est_total_run_time, est_remaining_run_time):
    self.procName = procName
    self.PID = PID
    self.state=state
    self.priority=priority
    self.interruptable= interruptable
    self.est_total_run_time= est_total_run_time
    self.est_remaining_run_time= est_remaining_run_time
    


def connect(host, port):

    with open('processes.txt', 'rt') as infile:
        lines = infile.read().split('\n')
        processes= queue.Queue(maxsize=7)


    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((host, port))
        print('Connected to %s:%s' % (host, port))

        for line in lines[:-1]:
            processes.put(line)

        while(processes.qsize() > 0) :
            # send the item next in queue
            send = processes.get()
            print('Sending:\t%s' % send)
            sock.send(send.encode('utf-8'))

            data = sock.recv(1024)
            print('Received:\t%s' % data.decode())
            check = data.decode().split(',')[-1]
            #print(check)

            if not int(check)<=0:
                processes.put(data.decode())
            

    print('Finished, connection closed.')


if __name__ == '__main__':

    host = '127.0.0.1'
    port = 9000

    connect(host, port)