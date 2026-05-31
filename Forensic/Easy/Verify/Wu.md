Vào terminal người chơi như đề hướng dẫn và liệt kê thử xem có những gì.

Ta có thể hiểu đơn giản mã hash là một bộ dấu vân tay. Dù file nặng hay nhẹ, chỉ cần chạy qua thuật toán SHA-256 nó luôn cho ra một chuỗi  64 kí tự cố định, đổi đúng 1 dấu phẩy cũng làm mã hash khác hoàn toàn.

<img width="1999" height="790" alt="image2" src="https://github.com/user-attachments/assets/a38d247f-bd4a-4203-b748-dc1b6103b545" />

Trong thư mục files/ sẽ có rất nhiều file nhỏ, ta được cho mã hash để tìm xem trong chỗ file này file nào có nội dung khớp với mã hash này.

<img width="1865" height="365" alt="image34" src="https://github.com/user-attachments/assets/89a66f9d-ea2a-4711-8867-7dc7e9b79be1" />


Lệnh quét toàn bộ file, tính mã SHA-256 của chúng và hiển thị file có mã # mã đề bài cho:
```
sha256sum files/* | grep fba9f49bf22aa7188a155768ab0dfdc1f9b86c47976cd0f7c9003af22e20598f7
```
`sha256sum <file>`                  `sha256sum <directory>/*`

Tìm được đúng file thì dùng nó để giải mã
```
./decrypt.sh files/<file>.
```
<img width="1999" height="172" alt="image8" src="https://github.com/user-attachments/assets/184c6486-9c06-4330-8800-6932c9c36288" />

Flag: picoCTF{trust_but_verify_87590c24}



