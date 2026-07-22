Phân tích metadata và xem phổ trên Audacity.

<img width="2170" height="1105" alt="Screenshot 2026-07-21 233536" src="https://github.com/user-attachments/assets/47f2759b-160b-436f-984a-75f965729c77" />

<img width="3782" height="785" alt="Screenshot 2026-07-21 233525" src="https://github.com/user-attachments/assets/789f0331-9deb-48a1-a0f9-94d403d62c80" />

Ta thấy file âm thanh thực chất chỉ là một tần số đơn lẻ kéo dài 1 giây với Sample Rate khá lạ : 2736 Hz.

Phổ hiện một đường ngang phẳng lì vì đây không phải dạng phổ chứa hình ảnh thông thường.

Ta kiểm tra các dạng mã hóa truyền tải dữ liệu qua âm thanh: PSK (Phase Shift Keying) hoặc FSK (Frequency Shift Keying)

Trước tiên thử xem chúng biểu diễn cái gì bằng 1 script Python nhỏ để trích xuất mảng dữ liệu mẫu:
```bash
from scipy.io import wavfile

rate, data = wavfile.read('main.wav')
print(data)  # Xem các giá trị số nguyên của mảng dữ liệu
```
Output:
```
[2002 2507 2001 ... 7502 1001 6009]
```
Quan sát các con số này ta thấy nó dao động theo từng khoảng (quanh mốc 1000, 2000, 7500,...)

Dữ liệu này đã được mã hóa thành các giá trị đại diện cho kí tự Hex.

### Quy luật

Khi cắt bỏ 2 chữ số cuối cùng của mỗi con số trong mảng (coi đó là phần nhiễu nhỏ của biên độ), ta sẽ chỉ còn lại các giá trị đầu. 

Gom tất cả các giá trị sau khi cắt bỏ này và lọc ra, kết quả sẽ trả về đúng 16 giá trị duy nhất.

Vì chỉ có đúng 16 mức giá trị biên độ khác nhau lặp đi lặp lại trong toàn bộ file âm thanh 1 giây đó, người ra đề đã dùng 16 mức biên độ này để đại diện cho 16 ký tự Hex.

Giải mã bằng script `wave.py`

Flag: picoCTF{mU21C_1s_1337_5db6b85e}
