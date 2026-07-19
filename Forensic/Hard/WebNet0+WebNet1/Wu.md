## Phân tích

Đề cho 1 file .key (khóa riêng tư - private key) và một file .pcap (file ghi lại lưu lượng mạng).

Đây là bài giải mã lưu lượng mạng được mã hóa bới giao thức TLS/SSL.

Cơ chế:
<img width="1325" height="1445" alt="image" src="https://github.com/user-attachments/assets/76bce386-0393-4822-8780-7ca8b50dfd08" />

Khi ta mở file và Follow TLS Stream thì nó không hiện gì vì đã bị mã hóa.

<img width="2822" height="1710" alt="image" src="https://github.com/user-attachments/assets/41fdf7c7-206f-4b7b-bffe-afc78c41d9ca" />

Và xuất hiện các gói "Application Data" (Dữ liệu Ứng dụng) là nhãn chung mà Wireshark dùng để chỉ dữ liệu đã bị mã hóa đang được truyền đi giữa Client và Server.

<img width="2827" height="1402" alt="image" src="https://github.com/user-attachments/assets/e60b62da-8c07-4b03-b6e8-f3a3a154804f" />

-----------------------------

## Giải mã

Vào menu `Edit` -> `Preferences`.

Mở rộng mục `Protocols` và tìm chọn `TLS`.

Tại mục `RSA keys list` nhất `Edit`.

Thêm mục mới (+) điền các thông tin:
* Ip address điền ip máy chủ `172.31.22.220`.
* Port: 443 (cổng mặc định cho https).
* Key File: chọn file .key mà đề cung cấp.
* Nhấn OK.
  
<img width="1862" height="1165" alt="image" src="https://github.com/user-attachments/assets/27550af7-48d6-4392-b5a9-03fbc42fec7a" />

Sau khi cấu hình xong, ta sẽ thấy các gói tin trước đây là `Application Data` (đã mã hóa) giờ đây có thể hiển thị dưới dạng HTTP hoặc các giao thức rõ nghĩa khác.

Follow TLS Stream lại để xem nội dung.

<img width="2862" height="1785" alt="image" src="https://github.com/user-attachments/assets/a6ba934e-1929-4abc-8e55-5cc20d3336a9" />

Flag: picoCTF{nongshim.shrimp.crackers}

WebNet1 làm tương tự.

Flag: picoCTF{honey.roasted.peanuts} 
