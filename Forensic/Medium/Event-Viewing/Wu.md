Bài này cho ta 1 file .evtx là định dạng log của Windows Event Log nên ta sẽ sử dụng công cụ Event Viewer có sẵn trên Windows.

Dùng tính năng "Filter Current Log..." ở cột bên phải để lọc Event ID.

**1.Mảnh flag thứ nhất tìm được ở Event ID 1033 (Windows Installer).**

Đây là ID ghi lại sự kiện một ứng dụng đã được cài đặt, cập nhật hoặc gỡ bỏ. Vì đề bài nói "họ đã cập nhật phần mềm" nên ta sẽ tìn log này.

<img width="3815" height="1422" alt="image" src="https://github.com/user-attachments/assets/67c469b3-1e9e-423f-8c13-ec31454e58c1" />

**2.Mảnh thứ hai giấu ở Event ID 4657 (Registry Value Modified).**

Nếu phần mềm "chạy mà không làm gì", có thể nó chỉ âm thầm sửa Registry để ghi lại cấu hình hoặc flag vào đó.

<img width="3837" height="1447" alt="image" src="https://github.com/user-attachments/assets/9695e783-9b9b-4dee-b987-aa4cf74e2cf6" />

**3.Mảnh flag cuối ở Event ID 1074 (System Shutdown).**

Đây là lúc hệ thống bị tắt.

<img width="3812" height="1492" alt="image" src="https://github.com/user-attachments/assets/a37a3d55-2b4d-4922-81b8-d5c4be7dd288" />

Decode base64 3 đoạn kia theo lần lượt ta có flag.

Flag: picoCTF{Ev3nt_vi3wv3r_1s_a_pr3tty_us3ful_t00l_81ba3fe9}
