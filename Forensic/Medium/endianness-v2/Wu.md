Tên bài là "endianness-v2" và mô tả "organized the bytes a weird way" cho ta biết vấn đề nằm ở việc thứ tự các byte trong file bị đảo ộn theo cách hiểu về endianness (cách sắp xếp byte trong bộ nhớ).

Vì đây là hệ thống 32-bit, dữ liệu thường được chia thành các khối 4 byte

Kiểm tra cấu trúc byte bằng hexdump:
```
xxd -g 1 challengefile | head -n 20
```
<img width="2477" height="965" alt="image" src="https://github.com/user-attachments/assets/b594ed0c-e426-4baf-ad6d-1ba041f97e29" />

Nhìn qua là ta thấy FJ..FI nếu đảo lại thành JFIF chính là dấu hiệu của file JPEG.

Và ff d8 ff e0 (nếu đảo ngược e0 ff d8 ff) chính là Magic Number của file JPEG.

File này đang bị đảo ngược theo từng cụm 4 byte (32-bit Little Endian).

Script Python:
```bash
with open('challengefile', 'rb') as f_in:
    data = f_in.read()

# Đảo ngược từng khối 4 byte
# Sử dụng 'I' để đọc 32-bit, sau đó dùng socket.ntohl hoặc cách thủ công
fixed_data = bytearray()
for i in range(0, len(data), 4):
    chunk = data[i:i+4]
    if len(chunk) == 4:
        # Cách đơn giản nhất: đảo ngược 4 byte của chunk
        fixed_data.extend(chunk[::-1])
    else:
        fixed_data.extend(chunk)

with open('fixed_image.jpg', 'wb') as f_out:
    f_out.write(fixed_data)
```

Mở file ảnh được lưu ra: 

<img width="2755" height="1315" alt="image" src="https://github.com/user-attachments/assets/58f2b64e-aa76-4c87-add9-dcb3d7919f58" />

Flag: picoCTF{cert!f1Ed_iNd!4n_s0rrY_3nDian_004850bf}
