Check metadata bằng exiftool ta thấy ở trường comment có văn bản định dạng base64

<img width="1999" height="1115" alt="image29" src="https://github.com/user-attachments/assets/56c54b4e-932d-4ce8-b730-cc49923f3389" />

Giải mã ra ta thấy hint gợi ý sử dụng tool steghide cùng đoạn mật khẩu của nó cũng là định dạng base64.

Steghide là công cụ dòng lệnh dùng để giấu tin mật vào các tệp hình ảnh hoặc âm thanh mà không làm thay đổi vẻ ngoài hay chất lượng của tệp (phổ biến nhất cho JPG và WAV)

Option:
```
steghide info tên_file.jpg : kiểm tra xem file có chứa dữ liệu ẩn không
steghide extract -sf tên_file.jpg : trích xuất dữ liệu ẩn
steghide embed -ef bí_mật.txt -cf ảnh_gốc.jpg : giấu file vào ảnh (embed)
```
(nếu không biết mật khẩu có thể dùng stegseek để bẻ khóa = brute-force)

<img width="1999" height="208" alt="image25" src="https://github.com/user-attachments/assets/fc7be5dc-9cab-49fb-84e0-459c28d9bb30" />

Dữ liệu được xuất ra file flag.txt lưu trong File Explore

Mở file ra: 

<img width="1502" height="387" alt="image13" src="https://github.com/user-attachments/assets/dd570e69-b7fc-4047-8679-57bce2c0b24a" />


Flag: picoCTF{h1dd3n_1n_1m4g3_f051f2e8}
