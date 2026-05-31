Sử dụng lệnh để nhận dạng định dạng file:
```
file Flag.pdf
```
<img width="1739" height="85" alt="Screenshot 2026-05-31 220728" src="https://github.com/user-attachments/assets/5fb704df-eb03-4146-9921-95cc9a3dda18" />

Kết quả trả về `shell archive text` nghĩa là nó nhận diện đây là một file văn bản chữa mà script hoặc một kho lưu trữ dạng shell.

Binwalk ta thấy:
<img width="2646" height="358" alt="image" src="https://github.com/user-attachments/assets/3830d6ba-7dcb-4938-8c35-38d27f2446eb" />

* Tại 0xBD5 (Vị trí cốt lõi): Phát hiện dữ liệu được mã hóa/đóng gói bằng uuencode (một cơ chế mã hóa dữ liệu nhị phân thành văn bản ASCII)

Đọc nội dung của file bằng lệnh:
```
cat Flag.pdf
```
<img width="1779" height="719" alt="image" src="https://github.com/user-attachments/assets/2403b02c-3ed8-4d77-8626-7ac1c46b2e31" />
<img width="634" height="532" alt="image" src="https://github.com/user-attachments/assets/87c21128-392c-4961-8956-8f0191366ba1" />

Tạo file script:

```
nano solve.sh
```

Dán toàn bộ đoạn begin 600 flag ... end.

Sau đó lưu và thoát: `Ctrl O -> Enter -> Ctrl X`


Sử dụng tool uudecode để giải mã file được mã hóa bằng uuencode:
```
uudecode solve.sh
```
<img width="2195" height="459" alt="image" src="https://github.com/user-attachments/assets/d85e5f66-8e11-45d6-bf71-d573bebc3ea0" />

Kiểm tra thử file flag mà ta giải mã được thực chất là định dạng gì thì kết quả là `current ar archive`.

Đây là định dạng lưu trữ Archive (.ar).

Và khi binwalk file flag này ta lại phát hiện tại offset 100 có chứa dữ liệu nén `bzip2 compressed data`.

Giải nén tiếp ta lại binwalk thấy bên trong lại ẩn chứa file nén gzip.

<img width="1152" height="233" alt="image" src="https://github.com/user-attachments/assets/ed890bda-063b-4dc1-9807-7aae9d53214e" />

Đổi tên file (.gz) bằng lệnh mv + giải nén bằng lệnh gunzip.

Giải nén xong bên trong lại chứa dữ liệu nén định dạng lzip, tiếp rồi tới lz4, lzma, lzop ...

<img width="1080" height="76" alt="image" src="https://github.com/user-attachments/assets/79e105dd-ef6f-4ac1-8c0b-b55924af4c1a" />

<img width="1142" height="154" alt="image" src="https://github.com/user-attachments/assets/405c815e-7d0a-48b7-a4df-9533f2cd408c" />

Ta có thể suy ra đây là file bị nén qua hàng chục lớp khác nhau, làm thủ công rất lâu nên nhờ AI viết script tự động chọn công cụ giải nén phù hợp cho đến khi ra chuỗi text hoặc ASCII

Script:
```bash
#!/bin/bash

CURRENT_FILE="next_flag"

while true; do
    FILE_INFO=$(file "$CURRENT_FILE")
    echo "[*] Processing: $FILE_INFO"

    # Nếu tìm thấy chữ picoCTF hoặc ASCII text/Plain text thì dừng lại
    if [[ "$FILE_INFO" == *"ASCII text"* || "$FILE_INFO" == *"text"* ]]; then
        echo "[+] ĐÃ CHẠM ĐẾN ĐÁY!"
        echo "----------------------------------------"
        cat "$CURRENT_FILE"
        echo ""
        echo "----------------------------------------"
        break
    elif [[ "$FILE_INFO" == *"lzip"* ]]; then
        mv "$CURRENT_FILE" "${CURRENT_FILE}.lz"
        lzip -d "${CURRENT_FILE}.lz"
    elif [[ "$FILE_INFO" == *"LZ4"* ]]; then
        lz4 -d "$CURRENT_FILE" "${CURRENT_FILE}_next"
        rm "$CURRENT_FILE"
        CURRENT_FILE="${CURRENT_FILE}_next"
    elif [[ "$FILE_INFO" == *"LZMA"* ]]; then
        mv "$CURRENT_FILE" "${CURRENT_FILE}.lzma"
        unlzma "${CURRENT_FILE}.lzma"
    elif [[ "$FILE_INFO" == *"XZ compressed data"* ]]; then
        mv "$CURRENT_FILE" "${CURRENT_FILE}.xz"
        unxz "${CURRENT_FILE}.xz"
    elif [[ "$FILE_INFO" == *"lzop"* ]]; then
        lzop -d -c "$CURRENT_FILE" > "${CURRENT_FILE}_next"
        rm "$CURRENT_FILE"
        CURRENT_FILE="${CURRENT_FILE}_next"
    elif [[ "$FILE_INFO" == *"gzip"* ]]; then
        mv "$CURRENT_FILE" "${CURRENT_FILE}.gz"
        gunzip "${CURRENT_FILE}.gz"
    elif [[ "$FILE_INFO" == *"bzip2"* ]]; then
        mv "$CURRENT_FILE" "${CURRENT_FILE}.bz2"
        bunzip2 "${CURRENT_FILE}.bz2"
    elif [[ "$FILE_INFO" == *"Zlib"* || "$FILE_INFO" == *"zlib"* ]]; then
        # Nếu gặp zlib compressed data, dùng zlib-flate (nằm trong qpdf) để xả
        zlib-flate -uncompress < "$CURRENT_FILE" > "${CURRENT_FILE}_next"
        rm "$CURRENT_FILE"
        CURRENT_FILE="${CURRENT_FILE}_next"
    elif [[ "$FILE_INFO" == *"tar archive"* ]]; then
        tar -xf "$CURRENT_FILE"
        CURRENT_FILE="flag" 
    else
        echo "[-] Gặp định dạng lạ: $FILE_INFO"
        echo "[*] Hãy thử đọc trực tiếp bằng strings hoặc cat xem sao:"
        strings "$CURRENT_FILE" | grep -i "pico"
        break
    fi
done
```

Kết quả là một chuỗi Hex biểu diễn các kí tự ASCII:
```
7069636f4354467b66316c656e406d335f6d406e3170756c407431306e5f
6630725f3062326375723137795f33633739633562617d0a
```
<img width="2495" height="383" alt="image" src="https://github.com/user-attachments/assets/cb026155-3cd2-48d6-a0cf-33c95dab7537" />

Chuyển chuỗi sang văn bản:

<img width="2817" height="142" alt="image" src="https://github.com/user-attachments/assets/1d9246ca-c1f7-4a5d-a923-399f70d0bfc6" />

Flag: picoCTF{f1len@m3_m@n1pul@t10n_f0r_0b2cur17y_3c79c5ba}

