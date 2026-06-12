## Cài đặt bộ công cụ giải mã SSTV (Slow Scan Television)

### Cơ chế và kiến trúc của SSTV

Một bức ảnh SSTV được truyền tải theo nguyên tắc: Quét từ trái sang phải, từ trên xuống dưới. 
```
+------------------+      +-------------------+      +-------------------+      +-------------------+
|   Module Sound   | ---> |    Module DSP     | ---> |   Decoder Logic   | ---> |    Module Image   |
| (Đọc file .wav)  |      | (Biến đổi Fourier)|      | (Bóc tách Pixel)  |      |  (Vẽ ảnh bằng PIL)|
+------------------+      +-------------------+      +-------------------+      +-------------------+
```
```
Khai thác âm thanh thô -> Chuyển đổi âm thanh thành tần số -> Phân tích cú pháp SSTV -> tạo dựng file ảnh đầu ra
```
Ở bước phân tích cú pháp nó sẽ quét tìm VIS Header để tự cấu hình, bài này là chế độ Scottie 1 dựa vào hint 2 ( linh vật của trường CMU là chó Scottie).

Sau đó nó quy đổi tần số thành pixel căn cứ vào thời gian quy định của chế độ và sử dụng công thức nội suy tuyến tính:

$$\text{Giá trị Color} = \frac{(\text{Tần số thực tế} - 1500)}{(2300 - 1500)} \times 255$$

### Cài đặt sstv từ GitHub

**1. Di chuyển về thư mục home của WSL để tải tool**
```
cd ~
```
**2. Clone repository của công cụ sstv về máy**
```
git clone https://github.com/colaclanth/sstv.git
```
**3. Di chuyển vào thư mục sstv vừa tải**
```
cd sstv
```
**4. Cài đặt trực tiếp script này vào hệ thống**
```
sudo python3 setup.py install
```

### Cài thêm libsndfile1 nếu chưa có
```
sudo apt update
sudo apt install -y libsndfile1
```
## Tiến hành giải mã

Di chuyển về thư mục chứa bài tập và chạy lệnh giải mã:
```
sstv -d message.wav -o result.png
```

Lần này tool sẽ nhận diện được driver âm thanh và tiến hành quét từng dòng tín hiệu để vẽ ra file result.png

<img width="2799" height="1534" alt="Screenshot 2026-06-12 162940" src="https://github.com/user-attachments/assets/bb87cec7-2a30-4b75-9b76-df156329c86e" />

Flag: picoCTF{beep_boop_im_in_space}
