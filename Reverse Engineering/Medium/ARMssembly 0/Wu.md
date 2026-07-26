# picoCTF - What does this program print?

## 1. Phân tích `func1`

Hàm `func1` nhận hai tham số thông qua thanh ghi `w0` và `w1`.

Theo quy ước gọi hàm ARM64:

* `w0` chứa tham số thứ nhất `a`
* `w1` chứa tham số thứ hai `b`
* Giá trị trả về của hàm được đặt trong `w0`

Đoạn Assembly:

```asm
func1:
    sub sp, sp, #16
    str w0, [sp, 12]
    str w1, [sp, 8]

    ldr w1, [sp, 12]
    ldr w0, [sp, 8]

    cmp w1, w0
    bls .L2

    ldr w0, [sp, 12]
    b .L3

.L2:
    ldr w0, [sp, 8]

.L3:
    add sp, sp, 16
    ret
```

### `str` và `ldr`

`str` (Store Register) dùng để lưu dữ liệu từ thanh ghi vào bộ nhớ.

Ví dụ:

```asm
str w0, [sp, 12]
```

có thể hiểu đơn giản là:

```text
Memory[sp + 12] = w0
```

Tương tự:

```asm
str w1, [sp, 8]
```

lưu `w1` vào vị trí `sp + 8`.

Ngược lại, `ldr` (Load Register) lấy dữ liệu từ bộ nhớ đưa vào thanh ghi:

```asm
ldr w1, [sp, 12]
ldr w0, [sp, 8]
```

Sau hai lệnh này, giá trị của hai thanh ghi được đổi vị trí:

```text
w1 = giá trị ban đầu của w0 = a
w0 = giá trị ban đầu của w1 = b
```

Vì vậy, với:

```text
a = 2593949075
b = 2233560849
```

ta có:

```text
w1 = 2593949075
w0 = 2233560849
```

---

## 2. Phân tích phép so sánh

Tiếp theo:

```asm
cmp w1, w0
bls .L2
```

`cmp` thực hiện phép so sánh giữa `w1` và `w0`.

`bls` là viết tắt của **Branch if Lower or Same**, tức là nhảy tới `.L2` nếu giá trị thứ nhất nhỏ hơn hoặc bằng giá trị thứ hai theo phép so sánh unsigned.

Có thể hiểu logic tương đương:

```c
if (w1 <= w0)
    goto L2;
```

Trong bài:

```text
w1 = 2593949075
w0 = 2233560849
```

Ta có:

```text
2593949075 > 2233560849
```

Do đó điều kiện `w1 <= w0` là sai, nên chương trình **không nhảy** tới `.L2`.

Nó tiếp tục:

```asm
ldr w0, [sp, 12]
```

Lệnh này đưa lại giá trị `a` vào `w0`:

```text
w0 = 2593949075
```

Sau đó:

```asm
b .L3
```

`b` là **Branch**, dùng để nhảy vô điều kiện tới label `.L3`.

Tại `.L3`:

```asm
add sp, sp, 16
ret
```

Stack được khôi phục lại và `ret` đưa chương trình quay trở về nơi đã gọi `func1`.

Do `w0` chứa giá trị trả về nên:

```text
func1(a, b) = 2593949075
```

Nhìn tổng thể, `func1` có thể được viết lại gần giống C như sau:

```c
int func1(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
```

Hay đơn giản là hàm trả về **giá trị lớn hơn giữa `a` và `b`**.

---

## 3. Sau khi `func1` trả về

Trong `main`, sau khi gọi:

```asm
bl func1
```

giá trị trả về được đặt trong `w0`:

```text
w0 = 2593949075
```

Tiếp theo là đoạn Assembly khá thú vị:

```asm
mov w1, w0
adrp x0, .LC0
add x0, x0, :lo12:.LC0
bl printf
```

Đây chính là phần chuẩn bị các tham số cho hàm `printf`.

---

## 4. `mov w1, w0`

```asm
mov w1, w0
```

Lệnh này sao chép giá trị từ `w0` sang `w1`:

```text
w1 = w0
```

Do đó:

```text
w1 = 2593949075
```

Trong ARM64, các đối số của hàm thường được truyền qua các thanh ghi:

```text
x0 / w0 → argument 1
x1 / w1 → argument 2
x2 / w2 → argument 3
...
```

Ở đây chương trình chuẩn bị gọi:

```c
printf("Result: %ld\n", result);
```

Hàm `printf` có hai đối số:

```text
argument 1 → chuỗi format
argument 2 → giá trị cần in
```

Vì vậy, chương trình cần chuẩn bị:

```text
x0 → địa chỉ chuỗi "Result: %ld\n"
w1 → 2593949075
```

`mov w1, w0` chính là bước đưa kết quả của `func1` sang vị trí của **đối số thứ hai** của `printf`.

---

## 5. `adrp x0, .LC0`

Trong phần `.rodata` có:

```asm
.LC0:
    .string "Result: %ld\n"
```

`.LC0` là một label đại diện cho vị trí của chuỗi:

```text
"Result: %ld\n"
```

Lệnh:

```asm
adrp x0, .LC0
```

được dùng để lấy phần địa chỉ trang bộ nhớ (page address) chứa `.LC0` và đặt vào `x0`.

Nói đơn giản, sau lệnh này:

```text
x0 ≈ địa chỉ vùng bộ nhớ chứa .LC0
```

Tuy nhiên, `adrp` chỉ xử lý phần địa chỉ theo đơn vị page, nên vẫn cần thêm phần offset bên trong page.

---

## 6. `add x0, x0, :lo12:.LC0`

Tiếp theo:

```asm
add x0, x0, :lo12:.LC0
```

Lệnh này cộng thêm phần offset thấp (low 12 bits) của địa chỉ `.LC0`.

Kết hợp hai lệnh:

```asm
adrp x0, .LC0
add x0, x0, :lo12:.LC0
```

ta thu được địa chỉ đầy đủ của chuỗi `.LC0`.

Có thể hiểu đơn giản:

```text
adrp
  ↓
Lấy phần địa chỉ lớn / page address
  ↓
add
  ↓
Cộng thêm offset 12-bit
  ↓
x0 = địa chỉ chính xác của "Result: %ld\n"
```

Đây là một cách phổ biến trong ARM64 để tạo địa chỉ của một biến hoặc chuỗi nằm trong vùng nhớ tĩnh.

---

## 7. Gọi `printf`

Ngay trước khi gọi:

```asm
bl printf
```

ta có:

```text
x0 → "Result: %ld\n"
w1 → 2593949075
```

Theo quy ước truyền tham số của ARM64, điều này tương đương với:

```c
printf("Result: %ld\n", 2593949075);
```

Vì vậy chương trình in ra:

```text
Result: 2593949075
```

---

## 8. Kết luận

Giá trị lớn hơn giữa hai số:

```text
a = 2593949075
b = 2233560849
```

là:

```text
2593949075
```

Đổi sang hexadecimal 32-bit:

```text
2593949075 = 0x9ab4b6d3
```

Theo format của flag:

```text
picoCTF{9ab4b6d3}
```

### Flag

```text
picoCTF{9ab4b6d3}
```
