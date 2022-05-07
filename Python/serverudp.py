#!/usr/bin/env python3
import socket
import sys

# Connection config
HOST = "127.0.0.1"
PORT = 2000

# Update HOST
if (len(sys.argv) == 2):
    HOST = sys.argv[1]
if (len(sys.argv) == 3):
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
print(f"Selected: -> {HOST}:{PORT}")

# Create a UDP socket at server side
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as s:
    buffer_size = 1024
    s.bind((HOST, PORT))
    print("UDP server ready")
    # Manage message
    while(True):
        # Get message and address
        data, client = s.recvfrom(buffer_size)
        message = data.decode()
        clientAddr, clientPort = client
        print(f"[{clientAddr}:{clientPort}]: {message}")
        # Send responde
        s.sendto(message.encode(), client)
        # Check close message
        if message == "close":
            print("Server closed")
            break