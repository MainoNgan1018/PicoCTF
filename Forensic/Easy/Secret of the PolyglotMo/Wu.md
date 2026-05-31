Mở file thì ta chỉ thấy mỗi phần cuối của flag.

<img width="1110" height="317" alt="image17" src="https://github.com/user-attachments/assets/660ee700-093d-4f9b-b57d-6e5a50779d6b" />

Binwalk ta thấy:

<img width="1999" height="314" alt="image16" src="https://github.com/user-attachments/assets/12469cda-8247-4d2f-b5e5-d039da62c734" />
Có ảnh PNG ở đầu nhưng trong thư mục download lại không thấy ảnh PNG được trích ra vì do pdf làm nhiễu.

Binwalk tìm header và footer của png nhưng ngay sau đó là khởi đầu của pdf, sự chuyển tiếp đột ngột khiến nó không thể xác định chắc chắn đâu là ranh giới an toàn để cắt file.

Đổi đuôi file thành .png ta sẽ mở được ảnh là phần đầu của flag.

<img width="1999" height="739" alt="image15" src="https://github.com/user-attachments/assets/58a9820c-0c84-4408-a95c-703e4c0095e4" />

Flag: picoCTF{f1u3n7_1n_pn9_&_pdf_724b1287}
