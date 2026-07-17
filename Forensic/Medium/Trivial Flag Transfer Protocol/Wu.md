TFTP truyền file bằng cách chia nhỏ thành các khối dữ liệu (Blocks), như ta thấy trong cột "Info" của Wireshark (Data Packet, Block: 23295, v.v.).

<img width="2772" height="1272" alt="image" src="https://github.com/user-attachments/assets/57b9bd8b-df7e-4958-b11a-18f678fdfae9" />

Ta sử dụng tính năng Export Objects của Wireshark để khôi phục toàn bộ các file đã được truyền qua giao thức TFTP này.

```
File -> Export Objects -> TFTP -> Save all.
```

<img width="1855" height="1360" alt="image" src="https://github.com/user-attachments/assets/396b5507-57c8-4185-9475-0b815a0ebbbb" />

Sau khi trích xuất ta có 3 file ảnh, 1 file program.deb và 1 file plan chữa chuỗi mã hóa ROT13 (một dạng Caesar cipher với độ dịch chuyển là 13).
```
VHFRQGURCEBTENZNAQUVQVGJVGU-QHRQVYVTRAPR.PURPXBHGGURCUBGBF
```

Cho lên CyberChef với recipe `ROT13`:

<img width="2282" height="1295" alt="image" src="https://github.com/user-attachments/assets/75253f0d-28df-438d-918d-fa8b5540c07a" />

Nội dung giải mã : `I USED THE PROGRAM AND HID IT WITH- DUEDILIGENCE`

Mật khẩu `DUEDILIGENCE` để ta giải mã dữ liệu ẩn trong các file ảnh bằng công cụ ẩn giấu (Steganography) như Steghide.

<img width="2565" height="285" alt="image" src="https://github.com/user-attachments/assets/6501799a-08c5-4abc-8437-1b5e4032c3bb" />

Kết quả trích xuất được file flag.txt từ ảnh số 3.

picoCTF{h1dd3n_1n_pLa1n_51GHT_18375919}
