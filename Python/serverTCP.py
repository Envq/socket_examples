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
print(f"Selected: -> {HOST}:{PORT}")

# Create a TCP socket at server side
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    buffer_size = 1024
    s.bind((HOST, PORT))
    s.listen() # enable to accept connection
    print("TCP server ready")
    # Wait connection
    conn, client = s.accept()
    clientAddr, clientPort = client
    print("TCP server connected to client {}:{}".format(clientAddr, clientPort))
    with conn:
        while (True):
            # Get only message
            data = conn.recv(1024)
            message = data.decode()
            print(f"[{clientAddr}:{clientPort}]: {message}")
            # Send responde
            conn.send(message.encode())
            # Check close message
            if message == "close":
                print("Server closed")
                break