# For what argument does this program print "win"?

## 1. Phân tích hàm `func`

Đầu tiên, hàm `func` lưu các giá trị vào stack:

```asm
str w0, [sp, 12]

mov w0, 88
str w0, [sp, 16]

mov w0, 4
str w0, [sp, 20]

mov w0, 3
str w0, [sp, 24]
```

Có thể biểu diễn stack như sau:

| Stack | Giá trị |
|---|---:|
| `[sp, #12]` | `input` |
| `[sp, #16]` | `88` |
| `[sp, #20]` | `4` |
| `[sp, #24]` | `3` |

Sau đó chương trình thực hiện:

```asm
ldr w0, [sp, 20]
ldr w1, [sp, 16]
lsl w0, w1, w0
```

Ta có:

```text
w0 = 4
w1 = 88
```

Lệnh `lsl` thực hiện phép dịch trái:

```text
w0 = 88 << 4
   = 88 × 2^4
   = 1408
```

Tiếp theo:

```asm
ldr w1, [sp, 28]
ldr w0, [sp, 24]
sdiv w0, w1, w0
```

Đây là phép chia số nguyên:

```text
w0 = 1408 / 3
   = 469
```

Cuối cùng:

```asm
ldr w1, [sp, 28]
ldr w0, [sp, 12]
sub w0, w1, w0
```

Thực hiện:

```text
w0 = 469 - input
```

Do đó, xét tổng quát theo các giá trị trong Assembly, ta có công thức:

```text
func(input) = ((88 << 4) / 3) - input
```

Hay theo công thức tổng quát của các tham số:

```text
func(input) = (a << b)) / c - input
```

---

## 2. Tìm argument để chương trình in `You win!`

Trong `main`:

```asm
bl func
cmp w0, 0
bne .L4
```

Sau khi `func` trả về:

- Nếu `w0 != 0` → nhảy tới `.L4` → `You Lose :(`
- Nếu `w0 == 0` → tiếp tục → `You win!`

Vì vậy, ta cần:

```text
func(input) = 0
```

Đề bài cho:

```text
a = 86
b = 3
c = 3
```

Thay vào công thức và suy ra:

```text
input = 229
```

---

## 3. Chuyển argument sang Flag

Đổi `229` sang hexadecimal:

```text
229 = 0xe5
```

Đề yêu cầu:

```text
hex, lowercase, no 0x, and 32 bits
```

`no 0x` nghĩa là bỏ tiền tố `0x`:

```text
e5
```

Còn `32 bits` nghĩa là cần biểu diễn đủ 32 bit, tương đương **8 chữ số hexadecimal**:

```text
e5 → 000000e5
```

Flag: picoCTF{000000e5}


## Flag

```text
picoCTF{000000e5}
```
