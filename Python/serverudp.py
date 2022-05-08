#!/usr/bin/env python3
import socket
import sys

# settings
HOST = "127.0.0.1"
PORT = 2000

# update HOST
if (len(sys.argv) == 2):
    HOST = sys.argv[1]
if (len(sys.argv) == 3):
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
print(f"Selected: -> {HOST}:{PORT}")

# create a UDP socket at server side
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as s:
    buffer_size = 1024
    s.bind((HOST, PORT))
    print("UDP server ready")
    # manage message
    while(True):
        # get response and address
        data, client = s.recvfrom(buffer_size)
        message = data.decode()
        clientAddr, clientPort = client
        # process request
        print(f"[{clientAddr}:{clientPort}]: {message}")
        if message == "close":
            print("Server closed")
            break
        # send reply
        s.sendto(message.encode(), client)