#! /usr/local/bin/python3

'''
    CPU_EMULATOR 
'''


import socket
import sys


def listen(host, port, timeQuantum):

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind((host, port))
        sock.listen()

        print('Listening on %s:%s' % (host, port))

        conn, addr = sock.accept()

        with conn:
            print('Connection from:', addr)

            while True:
                data = conn.recv(1024)

                if not data:
                    break
                else:

                    decode = data.decode().split(',')
                    if timeQuantum == 0:
                        timeQuantum = int(decode[-1])
                        newCycle = int(decode[-1])-timeQuantum
                        timeQuantum = 0
                    else:
                        newCycle = int(decode[-1])-timeQuantum

                    if (newCycle <= 0):
                        newCycle = 0
                    decode[-1] = str(newCycle)
                    data = ','.join(decode)
                    conn.send(data.encode('utf-8'))

            print('Connection closed to:', addr)


if __name__ == '__main__':

    host = '127.0.0.1'
    port = 9000
    tq = 0
    if len(sys.argv) == 2:
        tq = int(sys.argv[1])
    else:
        print("No Input So Process Will Run Till DONE")
    listen(host, port, tq)
