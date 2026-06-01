Nhìn tổng quan ta có thể thấy được từ

Dòng 3-10:

* Truy vấn DNS: tìm tên miền có dạng device-..
* Ngay sau là yêu cầu HTTP GET
* Các ip nội bộ khác nhau 10.100.x.x cùng thực hiện
  
Dòng 17-18:

Sau khi đăng kí thành công thiết bị 10.100.50.122 thực hiện lệnh POST/ upload (dấu hiệu của việc đánh cắp dữ liệu hoặc gửi báo cáo trạng thái từ máy nạn nhân -> máy tấn công).

<img width="1017" height="397" alt="image13" src="https://github.com/user-attachments/assets/9da009b0-f5e6-4c28-9904-2f39ac94233b" />

Xuống những gói POST/upload ta thấy mỗi gói đều có một chuỗi kí tự lạ.

<img width="1440" height="410" alt="image19" src="https://github.com/user-attachments/assets/0085b0d5-31ae-4283-982f-5f4217a2a294" />

Ghép vào ta được ciphertext hoàn chỉnh mang đặc trưng của định dạng base64:
```
QFFWWnZjfkxCCFJABmhbBFxUakEFQAtFb1xXVgEHAAQBRQ==
```

Theo Reveal hint 3 thì ta biết được key của thuật toán mã hóa XOR là mã IMSI của thiết bị nạn nhân.

Trạm giả trong kịch bản này đang gửi các gói tin UDP Port 55000 tới địa chỉ Broadcast nên bất kì thiết bị nào phản hồi hoặc kết nối thì đó chính là thiết bị đã bị lừa.

Trước đó tấn công các ip khác không được nhưng đến gói 16 đã được nên thiết bị này chính là nạn nhân → ta cần lấy IMSI của thiết bị này làm key chứ không phải bất kì IMSI của thiết bị khác.

<img width="860" height="207" alt="image14" src="https://github.com/user-attachments/assets/0bb9b8cf-a419-4ab2-a20a-7d2126edecb6" />

### Cấu trúc của một mã IMSI tiêu chuẩn

```
MCC (mobile country code) : 3 số đầu (310 là của Mỹ)
MNC (mobile network code) : 2 hoặc 3 chữ số tiếp theo ( 410 là mạng AT&T)
MSIN (mobile subscription identification number): dãy còn lại để định danh duy nhất người dùng mạng đó
```

Để nguyên mã ISMI thì nó ra một chuỗi vô nghĩa nhưng dạng gần đúng , ta xóa từng chữ số của key và sau khi xóa 6 số đầu còn lại là phần MSIN.

<img width="1999" height="982" alt="image18" src="https://github.com/user-attachments/assets/2ad10318-a95f-4b00-b27a-5f57cf930c6d" />

Flag: picoCTF{r0gu3_c31l_t0w3r_dbc40831}
