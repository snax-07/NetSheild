import socket

HOST = "127.0.0.1"
PORT = 8080

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

print(f"Listening on {HOST}:{PORT}...")

while True:
    data, address = sock.recvfrom(4096)

    print(f"\nReceived {len(data)} bytes from {address}"  , "\n")

    # Raw bytes
    print("Raw bytes:", data , "\n")

    # Hex representation
    print("Hex:", data.hex() , "\n")

    # Try to interpret bytes as text
    try:
        message = data.decode("utf-8")
        print("Message:", message ,  "\n")
    except UnicodeDecodeError:
        print("Message: <binary data - cannot decode as UTF-8>")