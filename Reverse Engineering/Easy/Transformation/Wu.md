### UTF-8 và UTF-16LE

Đây đều là phương thức mã hóa Unicode.

**UTF-8**: Là mã hóa độ dài thay đổi. Ký tự tiếng Anh chiếm 1 byte, ký tự có dấu/tiếng Việt chiếm 2-3 byte, và các ký tự đặc biệt/emoji chiếm 4 byte.

**UTF-16LE**: Là mã hóa độ dài cố định hoặc thay đổi từng phần. Nó dùng 2 byte cho hầu hết các ký tự (kể cả tiếng Anh và tiếng Việt) và 4 byte cho các ký tự hiếm.

Với bài này, đề cho file enc với nội dung:

<img width="1877" height="512" alt="image" src="https://github.com/user-attachments/assets/ee894fa7-e5c3-43b3-b2bb-5f232eabfea8" />

Cho chuỗi văn bản lên gpt phân tích, ta biết:

File gốc ban đầu viết chữ CTF{ theo chuẩn UTF-16 (mỗi kĩ tự chiếm 2 byte). 

Khi ta dùng lệnh file hoặc mở bằng một trình đọc text mặc định dùng UTF-8 máy tính sẽ nhầm đây là 1 kí tự 16 bit của tiếng Trung.

<img width="1290" height="650" alt="image" src="https://github.com/user-attachments/assets/9ca528cd-8e20-42d9-b38c-56891e999d89" />

Code Python:

```bash
# Chuỗi bị lỗi hiển thị
bad_str = "灩捯䍔䙻ㄶ形楴獟楮獴㌴摟潦弸形㝦㘲捡㕽"

# Thử encode sang UTF-16LE rồi dịch lại sang chuỗi gốc
try:
    flag = bad_str.encode('utf-16-be').decode('utf-8', errors='ignore')
    print("Flag (Dạng 1):", flag)
except Exception as e:
    pass
```

Kết quả: 

<img width="1932" height="227" alt="image" src="https://github.com/user-attachments/assets/506f9153-cce4-418b-9a04-9516569da670" />

Flag: picoCTF{16_bits_inst34d_of_8_b7f62ca5}
