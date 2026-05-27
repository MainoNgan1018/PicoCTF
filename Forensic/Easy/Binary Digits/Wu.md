
## 1. Binary Digits

Đề cho ta một file .bin toàn những kí tự nhị phân 0,1
<img width="2796" height="806" alt="image" src="https://github.com/user-attachments/assets/5a94b3fe-7993-40e9-b1d2-e30add9e3b54" />

Bản chất của dữ liệu số:

* Nếu ta đọc 8 bit 1 lúc, ta có văn bản (ASCII)
* Nếu ta đọc 24 bit 1 lúc, ta có màu sắc (RGB)
* Nếu ta xếp chúng lên một mặt phẳng tọa độ, ta có hình ảnh

Các chuỗi 0 và 1 này có thể đại diện cho các ký tự ASCII

Chia chuỗi thành các nhóm 8 bit, mỗi nhóm này sẽ tương ứng với một giá trị thập phân và từ đó chiếu lên bảng mã ASCII

Sử dụng ([CyberChef](https://gchq.github.io/CyberChef/))

Ta dùng module "From Binary" nó chuyển chuỗi 01 về các byte gốc, và các byte đó bắt đầu bằng JFIF (magic bytes của file ảnh jpg) 

-> file thực chất là ảnh jpg đã bị chuyển sang dạng nhị phân.
<img width="1999" height="1224" alt="image23" src="https://github.com/user-attachments/assets/8b65e4ce-21c6-4c54-ae64-c4a3b1c779a9" />

Thêm module “Render Image” có tác dụng biến các byte dữ liệu thô thành một hình ảnh được hiển thị trên màn hình -> flag
<img width="1999" height="952" alt="image9" src="https://github.com/user-attachments/assets/cee8351d-d489-4983-a9ee-a72abe8dbe3a" />

Flag: picoCTF{h1dd3n_1n_th3_b1n4ry_3d2e65ba}
