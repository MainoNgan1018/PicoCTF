Bài này đầu tiên binwalk thì ta phát hiện có file zlib nén , header 78 9C là Magic Number của zlib nhưng kết thúc bằng IEND.

<img width="1970" height="315" alt="image6" src="https://github.com/user-attachments/assets/dd5e232c-3beb-42cb-a39b-af37b6294205" />

Sau đoạn phân tích khá lạc hướng tập trung vào file nén này thì mình đã tìm hiểu được một vài thứ, tại trước đây mình cũng từng làm 1 bài không nhớ là file ảnh nào (khả năng cũng là png) nhưng mà nó cũng kiểu có 1 file nén mà không quan trọng:

* Một file PNG có thể có nhiều IDAT (chủ yếu là để xử lý dữ liệu theo từng khối). Quy tắc các chunk IDAT phải nằm cạnh nhau và dữ liệu bên trong chunk bắt buộc phải được nén
* PNG sử dụng thuật toán nén Deflate và cấu trúc của khối dữ liệu nén này chính là zlib để giảm dung lượng tối thiểu mà không làm mất chất lượng (nếu không nén có thể nặng vài mb thay vì vài trăm kb)
* Vì vật khi binwalk một file PNG chuẩn ta sẽ luôn thấy thông báo về Zlib compressed data , đó là dữ liệu hình ảnh thật
* Còn nếu có file zlib không bình thường thì file đó phải ở 1 offset như kiểu nằm sau IEND , kích thước quá lớn
* Trong bài này thì dữ liệu zlib là dữ liệu nén của 1 màu đỏ thuần , và cụm từ đi kèm default compression chỉ mức độ nén cân bằng ( mức 6 trong thang 0-9) , ( 78 01 : low/no compression, 78 DA : best compression)

Vì đây là ảnh nguyên màu đỏ nên nó rất có khả năng bị sửa ở lsb vì mắt thường khó nhận dạng.

Sử dụng tool zsteg
Cơ chế hoạt động của zsteg:
### 1-Quét qua các plane màu

> zsteg sẽ tách ảnh thành 24 lớp bit khác nhau (8 bit R + 8 bit G + 8 bit B), nó kiểm tra từ bit có trọng số thấp nhất đến cao nhất

### 2-Thử các tổ hợp sắp xếp

Dữ liệu có thể giấu theo nhiều cách:

> Pixel order: giấu theo hàng ngang (x,y) hoặc theo hàng dọc (y,x)

> Bit order: giấu từ bit cao đến thấp hoặc thấp đến cao

> Thử theo các kiểu bù trừ byte khác nhau

### 3-Nhận diện chữ kí số

> Sau khi trích xuất dữ liệu thô từ các lớp bit, nó chạy một bộ lọc nhận diện xem dữ liệu có bắt đầu bằng các chuỗi quen thuộc không

Sau khi dùng zsteg thì ta thấy ở loạt dữ liệu liệt kê ra có dạng văn bản base64 

<img width="1845" height="1045" alt="image14" src="https://github.com/user-attachments/assets/4f71a625-6c3a-4f79-8a2c-7b646b777268" />

Giải mã chuỗi: 

<img width="1855" height="145" alt="image11" src="https://github.com/user-attachments/assets/7d391aa4-7a50-4248-81ae-f922d20576d2" />

Flag: picoCTF{r3d_1s_th3_ult1m4t3_cur3_f0r_54dn355_}
