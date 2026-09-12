import socket
import time
import threading
import json

recv_nav_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
recv_nav_sock.bind(("0.0.0.0", 9001))
recv_nav_sock.settimeout(1.0)

recv_extrap_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
recv_extrap_sock.bind(("0.0.0.0", 9002))
recv_extrap_sock.settimeout(1.0)

send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

running = True

def listen_nav():
    print("[*] Mendengarkan Data Navigasi Gabungan di Port 9001...")
    while running:
        try:
            data, addr = recv_nav_sock.recvfrom(1024)
            print(f"\n[NAVIGASI 9001] {data.decode()}")
        except socket.timeout:
            continue

def listen_extrap():
    print("[*] Mendengarkan Data Ekstrapolasi di Port 9002...")
    while running:
        try:
            data, addr = recv_extrap_sock.recvfrom(1024)
            print(f"\n[EKSTRAPOLASI 9002] {data.decode()}")
        except socket.timeout:
            continue
        
t1 = threading.Thread(target=listen_nav)
t2 = threading.Thread(target=listen_extrap)
t1.start()
t2.start()

print("Mulai mengirim data sensor mock ke port 8080 setiap 1 detik...")
print("Tekan Ctrl+C untuk berhenti.\n")

mock_sentences = [
    b"$GP,4807.038,N,01131.000,E*2E",
    b"$HE,123.456,T*70",
    b"$VE,5.5,K,3.0,N,123.45,T*5E"
]

idx = 0
try:
    while True:
        sentence = mock_sentences[idx % len(mock_sentences)]
        print(f"[SENSOR -> 8080] Mengirim: {sentence.decode()}")
        send_sock.sendto(sentence, ("127.0.0.1", 8080))
        idx += 1
        time.sleep(1)
except KeyboardInterrupt:
    print("\nBerhenti...")
    running = False

t1.join()
t2.join()
recv_nav_sock.close()
recv_extrap_sock.close()
send_sock.close()
