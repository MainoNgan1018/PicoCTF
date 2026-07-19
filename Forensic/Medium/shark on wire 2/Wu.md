Sau khi follow Stream thì tôi thấy rất nhiều cụm pico nhưng tất cả chỉ là thông tin nhiễu.

Và khi đến gói này bắt đầu xuất hiện chữ `start` và `end`. Các gói tin giữa 2 gói này đều chứa các chuỗi linh tinh không có gì.

<img width="1787" height="615" alt="image" src="https://github.com/user-attachments/assets/4ca611c1-ac4c-4a48-ba62-3c637ef375ac" />
<img width="1905" height="575" alt="image" src="https://github.com/user-attachments/assets/360c5f26-096e-4ef6-9bb6-3778f8b976b9" />

2 gói này từ các ip nguồn khác nhau nhưng ip đích đều là `10.0.0.1`, ta sẽ filter theo ip và giao thức `udp`:

<img width="2865" height="1200" alt="image" src="https://github.com/user-attachments/assets/0b7e06aa-91bc-4cfd-bafe-c70dac8f9d83" />

Nhìn vào port đích là 22 và các port nguồn không cố định, khi lấy port nguồn -5000 chuyển sang kí tự ở bảng mã ASCII thì dần lộ ra định dạng cờ.

Nhờ AI viết script lọc từ gói 1104 đến 1303, 2 gói chứa `start` và `end`.

Script Python:
```bash
from scapy.all import rdpcap, UDP

# Đọc tệp pcap
packets = rdpcap('capture_2.pcap')

flag = ""

# Lặp qua các gói tin
for pkt in packets:
    # Kiểm tra gói tin có giao thức UDP và cổng đích là 22
    if UDP in pkt and pkt[UDP].dport == 22:
        # Lấy cổng nguồn (src port)
        src_port = pkt[UDP].sport
        
        # Chỉ lấy các gói tin có cổng nguồn > 5000 (dựa trên logic của bạn)
        if src_port > 5000:
            # Thực hiện phép tính trừ 5000 và chuyển sang ký tự ASCII
            char_code = src_port - 5000
            flag += chr(char_code)

print("Flag của bạn là:", flag)
```
**Chú ý:** trước khi run ta phải cài thư viện bằng lệnh `pip install scapy`(tạo 1 môi trường ảo rồi cài trên đó nếu gặp lỗi).

<img width="2000" height="132" alt="image" src="https://github.com/user-attachments/assets/f995e7c0-b67a-48fa-bcc2-1614055c3e4f" />

Flag: picoCTF{p1LLf3r3d_data_v1a_st3g0}
