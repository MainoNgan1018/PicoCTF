Quan sát 'Conservation' của file shark1.pcapng:

<img width="2593" height="574" alt="image" src="https://github.com/user-attachments/assets/882fd844-e108-4cc0-88bb-e4c86d00f59f" />

Ta có thể thấy giao thức chiếm nhiều dữ liệu nhất là HTTP (Hypertext Transfer Protocol) với 152,220 Bytes (tương đương khoảng 75.6% tổng số lượng Bytes của toàn bộ file capture).

<img width="2419" height="1025" alt="image" src="https://github.com/user-attachments/assets/1132449d-0d34-422e-bd17-86509cfd822a" />

### 1. Lọc theo HTTP

Ta thấy liên tục là một vòng lặp máy .104 gửi yêu cầu HTTP POST đến máy .103 và máy .103 phản hồi lại bằng dữ liệu mã hóa Kerberos (http-kerberos-session-encrypted).  

<img width="3028" height="1265" alt="image" src="https://github.com/user-attachments/assets/dab0c1ab-4032-470d-8e8b-81a62269894d" />

Nhưng tới gói tin thứ 962, máy .104 gửi gói tin HTTP GET tới địa chỉ 169.254.169.254 và lần này gói tin gửi lại không bị mã hóa.

<img width="3017" height="1139" alt="image" src="https://github.com/user-attachments/assets/4121ca5a-44e7-4248-9de0-8942e66824af" />

### 2. Xem toàn bộ cuộc trò chuyện

`Chuột phải -> Follow -> HTTP Stream`

Và ta thấy đoạn mã rot13 (là một thuật toán mã hóa thay thế cực kỳ đơn giản, hoạt động bằng cách dịch chuyển mỗi chữ cái trong bảng chữ cái tiến lên 13 vị trí)
```
Gur synt vf cvpbPGS{c33xno00_1_f33_h_qrnqorrs}
```

<img width="1942" height="1150" alt="Screenshot 2026-06-08 105550" src="https://github.com/user-attachments/assets/c0312f43-a77c-4c4f-be19-82b1ba516f67" />

### 3. Giải mã rot13

<img width="2656" height="1552" alt="Screenshot 2026-06-08 105603" src="https://github.com/user-attachments/assets/6c9410ab-bb91-4c39-8d27-c38b840f13f8" />

Flag: picoCTF{p33kab00_1_s33_u_deadbeef}
