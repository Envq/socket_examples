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

# Create a UDP socket at client side
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as s:
    buffer_size = 1024
    print("UDP client ready")
    # Listen for incoming data from User
    while(True):
        message = input("Send messagge: ")
        data = message.encode()
        s.sendto(data, (HOST, PORT))
        # Check close message
        if message == "close":
            print("Client closed")
            break
        # Get only message
        response = s.recv(buffer_size)
        print(f"> {response.decode()}")