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

# create a UDP socket at client side
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as s:
    buffer_size = 1024
    print("UDP client ready")
    while(True):
        # listen for incoming data from User
        message = input("Send messagge: ")
        data = message.encode()
        # send request
        s.sendto(data, (HOST, PORT))
        # check close message
        if message == "close":
            print("Client closed")
            break
        # get only reply
        response = s.recv(buffer_size)
        # process reply
        print(f"> {response.decode()}")