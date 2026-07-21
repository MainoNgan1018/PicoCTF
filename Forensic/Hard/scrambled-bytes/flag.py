import random
from scapy.all import rdpcap, IP, UDP, Raw

# Load packets from the capture file
packets = rdpcap('capture.pcapng')

payload_packets = []
arrival_time = None

for packet in packets:
    # Kiểm tra xem gói tin có đủ lớp IP, UDP và Raw hay không
    if packet.haslayer(IP) and packet.haslayer(UDP) and packet.haslayer(Raw):
        if arrival_time is None:
            arrival_time = int(packet.time)
        payload_packets.append(packet[Raw].load[0])

# Seed Python's random with the transmission time
random.seed(int(arrival_time))

# Re-create the shuffle mapping/control array
control = list(range(len(payload_packets)))
random.shuffle(control)

decoded = bytearray(len(payload_packets))

for i in range(len(payload_packets)):
    port = random.randrange(65536)  # Advance the PRNG state identically to send.py
    xor_val = random.randrange(256)
    decoded[control[i]] = payload_packets[i] ^ xor_val

# Write the recovered file out (often a PNG image containing the flag)
with open('decoded_flag.png', 'wb') as f:
    f.write(decoded)