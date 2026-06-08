Soi hxd cũng như cat -A :
> option -A của lệnh cat: ép toàn bộ những kí tự không in ra được phải hiện nguyên hình hết

<img width="1825" height="1119" alt="image" src="https://github.com/user-attachments/assets/5a9ae98e-62ba-4c35-b4e1-a2cb468dda0c" />

<img width="1887" height="655" alt="image" src="https://github.com/user-attachments/assets/7de2e6b3-8a4f-460a-87da-19cf00d38db5" />

Dữ liệu thực tế không phải mỗi dấu cách mà nó đan xen giữa 2 loại kí tự:

### 1. Dấu cách thông thường

Kí tự `space` (mã hex 20) trên `cat -A` nó hiện thị khoảng trắng.

### 2. Chuỗi E2 80 83

Trên `cat -A`, chuỗi này bị rã ra và hiển thị dưới dạng mã băm `M-bM-^@M-^C`.

Đây chính là ký tự Em Space (\u2003) — một loại khoảng trắng đặc biệt trong Unicode có độ rộng bằng một đại tự (bằng chữ M).

Và đây là dạng bài Binary Substitution.

Ta sẽ coi một loại khoảng trắng là 0 và loại còn lại là 1 nên sẽ có 2 trường hợp.

Script Python:
```bash
def solve_stego():
    # Đọc file dưới dạng byte để tránh lỗi encoding
    with open("whitepages.txt", "rb") as f:
        content = f.read()

    # Tìm và tách các ký tự dựa trên byte:
    # Space thông thường là b'\x20'
    # Em Space (E2 80 83) là b'\xe2\x80\x83'
    
    # Chúng ta sẽ duyệt qua chuỗi byte để gom thành danh sách các token
    tokens = []
    i = 0
    while i < len(content):
        if content[i:i+3] == b'\xe2\x80\x83':
            tokens.append('EM_SPACE')
            i += 3
        elif content[i:i+1] == b'\x20':
            tokens.append('SPACE')
            i += 1
        else:
            # Bỏ qua các ký tự xuống dòng (\n, \r) nếu có
            i += 1

    # TRƯỜNG HỢP 1: Em Space = 1, Space = 0
    bin_str1 = "".join(['1' if t == 'EM_SPACE' else '0' for t in tokens])
    
    # TRƯỜNG HỢP 2: Em Space = 0, Space = 1
    bin_str2 = "".join(['0' if t == 'EM_SPACE' else '1' for t in tokens])

    def binary_to_text(bin_data):
        try:
            # Gom mỗi 8 bit thành 1 byte
            bytes_output = bytearray()
            for i in range(0, len(bin_data), 8):
                byte_bits = bin_data[i:i+8]
                if len(byte_bits) == 8:
                    bytes_output.append(int(byte_bits, 2))
            return bytes_output.decode('utf-8', errors='ignore')
        except Exception as e:
            return f"Lỗi dịch: {e}"

    print("=== THỬ TRƯỜNG HỢP 1 (EmSpace=1, Space=0) ===")
    text1 = binary_to_text(bin_str1)
    print(text1[:300]) # In ra đoạn đầu xem có dạng flag không
    
    print("\n=== THỬ TRƯỜNG HỢP 2 (EmSpace=0, Space=1) ===")
    text2 = binary_to_text(bin_str2)
    print(text2[:300])

if __name__ == "__main__":
    solve_stego()
```
Tạo file và chạy:
<img width="1759" height="575" alt="image" src="https://github.com/user-attachments/assets/bcedc779-6457-4b64-ad62-aae7fe0e738a" />

Flag: picoCTF{not_all_spaces_are_created_equal_f5d46aff52c6e17f9fd6317b33d2d783}
