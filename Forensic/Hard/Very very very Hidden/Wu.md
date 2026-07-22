Xem danh sách tổng hợp tất cả các giao thức xuất hiện trong file .pcap và tỉ lệ của chúng trong Wireshark:

`Statistics` -> `Protocol Hierarchy`

<img width="2275" height="1530" alt="image" src="https://github.com/user-attachments/assets/a2f54b74-35a8-4a74-840e-910c929462bf" />

Filter theo 1 số giao thức nổi bật hay được giấu flag như http, dns, tls,..

Thông qua việc quan sát lưu lượng, ta thấy kẻ tấn công đã truy cập các trang như Google, GitHub và Microsoft.

<img width="3820" height="1517" alt="image" src="https://github.com/user-attachments/assets/e60c5239-b2c8-4f88-ac2b-56aa85292580" />

Filter theo http ta thấy dữ liệu ảnh PNG được truyền trực tiếp qua giao thức HTTP:

Sử dụng tính năng `File` -> `Export Objects` -> `HTTP` để trích xuất ra phân tích.

<img width="2870" height="1605" alt="image" src="https://github.com/user-attachments/assets/d69ffd63-c9c5-4acb-a534-bd75ad424edd" />

<img width="742" height="537" alt="image" src="https://github.com/user-attachments/assets/1f21e334-8983-493d-bfd6-8644791ec3e4" />


Ta có thể thấy 2 bức ảnh mặc dù mở lên đều là hình con vịt nhưng `evil_duck.png` lại có dung lượng lớn gấp đôi `duck_png`nhưng độ phân giải lại thấp hơn, nghi vấn có dữ liệu ẩn bên trong.

<img width="1537" height="145" alt="image" src="https://github.com/user-attachments/assets/7e4f11ee-6e27-4f57-8b21-b61118247895" />

Tôi đã thử dùng các công cụ như binwalk, zsteg, exiftool,... nhưng hầu như không có gì.

Dưa trên các từ khóa như PowerShell, Steganography và Microsoft, sau khi tìm kiếm 1 hồi thì tôi biết 1 kĩ thuật được sử dụng là Invoke-PSImage.

Đây là một công cụ PowerShell cho phép nhũng tệp script và các pixel của tệp hình ảnh PNG

Lý thuyết hiểu về cách nhúng dữ liệu tải trọng : https://github.com/peewpw/invoke-psimage

Cách cài đặt : https://github.com/imurasheen/Extract-PSImage

Trước khi cài ta phải tắt tạm thời Windows Defender / Antivirus

Vào `Windows Security` > `Virus & threat protection settings` > `Manage settings` và tạm thời tắt Real-time protection.

Sau đó tạo file code trên máy, ở đây mik mở tạo trên VsCode, chọn 1 thư mục để lưu trữ.

Tạo file Extract-Invoke-PSImage.ps1 trong thư mục đó, mở trang github trên cop toàn bộ nội dung vào rồi lưu.

Chạy các lệnh sau :

```
Set-ExecutionPolicy -ExecutionPolicy Unrestricted -Scope Process
```
```
. .\Extract-Invoke-PSImage.ps1
```
```
Extract-Invoke-PSImage -Image .\evil_duck.png -Out .\result.ps1
```
Mở file `result.ps1`:
<img width="795" height="455" alt="image" src="https://github.com/user-attachments/assets/2e53179e-869e-4121-a5af-7c1d00684ac5" />

Đoạn mã PowerShell trong hình ảnh nội dung là thực hiện phép toán XOR giữa hai chuỗi $string1 và $string2 để giải mã ra dòng cờ (flag).

Ta copy và chỉnh lại đoạn code, xóa dòng cuối và thêm dòng lệnh viết kết quả ra sau đó chạy, lưu ý đây là code PowerShell nên phải lưu file đuôi .ps1

<img width="2232" height="2047" alt="image" src="https://github.com/user-attachments/assets/4cfd509c-3719-4845-8a96-10c1d2f068d5" />

<img width="3317" height="1705" alt="image" src="https://github.com/user-attachments/assets/53a1ecbc-d87d-4450-a741-4c627a6a4133" />


