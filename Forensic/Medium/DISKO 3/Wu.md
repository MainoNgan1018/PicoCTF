### Cách 1: Sử dụng công cụ giao diện trực quan Autopsy.

Dùng tính năng `Keyword Search` để tìm kiếm cụm "picoCTF":

<img width="523" height="414" alt="image" src="https://github.com/user-attachments/assets/4684f497-884b-4f05-9bbe-89a46f6129b1" />

Kết quả:

<img width="1544" height="887" alt="image" src="https://github.com/user-attachments/assets/0fbf5541-2e3b-4873-8fd6-8710885ec2c4" />

### Cách 2: Sử dụng bộ công cụ mã nguồn mở Sleuth Kit

Xem phân vùng:
```
mmls disko-3.dd
```
Kiểm tra định dạng thực sự của file:
```
file disko-3.dd
```
Kết quả:
<img width="1162" height="74" alt="image" src="https://github.com/user-attachments/assets/41b3f90d-2e9c-44ab-809d-441de3c731d8" />

Lệnh mmls hệ thống trả về trống rỗng, điều này chứng minh file .dd không có bảng phân vùng và nó là một phân vùng đơn lẻ.

Và nó là một phân vùng FAT32 mà lệnh file đã chỉ ra.

Thử lọc bằng strings + grep (tham số -i để tìm không phân biệt chữ hoa chữ thường) và kết quả là không có gì đặc biệt.
<img width="1157" height="324" alt="image" src="https://github.com/user-attachments/assets/970e2324-38f3-4578-b8b3-27a941cfd24c" />

Liệt kê các tên tệp tin và thư mục:
Command:
```
fls -r -p disko-3.dd
```
<ins>Các option để lọc các file</ins> (nếu không thêm tham số , fls sẽ hiện cả file đang tồn tại và bị xóa):

  **-d**: chỉ hiển thị các file và thư mục đã bị xóa.
  
  **-u**: chỉ hiển thị các file đang tồn tại trên ổ đĩa (chưa từng bị xóa).
  
  **-r**: quét đệ quy, tức động chui vào tất cả các thư mục con bên trong ổ đĩa để liệt kê hết toàn bộ file từ trong ra ngoài.
  
  **-p**: hiển thị đường dẫn đầy đủ của file tính từ thư mục gốc.

  **-o**: chỉ định vị trí bắt đầu của một phân vùng (tính bằng sector).

  **-l**: hiển thị chi tiết theo định dạng dài (thêm quyền hạn, kích thước, GID, UID và mactimes).

  **-m**: tạo ra dữ liệu thô để phối hợp với mactime tạo dòng thời gian.

<img width="858" height="538" alt="image" src="https://github.com/user-attachments/assets/e75ce697-9103-4705-ba2d-cc564e03c9ad" />

Ta thấy có file flag.gz.

Trích xuất file này ra khỏi ổ đĩa theo inode và sao chép ra một tập tin mới bằng `icat`.

Command:
```
 icat disko-3.dd 522628 > flag.gz
```
Sau đó vào thư mục giải nén ta có flag: 

<img width="857" height="258" alt="image" src="https://github.com/user-attachments/assets/66726ad5-3b12-4a3b-97dc-95a89afbc4dd" />

Flag: picoCTF{n3v3r_z1p_2_h1d3_654235e0}
