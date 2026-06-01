### **1.Để làm bài này trước tiên ta phải cài đặt các công cụ cần thiết:**
```
sudo apt-get update
sudo apt-get install sleuthkit
```
### **2.Tạo tệp nội dung và dòng thời gian:**

Sử dụng tool fls để quét cấu trúc và thu thập siêu dữ liệu tệp vào một tệp nội dung, nó xuất ra dữ liệu thô dưới định dạng Body File.

Command:
```
fls -r -m / <image_name> > body.txt
```
Xem nội dung bằng lệnh `cat body.txt`:

<img width="942" height="150" alt="image2" src="https://github.com/user-attachments/assets/0976db23-14d4-4498-b38f-b8e5a1f05999" />

Cấu trúc của nó:

> MD5 | Name | Inode | Mode | UID | GID | Size | Atime | Mtime | Ctime | Crtime

Tạo dòng thời gian để nhìn dễ hiểu hơn.

Command:
```
mactime -b body.txt > new_body.txt
```
<img width="855" height="57" alt="image20" src="https://github.com/user-attachments/assets/25f6508a-d138-491d-89bc-7bdce17a3005" />

Xem nội dung bằng lệnh `cat new_body.txt`:
<img width="1150" height="220" alt="image10" src="https://github.com/user-attachments/assets/e3889890-0c1d-46fa-a5d4-810a5f272a98" />

### **3.Lọc các sự kiện theo hint (MACB)**

Command:
```
grep “macb” new_body.txt
```
MACB (Modify, Access, Change, Birth) - nơi chứa các manh mối về hành động anti-forensics.

<img width="1999" height="231" alt="image9" src="https://github.com/user-attachments/assets/95cace64-72cb-4f0b-aca8-d02cb1f92cd1" />

***Phân tích thông số:***
- Cột kích thước tệp tin
  
- Cột macb:
```
m (modified): nội dung tệp tin đã bị thay đổi
a (accessed): tệp tin đã được truy cập (đọc)
c (changed): metadata của tệp bị thay đổi
b (birth): thời điểm tệp tin được tạo ra lần đầu
```

- Cột loại tệp và quyền hạn:
  
  * Kí tự đầu : r (regular file): tệp tin thông thường ; d (directory): thư mục ; l (symbolic link) : liên kết mềm
    
  * Dãy các kí tự tiếp theo là quyền đọc -r, ghi -w, thực thi -x của ba nhóm chủ sở hữu, nhóm và người khác
    
- Cột User IB và Group ID:
  
  * Số 0 đầu là UID: mã số định danh người sở hữu tệp tin, số 0 thường đại diện cho tài khoản root (quản trị cao nhất)
    
  * ố 0 thứ hai là GID: mã số định danh nhóm sở hữu tệp tin
    
- Cột Inode : là mã số định danh ID thực sự của tệp tin, giúp hệ điều hành tìm thấy vị trí thực tế của dữ liệu trên đĩa.
  
- Cột đường dẫn: hiển thị đường dẫn đầy đủ đến tệp tin đó trên hệ thống
  
Kiểm tra phần đầu cuối của timeline.

<img width="1155" height="440" alt="image5" src="https://github.com/user-attachments/assets/ea8c1f99-1522-48d2-921f-ae850ed24bb9" />

Trong linux, .ash_history đóng vai trò tương tự như .bash_history trong Bash shell.
Chức năng của là lưu trữ lịch sử các câu lệnh mà người dùng gõ trong terminal.

Khi xây dựng timeline = mactime tất cả các sự kiện thay đổi trên hệ thống được liệt kê theo thứ tự thời gian 

→ file ash_history bình thường phải tồn tại từ khi hệ thống mới cài đặt mà khi lọc ta lại thấy xuất hiện với mốc thời gian rất gần

→ attacker đã xóa file lịch sử cũ và tạo một file mới để xóa sạch dấu vết (anti - forensics).


### **4.Trích xuất nội dung từ một file nghi vấn**

Command:
```
 icat <image_name> ID
```
Sau khi xem nội dung ta base64 ra flag.

<img width="1145" height="160" alt="image4" src="https://github.com/user-attachments/assets/0a90b827-12f8-4aa6-9a91-efac4086dd63" />

Flag: pico{573417h13r_7h4n_7h3_1457_58527bb222}


