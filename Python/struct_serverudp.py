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

# create a UDP socket at server side
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as s:
    buffer_size = 1024
    s.bind((HOST, PORT))
    print("UDP server ready")
    # manage message
    while(True):
        # get response and address
        rawdata, client = s.recvfrom(buffer_size)
        clientAddr, clientPort = client
        data = struct.unpack('!II', rawdata)
        # process request
        print(f"[{clientAddr}:{clientPort}]: {data}")
        if data[0] == 42:
            print("Server closed")
            break
        # send reply
        reply = struct.pack('!iiiiii', 0, 0, 0, 0, 0, 0)
        s.sendto(reply, client)
