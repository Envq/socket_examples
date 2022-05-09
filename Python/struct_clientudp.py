#!/usr/bin/env python3
import socket
import sys
import struct

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
    s.settimeout(10)
    buffer_size = 1024
    print("UDP client ready")
    while(True):
        # listen for incoming data from User
        message = int(input("Send unsigned int: "))
        request = struct.pack('!II', message, 130)
        # send request
        s.sendto(request, (HOST, PORT))
        # check close message
        if message == 42:
            print("Client closed")
            break
        # get only reply
        rawdata = s.recv(buffer_size)
        data = struct.unpack('!iiiiii', rawdata)
        # process reply
        print(f"> {data}")