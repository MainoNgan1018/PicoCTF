## Đề bài:
<img width="1582" height="607" alt="image" src="https://github.com/user-attachments/assets/a9e065ab-9dd6-4607-893e-8581db408822" />

Đầu tiên, ta xem cấu trúc bảng phân vùng của file .dd để biết phân vùng bắt đầu từ đâu.

Command (The Sleuth Kit - TSK trên WSL):
```
mmls image.dd
```
Kết quả:
<img width="918" height="208" alt="Screenshot 2026-06-05 105546" src="https://github.com/user-attachments/assets/731f830f-bd40-4d88-b6f1-1988d788eaba" />
**Phân vùng 1 (Linux - 0x83):**

* Bắt đầu từ Sector: 2048

* Kết thúc ở Sector: 53247

* Độ dài: 51200 sectors.

**Phân vùng 2 (Win95 FAT32 - 0x0b):**

* Bắt đầu từ Sector: 53248

* Kết thúc ở Sector: 118783

* Độ dài: 65536 sectors.

Ta thử sử dụng chiêu quét text:

Command:
```
strings image.dd | grep -i "text"
```
<img width="1076" height="491" alt="image" src="https://github.com/user-attachments/assets/e3e83eb3-0035-4124-8c72-e6fed24f61e0" />

Như ta thấy thì hiện ra hàng loạt các chuỗi flag và ta không biết chuỗi nào mới là thật. Nhưng trên đề bài ghi rõ "The right on is Linux" nghĩa là Flag thật phải nằm ở phân vùng Linux.

Trích xuất phân vùng của Linux thành file riêng để xử lý:

Command:
```
dd if=disko-2.dd of=linux_partition.img bs=512 skip=2048 count=51200
```
Lệnh này sẽ nhảy qua 2048 sectors đầu và chỉ lấy đúng 51200 sectors của Linux để lưu vào file linux_partition.img

<img width="1160" height="94" alt="image" src="https://github.com/user-attachments/assets/88ac3ad4-b89b-413d-9361-d552878e131f" />

Tiếp ra ta sẽ quét chữ "pico" trên file chỉ chứa duy nhất dữ liệu của Linux này:

<img width="1162" height="340" alt="image" src="https://github.com/user-attachments/assets/5909c486-49d3-4277-9847-7c0e7e656872" />

Flag: picoCTF{4_P4Rt_1t_i5_a93c3ba0}
