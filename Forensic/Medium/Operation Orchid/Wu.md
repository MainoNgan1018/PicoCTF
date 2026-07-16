Vào Wireshark, sau đó `Follow TCP Stream` để xem cuộc hội thoại.

<img width="1940" height="1580" alt="image" src="https://github.com/user-attachments/assets/6a60c78a-64bd-4887-8492-f08bc9781eec" />

Cuộc trò chuyện trong luồng TCP cho thấy người dùng đã gửi một file có tên là file.des3 kèm mật khẩu.

Và file đó được truyền qua cổng 9002 nên ta sẽ filter theo cổng này:
```
tcp.port == 9002
```

<img width="2867" height="1465" alt="image" src="https://github.com/user-attachments/assets/56f5d380-862f-4212-83bb-13467a929787" />
Xem các gói thì thấy gói có nội dung : Salt...
<img width="2872" height="700" alt="image" src="https://github.com/user-attachments/assets/aac90b45-36af-446f-ae44-5ab7840b84a0" />
Đây chính là gói ta cần export.

>Chuột phải vào phần dữ liệu -> Export Packet Bytes.. -> Lưu với tên file.des3

Dùng lệnh giải mã như trong đoạn chat:
```
openssl des3 -d -salt -in file.des3 -out file.txt -k supersecretpassword123
```
<img width="2810" height="242" alt="image" src="https://github.com/user-attachments/assets/7756f08b-4baf-4885-a180-7afba8477d04" />

Flag: picoCTF{nc_73115_411_dd54ab67}
