# Transformation

## Challenge Information

- Category: Reverse Engineering
- Difficulty: Easy
- Points: 20

## Mô tả

<img width="530" height="165" alt="image" src="https://github.com/user-attachments/assets/02d69a7e-18ce-4e82-8939-54f2667bc91c" />

I wonder what this really is...

```python
''.join([
    chr((ord(flag[i]) << 8) + ord(flag[i + 1]))
    for i in range(0, len(flag), 2)
])
```

## Phân tích

Phần quan trọng là `(ord(flag[i]) << 8) + ord(flag[i + 1])`:

ord(): chuyển một kí tự thành mã ASCII dạng số nguyên.

chr(): chuyển ngược một mã số nguyên thành kí tự tương ứng.

<<8: là phép dịch trái bit đi 8 vị trí (thêm 8 số 0 vào phía sau <-> nhân thêm 2^8).

-> lấy kí tự 1 <<8 + ký tự 2

Ví dụ: 
```
flag[i]     = 'p'
flag[i + 1] = 'i'
```
Sau đó:
```
ord('p') = 0x70
ord('i') = 0x69
```
Dịch trái 8 bits:
```
0x70 << 8 = 0x7000
```
Cộng kí tự 2:
```
0x7000 + 0x69 = 0x7069
```
Do đó, hai ký tự ASCII 8-bit được kết hợp thành một giá trị 16-bit.

Vì vậy trước khi dịch ngược ta phải chia 16 bit thành 2 phần 8 bit -> dịch phải sau đó && 0xFF để lấy 8 bits cuối để giải mã 

Code solve:
```python
with open('enc', 'r', encoding='utf-8') as f:
    data = f.read().strip()

flag = ""

for c in data:
    val = ord(c)
    flag += chr(val >> 8)
    flag += chr(val & 0xFF)

print(flag)
```

## Mở rộng

### UTF-8 và UTF-16LE

Đây đều là phương thức mã hóa Unicode.

**UTF-8**: Là mã hóa độ dài thay đổi. Ký tự tiếng Anh chiếm 1 byte, ký tự có dấu/tiếng Việt chiếm 2-3 byte, và các ký tự đặc biệt/emoji chiếm 4 byte.

**UTF-16LE**: Là mã hóa độ dài cố định hoặc thay đổi từng phần. Nó dùng 2 byte cho hầu hết các ký tự (kể cả tiếng Anh và tiếng Việt) và 4 byte cho các ký tự hiếm.

<img width="1290" height="650" alt="image" src="https://github.com/user-attachments/assets/9ca528cd-8e20-42d9-b38c-56891e999d89" />

Flag: picoCTF{16_bits_inst34d_of_8_b7f62ca5}
