Đầu tiên ta cần biết:

BitLocker là tính năng mã hóa toàn bộ ổ đĩa được tích hợp sẵn trên các hệ điều hành Windows (phản ứng với phiên bản Pro, Enterprise và Education). Nó hoạt động như một "két sắt" kỹ thuật số, bảo vệ mọi dữ liệu trên máy tính khỏi việc bị đánh cắp hoặc truy cập trái phép ngay cả khi ổ cứng bị tháo rời.

Đến với bài này, xem qua dữ liệu thô trên FTK:

<img width="3480" height="1750" alt="Screenshot 2026-07-14 093105" src="https://github.com/user-attachments/assets/b7b41941-aec5-47bf-b45b-b30c62d9b0cb" />

<img width="2255" height="397" alt="image" src="https://github.com/user-attachments/assets/3dc4ea45-847e-465a-98d8-ed92056f33c5" />

Ta thấy chuỗi kí tự -FVE-FS-. Đây chính là chữ ký (signature) của Full Volume Encryption File System, tức là BitLocker.

FTK báo "Unrecognized file system" vì toàn bộ phân vùng đã bị mã hóa FTK không thể đọc được cấu trúc bảng file, ngay cả `mmls` cũng không liệt kê được.

Công cụ quan trọng nhất `dislocker`. Đây là công cụ chuẩn trên Linux để đọc các phân vùng đã mã hóa BitLocker.

Vì đề bài nhấn mạnh vào "simple password" nên ta sẽ sử dụng `Hashcat` hoặc `John the Ripper` .

# Bước 1: ta sẽ trích xuất hash của BitLocker

**Tải script từ GitHub của John the Ripper**
```
wget https://raw.githubusercontent.com/magnumripper/JohnTheRipper/bleeding-jumbo/run/bitlocker2john.py
```
**Sau đó chạy lệnh trích xuất hash như bình thường**
```
python3 bitlocker2john.py bitlocker-1.dd > bitlocker_hash.txt
```
**Mở file bitlocker_hash.txt bằng lệnh `cat bitlocker_hash.txt`**
```
mainosenpai@DESKTOP-E956SQ4:/mnt/c/Users/ADMIN/Downloads$ cat bitlocker_hash.txt
$bitlocker$2$16$2b71884a0ef66f0b9de049a82a39d15b$1048576$12$00be8a46ead6da0106000000$60$a28f1a60db3e3fe4049a821c3aea5e4ba1957baea68cd29488c0f3f6efcd4689e43f8ba3120a33048b2ef2c9702e298e4c260743126ec8bd29bc6d58
$bitlocker$3$16$2b71884a0ef66f0b9de049a82a39d15b$1048576$12$00be8a46ead6da0106000000$60$a28f1a60db3e3fe4049a821c3aea5e4ba1957baea68cd29488c0f3f6efcd4689e43f8ba3120a33048b2ef2c9702e298e4c260743126ec8bd29bc6d58
$bitlocker$0$16$cb4809fe9628471a411f8380e0f668db$1048576$12$d04d9c58eed6da010a000000$60$68156e51e53f0a01c076a32ba2b2999afffce8530fbe5d84b4c19ac71f6c79375b87d40c2d871ed2b7b5559d71ba31b6779c6f41412fd6869442d66d
$bitlocker$1$16$cb4809fe9628471a411f8380e0f668db$1048576$12$d04d9c58eed6da010a000000$60$68156e51e53f0a01c076a32ba2b2999afffce8530fbe5d84b4c19ac71f6c79375b87d40c2d871ed2b7b5559d71ba31b6779c6f41412fd6869442d66d
$bitlocker$2$16$2b71884a0ef66f0b9de049a82a39d15b$1048576$12$00be8a46ead6da0106000000$60$a28f1a60db3e3fe4049a821c3aea5e4ba1957baea68cd29488c0f3f6efcd4689e43f8ba3120a33048b2ef2c9702e298e4c260743126ec8bd29bc6d58
$bitlocker$3$16$2b71884a0ef66f0b9de049a82a39d15b$1048576$12$00be8a46ead6da0106000000$60$a28f1a60db3e3fe4049a821c3aea5e4ba1957baea68cd29488c0f3f6efcd4689e43f8ba3120a33048b2ef2c9702e298e4c260743126ec8bd29bc6d58
$bitlocker$0$16$cb4809fe9628471a411f8380e0f668db$1048576$12$d04d9c58eed6da010a000000$60$68156e51e53f0a01c076a32ba2b2999afffce8530fbe5d84b4c19ac71f6c79375b87d40c2d871ed2b7b5559d71ba31b6779c6f41412fd6869442d66d
$bitlocker$1$16$cb4809fe9628471a411f8380e0f668db$1048576$12$d04d9c58eed6da010a000000$60$68156e51e53f0a01c076a32ba2b2999afffce8530fbe5d84b4c19ac71f6c79375b87d40c2d871ed2b7b5559d71ba31b6779c6f41412fd6869442d66d
```
Vì có nhiều dòng hash khác và còn bị lặp nên khi dùng hashcat nó không hiểu được hết dù vẫn chạy được và nếu chạy hết mà không ra thì có khả năng nó chưa chạy đúng trên cái hash chính xác.

Nên ta chỉ để lại 1 dòng duy nhất để Hashcar không bị phân tâm và lỗi trong quá trình phân tích.

Ta cần mở file bitlocker_hash.txt bằng lệnh `nano bitlocker_hash.txt`.

Xóa hết các dòng chỉ để lại đúng 1 dòng (dài nhất và có cấu trúc $bitlocker$0$16$). Đây là chân dung duy nhất và chính xác nhất của ổ đĩa và thường là dòng đại diện cho Password.

# Bước 2: Bẻ khóa (Crack) mật khẩu

Ta dùng Rockyou.txt. Đây là một file văn bản chứa danh sách hàng chục triệu mật khẩu thực tế từng bị lộ trong các vụ hack.

**Tải file nén trực tiếp từ kho Kali:**
```
wget https://gitlab.com/kalilinux/packages/wordlists/-/raw/kali/master/rockyou.txt.gz
```
**Giải nén:**
```
gunzip rockyou.txt.gz
```
**Sau đó dùng `Hashcat` với file rockyou.txt:**
```
hashcat -m 22100 -w 3 bitlocker_hash.txt rockyou.txt
```

<img width="1442" height="77" alt="image" src="https://github.com/user-attachments/assets/7adf0838-f395-4ce3-a974-2e1c17a97235" />

Chạy lệnh và bấm s định kì để kiểm tra xem nó đã tìm thấy mật khẩu chưa (Recovered: 1/1) 

[s]tatus: Gõ s để xem tốc độ bẻ khóa hiện tại, mật khẩu đã thử được bao nhiêu phần trăm, và thời gian dự kiến hoàn thành. 

<img width="2767" height="1125" alt="image" src="https://github.com/user-attachments/assets/4b37e195-1de6-482c-a725-0e452b82ed15" />

Dòng chữ Recovered: 1/1 và mật khẩu hiển thị ngay phía sau dấu hai chấm chính là mật khẩu : jacqueline.
 
# Bước 3: Giải mã bằng dislocker
**Tạo thư mục mount trong thư mục home của bạn (để tránh lỗi quyền trên /mnt/)**
```
mkdir -p ~/bitlocker_mount
```
**Chạy lệnh dislocker và  nhập mật khẩu:**
```
dislocker -V bitlocker-1.dd -u -- ~/bitlocker_mount
```
**Dùng 7z để mở các file ảnh đĩa mà không cần mount qua loop device:**

Cài đặt:
```
sudo apt update
sudo apt install p7zip-full
```

Liệt kê nội dung file đã giải mã:
```
7z l ~/bitlocker_mount/dislocker-file
```

Mở file flag.txt:

<img width="1617" height="497" alt="image" src="https://github.com/user-attachments/assets/847cfdb0-8e30-4417-975a-0ce440780f13" />

Flag: picoCTF{us3_b3tt3r_p4ssw0rd5_pl5!_3242adb1}
