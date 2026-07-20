Bài này kết hợp giữa Reverse Engineering (file ELF) và Forensics (file ảnh).

Đầu tiên phân tích ảnh mystery.png trước thì quét zsteg hoặc có thể dùng strings + grep để tìm ra chuỗi cờ đã bị can thiệp.

<img width="2190" height="275" alt="image" src="https://github.com/user-attachments/assets/df57f3fb-a2c4-4c22-8010-e7b9ba0bc879" />

Chuỗi ta tìm được bị lệch thành `picoCTK` thay vì `picoCTF` nên ta sẽ dùng IDA Pro để xem nó đã bị biến đổi như thế nào.

<img width="3040" height="1570" alt="image" src="https://github.com/user-attachments/assets/f58d87bb-8d25-4822-be38-d7764d3bfd7c" />

Xem mã giả C ở hàm main, chương trình ELF không chỉ copy nguyên văn chuỗi từ `flag.txt` vào ảnh mà nó đã biến đổi trực tiếp từng kí tự thông qua các phép toán số học trước khi ghi (fputc) vào file `mystery.png`.

# Phân tích mã giả `main`.

### **1.Mở tệp tin**
* v7 = fopen("flag.txt", "r"); -> Mở file flag để đọc.
* v8 = fopen("mystery.png", "a"); -> Mở file ảnh ở chế độ append (ghi nối tiếp vào cuối).
  
### **2.Đọc dữ liệu**
* fread(ptr, 0x1Au, 1u, v7) -> Đọc vào buffer ptr một khối dữ liệu có kích thước 0x1A (26 byte) - đây chính là độ dài của chuỗi flag chuẩn (ví dụ: picoCTF{...}).
* 
### **3.Cơ chế ghi và biến đổi ký tự (fputc)**
Chương trình chia chuỗi 26 byte thành các đoạn và xử lý từng byte như sau:
* Giữ nguyên 6 ký tự đầu tiên (từ chỉ số 0 đến 5):
```
fputc(ptr[0], v8); // 'p'
fputc(ptr[1], v8); // 'i'
fputc(ptr[2], v8); // 'c'
fputc(ptr[3], v8); // 'o'
fputc(ptr[4], v8); // 'C'
fputc(ptr[5], v8); // 'T'
```
Đến đây, chuỗi bắt đầu với picoCT.
* Biến đổi đoạn từ ký tự thứ 6 đến 14 :
```
fputc((char)(ptr[i] + 5), v8);
```
Điểm mấu chốt: ký tư thứ 6 ban đầu là F ( mã ASCII là 70 ) được cộng thêm 5 thành 75 tương ứng với chữ K.
* Biến đổi ký tự thứ 15 (ptr[15]):
```
fputc((char)(ptr[15] - 3), v8);
```
Kí tự này bị trừ đi 3 đơn vị so với gốc.
* Giữ nguyên đoạn từ 16 đến 25:
```
fputc((char)ptr[j], v8);
```
Đoạn cuối được giữ nguyên giá trị gốc và ghi tiếp vào ảnh.

Vì file ELF đã làm biến đổi chuỗi gốc trước khi in ra file ảnh nên ta khôi phục lại chuỗi `flag.txt` ban đầu bằng cách làm ngược lại các phép toán trong code:
* Những ký tự nào bị cộng (+ 5), ta phải trừ đi (- 5).
* Những ký tự nào bị trừ (- 3), ta phải cộng lại (+ 3).

Code C++:

<img width="1937" height="1942" alt="image" src="https://github.com/user-attachments/assets/9a5a0e97-0f17-46f3-8db7-f3993f64a9d3" />

<img width="2860" height="182" alt="image" src="https://github.com/user-attachments/assets/d1010dc4-af61-4a93-9f69-bc8004752470" />

Flag in ra bị lỗi 1 kí tự dấu do phần đó bị trống ta thay dấu `.` vào nên đoạn đó bị dịch thành dấu `)`

Thay bằng `{`.

Flag: picoCTF{f0und_1t_b3ea3199}
