Xem payload của các gói đầu và mấy gói sau đó thấy nó giống nhau, đều gửi đi cùng 1 thông điệp.

### C1:

Ở cửa sổ giữa, tìm đến phần dữ liệu thô: `Chuột phải -> Apply as Column`

Lúc này màn hình chính hiển thị nội dung trực tiếp của tất cả các gói tin giúp ta cuộn nhanh để thấy toàn bộ nội dung của hàng trăm gói tin thay đổi ra sao.

<img width="3037" height="1380" alt="image" src="https://github.com/user-attachments/assets/cd551f2f-ea86-440c-91f2-9c6fc29e8e92" />

### C2:

`Ctrl + F (Edit -> Find Packet...)`

Một thanh công cụ nhỏ xuất hiện dưới thanh filter.
```
Ô 1 (display filter): chuyển thành Packet bytes (để nó tìm trong nội dung payload thô).
Ô 2 (Narrow & Wide): giữ nguyên.
Ô 3 (Hex value): chuyển thành String.
```

<img width="3030" height="1533" alt="image" src="https://github.com/user-attachments/assets/d7200a23-aeb3-42ff-b0a1-de60936f7206" />
### C3:

Trích xuất toàn bộ nội dung ra file text để soi trên Notepad: `File -> Export Packet Dissections -> As Plain Text ...`

Mở Notepad, đổi 'pico' sang dạng hex rồi Ctrl F tìm.

<img width="2562" height="1474" alt="image" src="https://github.com/user-attachments/assets/5db2ada8-3817-4dc8-b95e-e670d15baa55" />

Flag: picoCTF{P64P_4N4L7S1S_SU55355FUL_f621fa37}
