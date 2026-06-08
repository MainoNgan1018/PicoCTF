### Giới thiệt về Olevba

Đây là một trong những vũ khí mã nguồn mở phân tích mã độc tài liệu phổ biến và mạnh mẽ nhất.

Nó có thể phân tích các định dạng Microsoft Office thế hệ cũ (.doc, .xls, .ppt) lẫn thế hệ mới (.docm, .xlsm, .pptm).

Olevba phân tích file bằng cách đọc cấu trúc nhị phân và mã nguồn ẩn bên trong mà không cần mở file

Kết quả trả về được tổ chức thành một bảng tổng hợp rất rõ ràng, phân loại đâu là manh mối nguy hiểm, đâu là chuỗi nghi vấn.

***Cơ chế***
```
[File .docm]
(1. Giải mã cấu trúc / Unzip)
(2. Trích xuất code VBA)
(3. Quét Heuristic / Regex)
──> [Bảng Báo Cáo]
```
***Tác dụng***
* Phát hiện nhanh ký thuật làn rối mã
* Định hình kịch bản tấn công, biết con mã độc định làm gì
* ...
  
### Cài đặt oletools qua pip
```
sudo apt update && sudo apt install pipx -y
```
```
pipx install oletools
```
```
pipx ensurepath
```
Sau lệnh này restart lại terminal.

Sử dụng tool:

Command:
```
olevba weird.docm
```
Ta thấy phần print có chứa chuỗi base64 chính là flag.
```
cGljb0NURnttNGNyMHNfcl9kNG5nM3IwdXN9
```
<img width="2573" height="1255" alt="image" src="https://github.com/user-attachments/assets/2675ba12-8619-4ed4-a8b1-8f12bfb53279" />

Giải mã ta được:

<img width="2797" height="96" alt="image" src="https://github.com/user-attachments/assets/04152c47-1cef-444a-bb96-806c9754effc" />

Flag: picoCTF{m4cr0s_r_d4ng3r0us}
