### Cách 1: Sử dụng công cụ giao diện trực quan Autopsy

Sử dụng tính năng `Keyword Search` để tìm từ "picoCTF".

Kết quả:

<img width="1558" height="893" alt="image" src="https://github.com/user-attachments/assets/b6485e46-6959-4256-ae86-49a8702e7fe0" />

### Cách 2: Sử dụng bộ công cụ mã nguồn mở Sleuth Kit

Đề bài nói rằng "This time I deleted the file!" nghĩa là file chứa flag đã bị xóa.

Liệt kê các tên tệp tin và thư mục đã bị xóa :

Command:
```
fls -r -d disko-4.dd
```
<img width="898" height="56" alt="image" src="https://github.com/user-attachments/assets/92018d8f-4b7a-4774-ada0-53c0d3dfbd0d" />

Ta thấy có 2 file, vì biết là file dont-delete.gz rồi nên mình trích xuất ra khỏi ổ đĩa theo inode và sao chép ra một tập tin mới bằng `icat`luôn.

Command:
```
 icat disko-4.532021 > flag.gz
```
<img width="969" height="22" alt="image" src="https://github.com/user-attachments/assets/8752f883-6a8a-40f5-a392-8fcdefd61780" />

Sau đó vào thư mục giải nén ta có flag: 

<img width="697" height="242" alt="image" src="https://github.com/user-attachments/assets/0ee078c7-39e7-45e1-882b-a3340f9e5a69" />

Flag: picoCTF{d3l_d0n7_h1d3_w3ll_4fed4369}
