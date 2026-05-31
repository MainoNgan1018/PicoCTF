File .dd là một tệp ảnh đĩa thô, được tạo ra bởi lệnh dd trong unix/linux, lưu trữ bản sao bit-for-bit của một thiết bị lưu trữ như ổ cứng, USB, hoặc CD/DVD.

Đặc điểm:

* Sao chép thô : tệp chứa toàn bộ nội dung của đĩa : các tệp tin, thư mục, hệ thống tệp và cả không gian trống hoặc dữ liệu đã bị xóa.

* Thường dùng để tạo bản sao lưu, phục hồi dữ liệu hoặc trong các quy trình pháp chứng máy tính
  
* Công cụ mở: các phần mềm quản lý ảnh đĩa, dùng lệnh dd trên linux/macOS ghi ngược lại ổ cứng

### Cách 1: Sử dụng FTK Imager  + nhập từ khóa của cờ:
<img width="1161" height="1467" alt="image5" src="https://github.com/user-attachments/assets/d6d56007-b84d-4865-9f41-74fbfa626962" />

### Cách 2: Sử dụng lệnh Strings + Grep:
Cách này nhanh vì nó không quan tâm đến cấu trúc file hệ thống, chỉ tìm chuỗi kí tự.
<img width="1999" height="100" alt="image4" src="https://github.com/user-attachments/assets/b4a173ef-bf0c-46d3-8ad8-de7757ef7087" />

Flag: picoCTF{1t5_ju5t_4_5tr1n9_e3408eef}

