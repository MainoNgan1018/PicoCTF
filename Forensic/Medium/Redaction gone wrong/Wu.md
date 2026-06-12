Đề cho ta một file PDF và nội dung bị che bởi những hộp đen.

Cạnh hộp đen còn có dòng gợi ý - Just painted over in MS Word (chỉ vẽ đè lên trong MS Word).

Đây là một kiểu che thông tin không chuyên dụng khi mắt thường nhìn vào sẽ thấy các hộp màu đen che khuất chữ nhưng ở tầng cấu trúc bên dưới, toàn bộ các kí tự chữ đó vẫn tồn tại nguyên vẹn 100%.

<img width="1599" height="1007" alt="image" src="https://github.com/user-attachments/assets/8629b755-f74d-486f-ab74-b1e29211caf7" />

Trong file PDFL các đối tượng sẽ được vẽ theo thứ tự. Dùng MS Word vẽ 1 cái hộp đen đè lên chữ, file sẽ hiểu:

* Lớp 1: các chuỗi text.

* Lớp 2: Vẽ một hình chữ nhật và tô đen tại tọa độ đó.

Các trình duyệt nhiệm vụ của chúng là render. Chúng sẽ đọc từ trên xuống dưới.

Hành động sao chép hoặc các công cụ như notepad: chúng bỏ qua các đối tượng đồ họa và chỉ tìm các text stream để trích xuất dữ liệu.

### Copy-paste thủ công ra notepad:

<img width="582" height="278" alt="image" src="https://github.com/user-attachments/assets/92a9ccf6-d6e5-4bbd-840f-2c55634e4b14" />

Flag: picoCTF{C4n_Y0u_S33_m3_fully}
