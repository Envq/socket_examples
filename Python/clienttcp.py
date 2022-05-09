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
    s.settimeout(10)
    buffer_size = 1024
    print("TCP client ready")
    s.connect((HOST, PORT))
    print(f"TCP client connected to server {HOST}:{PORT}")
    # Listen for incoming data from User
    while(True):
        message = input("Send messagge: ")
        data = message.encode()
        s.send(data)
        # Check close message
        if message == "close" or message == "closeall":
            print("Client closed")
            break
        # Get only message
        reply = s.recv(buffer_size)
        print(f"> {reply.decode()}")