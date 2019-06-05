#! /usr/local/bin/python3

'''
    CPU_EMULATOR 
'''


import socket


def listen(host, port):

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
                
                    decode= data.decode().split(',')
                    newCycle= int(decode[-1])-200
                    # if (newCycle<=0)
                    #     newCycle=0
                    decode[-1]= str(newCycle)
                    data = ','.join(decode)
                    #print(data)
                    conn.send(data.encode('utf-8'))
                

            print('Connection closed to:', addr)


if __name__ == '__main__':

    host = '127.0.0.1'
    port = 9000

    listen(host, port)