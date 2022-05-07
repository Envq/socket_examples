#!/usr/bin/env python3
import socket
import sys

# Connection config
HOST = "127.0.0.1"
PORT = 2001

# Update HOST
if (len(sys.argv) == 2):
    HOST = sys.argv[1]
if (len(sys.argv) == 3):
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
print("Selected: -> {}:{}".format(HOST,PORT))

# Create a TCP socket at client side
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    buffer_size = 1024
    print("TCP client ready")
    s.connect((HOST, PORT))
    print(f"TCP client connected to server {HOST}:{PORT}")
    # Listen for incoming data from User
    while(True):
        message = input("Send messagge: ")
        data = message.encode()
        s.send(data)
        # Get only message
        response = s.recv(buffer_size)
        print(f"> {response.decode()}")
        # Check close message
        if message == "close":
            print("Client closed")
            break