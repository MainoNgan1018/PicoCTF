Bài này không như 2 bài trước là có sẵn chuỗi cờ bị biến đổi vì khi dùng strings ta thấy toàn những kí tự lặp và nhiễu.

<img width="705" height="380" alt="Screenshot 2026-07-21 113206" src="https://github.com/user-attachments/assets/c279d3ce-2cbf-40ef-8315-3cf2e3663b0a" />

Soi HxD ta thấy đây là dữ liệu bị mã hóa.

<img width="1550" height="1290" alt="Screenshot 2026-07-21 113221" src="https://github.com/user-attachments/assets/08048d98-b9b6-4399-a7be-b097f1c72108" />

Mở file thực thi bằng IDA để xem quá trình file này bị mã hóa như nào từ đó giải mã.

<img width="2787" height="1565" alt="Screenshot 2026-07-21 102941" src="https://github.com/user-attachments/assets/99276791-3ca0-40c7-a0fc-ef71339ae651" />

# Phân tích mã giả hàm main

## 1. Phân tích luồng mở file

* v13 = fopen("flag.txt", "r"): Mở file chứa flag để đọc.

* stream = fopen("original.bmp", "r"): Mở file ảnh gốc.

* v15 = fopen("encoded.bmp", "a"): Mở file ảnh đích để ghi nối tiếp (append).

## 2. Giải thích chi tiết từng phần trong code.

* Đoạn 1 (chép phần header/đầu file BMP gốc)
```bash
v6 = fread(&ptr, 1u, 1u, stream);
v11 = 2000;
for ( i = 0; i < v11; ++i )
{
    fputc(ptr, v15);
    v6 = fread(&ptr, 1u, 1u, stream);
}
```
Vòng lặp này đọc lần lượt từng byte từ original.bmp và ghi thẳng sang encoded.bmp trong 2000 byte đầu tiên.

* Đoạn 2 (đọc và kiểm tra độ dài flag)
```bash
v12 = fread(v16, 0x32u, 1u, v13);
if ( v12 <= 0 ) {
    puts("flag is not 50 chars");
    exit(0);
}
```
Chương trình đọc đúng 50 ký tự từ flag.txt vào biến mảng v16. Nếu không đủ 50 ký tự, chương trình sẽ báo lỗi và thoát.

* Đoạn 3 (vòng lặp nhúng dữ liệu chính - Logic mã hóa)
```bash
for ( j = 0; j <= 49; ++j )
{
    for ( k = 0; k <= 7; ++k )
    {
        v5 = codedChar((unsigned int)k, (unsigned int)(char)(v16[j] - 5), (unsigned int)ptr);
        fputc(v5, v15);
        fread(&ptr, 1u, 1u, stream);
    }
}
```
Vòng lặp duyệt qua từng kí tự của flag (0->49 : 50 ký tự).

Vòng lặp trong chạy 8 lần cho mỗi kí tự (tương ứng 8 bit của 1 byte).

Hàm codedChar(...) nhận vào vị trí k, giá trị kí tự flag đã bị trừ đi 5, và byte dữ liệu hiện tại của ảnh gốc (ptr), sau đó trả về 1 byte v5 đã được sửa đổi bit (đây chính là thao tác giấu bit LSB).

<img width="1745" height="725" alt="Screenshot 2026-07-21 111137" src="https://github.com/user-attachments/assets/acc165a4-14e7-4428-a403-88b5cf7f6987" />

**Phân tích thao tác hàm CodeChar**:

* Dịch phải k lần bit thứ k của kí tự sau khi -5.
* Xóa lsb của pixel gốc (a3 & 0xFE).
* Nhét bit vào chỗ trống (| (v4&1) ).

Phép dịch để cắt đúng bit thứ k của kí tự flag ( đưa bit đó về cuối rồi lấy ra) sau đó nhét vào lsb của pixel ảnh gốc.

Và chương trình phải mượn 8 pixel liên tiếp để chứa đủ 8 bit của 1 ký tự trong flag.

Sau mỗi lần nhúng 1 bit, chương trình đọc tiếp 1 byte tiếp theo từ original.bmp (fread(&ptr, 1u, 1u, stream)).

* Đoạn 4 (chép phần đuôi ảnh còn lại)
```bash
while ( v6 == 1 )
{
    fputc(ptr, v15);
    v6 = fread(&ptr, 1u, 1u, stream);
}
```
Sau khi nhúng xong, vòng lặp sao chéo nốt toàn bộ dữ liệu của file original.bmp sang encoded.bmp

Code C++:

<img width="825" height="925" alt="image" src="https://github.com/user-attachments/assets/03723598-0f0b-4509-878f-464576ab4f3b" />

Flag: picoCTF{n3xt_0n300000000000000000000000009e6b130d}



