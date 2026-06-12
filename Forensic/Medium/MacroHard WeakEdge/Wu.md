Mở file PowerPoint không mở được nên ta soi HxD.

<img width="1570" height="1698" alt="image" src="https://github.com/user-attachments/assets/64ad2b44-d27a-44d4-a22e-13019ac1490d" />

Ta thấy:

* Byte đầu chuẩn Zip `50 4B 03 04` (PK..)

* Nhưng ngay từ offset 00000040 đổ đi cho đến tận 00000150... toàn bộ dữ liệu bị ghi đè bằng một loạt byte 00

**Đây chỉnh là khu vực _Local File Header_ bắt buộc phải có các trường cố định:**

- Magic bytes: 50 4B 03 04 (Chuẩn)

- Kích thước file nén (Compressed Size)

- Kích thước file thực tế (Uncompressed Size)

- Độ dài tên file (Filename Length)

-> Các thông số này đã bị xóa sạch và bị đè một đống byte 00 -> Cấu trúc gãy -> File Corrupt
  
### Sơ đồ cấu trúc của một file .pptm (ZIP Format)
```
  +-------------------------------------------------------------+
| [1] LOCAL FILE HEADER 1 (Magic: 50 4B 03 04)                |
|     - Thông số: Kích thước, tên file ([Content_Types].xml)  |
+-------------------------------------------------------------+ <--- Bạn bị chèn '00' ở vùng thông số này làm gãy file
|     - DỮ LIỆU NÉN THỰC SỰ của file [Content_Types].xml      |
+-------------------------------------------------------------+
| [2] LOCAL FILE HEADER 2 (Magic: 50 4B 03 04)                |
|     - Tên file: ppt/presentation.xml                        |
|     - DỮ LIỆU NÉN THỰC SỰ của presentation.xml             |
+-------------------------------------------------------------+
| ... (Lặp lại cho hàng trăm file slide, media, vbaProject)   |
+-------------------------------------------------------------+
| [3] CENTRAL DIRECTORY (Mục lục trung tâm)                   |
|     (Mỗi file bên trên sẽ có 1 dòng tương ứng ở đây)        |
|     - Magic: 50 4B 01 02                                    |
|     - Chứa pointer (con trỏ) trỏ ngược về các Header [1][2] |
+-------------------------------------------------------------+
| [4] END OF CENTRAL DIRECTORY (EOCD - Kết thúc mục lục)      |
|     - Magic: 50 4B 05 06                                    |
|     - Lưu tổng số file và vị trí bắt đầu của vùng Mục lục [3]|
+-------------------------------------------------------------+ <--- Vị trí kết thúc file ZIP chuẩn hợp lệ
| [5] OVERLAY DATA (Vùng dữ liệu thừa / Giấu tin độc lập)     |
|     - Ký tự lạ, chuỗi mã hóa, hoặc file ZIP thứ 2 ẩn giấu   |
+-------------------------------------------------------------+ <--- Đuôi file thực tế trong bài CTF của bạn
```
### Các phần phải cố định đúng quy chuẩn 

***1.Các Magic Bytes (Signatures):***

* Đầu mỗi file con: 50 4B 03 04

* Đầu mỗi mục trong thư mục chính: 50 4B 01 02

* Kết thúc file: 50 4B 05 06

***2.Vùng thông số kích thước (Sizes & Offsets)***

### Phần có thể nhét ké dữ liệu (giấu cờ)

1- Giấu sau đuôi file

2- Trường thông tin mở rộng (Extra Field) trong các Header

3- Tên file hoặc Comment của file zip

4- Tạo ra một file XML "rác" không được khai báo trong `[Content_Types].xml`

<img width="694" height="457" alt="image" src="https://github.com/user-attachments/assets/d46727fc-4ad0-43f3-a6d4-9204e264eaf2" />

Xuống cuối ta thấy có khá nhiều file được nén trong này và đường dẫn `ppt/slideMasters/hidden` sau đó là kết thúc file `End of Central Directory` thông thường dài 22 bytes

Binwalk để kiểm tra nội dung bên trong:

<img width="1161" height="271" alt="image" src="https://github.com/user-attachments/assets/6f30aafb-8323-41a7-b043-533a7fb4bfa1" />

Vào file `hidden` thì ta thấy một chuỗi bị tách rời khả nghi:

<img width="874" height="322" alt="image" src="https://github.com/user-attachments/assets/4c3fd5b5-7eb9-48b9-9b1e-8591145e272b" />

Xóa các dấu cách đi ta có:

Chuỗi có độ dài 50 ký tự.

```
ZmxhZzogcGljb0NURntEMWRfV9rbjB3X3BwdHNfc196MXA1fQ
```

Nếu decode `base64 -d` như bình thường thì sẽ ra `invalid input` vì trong toán học mã hóa Base64, chuỗi hợp lệ phải có độ dài là bội số của 4.

Ta phải thêm option -i (--ignore-garbage) để nó tự động bỏ qua các kí tự lỗi hoặc thiếu padding ở cuối.

Option -n của echo có nghĩa không được thêm kí tự "\n" mà hệ điều hành sẽ tự động chèn nếu không có -n.

<img width="1166" height="50" alt="image" src="https://github.com/user-attachments/assets/d5fe2aa5-a5de-4209-8f6e-8fb57857e2b3" />

Flag: picoCTF{D1d_u_kn0w_ppts_r_z1p5}
