Soi HxD thì thấy file này thực chất là 1 file .png với đầy đủ header và footer mà không chứa bất kì hex nào của file .jpg

<img width="1705" height="918" alt="image" src="https://github.com/user-attachments/assets/597cee02-db76-4fe3-999c-eb6d90d068fe" />

Suy ra đây là 1 file bị chỉnh sửa định dạng.

Sửa về đúng định dạng và check binwalk:

<img width="2790" height="387" alt="image" src="https://github.com/user-attachments/assets/17ecd0e9-999e-49f8-a089-e961244a20f1" />

Kết quả cho ta biết có tập bị nén và cảnh báo một hoặc một vài tập tin không thể giải nén hoặc do chưa tìm thấy tiện ích nào để triển khai.

Giải nén và ta có file 2_c.jpg mở ra lại là ảnh búp bê giống hết file ảnh đầu tiên.

Tiếp tục binwalk file ảnh này:

Ta có thể thấy nó thực chất là file .png và bên trong nó lại chứa dữ liệu nén tiếp.

<img width="2808" height="906" alt="image" src="https://github.com/user-attachments/assets/ac454b33-ac07-4e61-89f5-2a54e0b4ed97" />

Sử dụng option -e kết hợp với option -M (quét đệ quy) của binwalk:

Command:
```
binwalk -e -M 2_c.png
```
> Option -M mình có từng đề cập tới ở bài File types file Bonus.md

<img width="2795" height="1124" alt="image" src="https://github.com/user-attachments/assets/6139e780-a0f1-4af2-8e03-3a221bdf993e" />

Mở lần lượt tất cả các file đã giải nén được thì đến tệp tin thứ 4 chứa file flag.txt:

<img width="2686" height="1276" alt="image" src="https://github.com/user-attachments/assets/24042ac4-2a4a-4b0f-b06a-384211d3186e" />


Flag: picoCTF{LL9lb1dR4QbGe4l4iWCvGq9pdtwt7392}
