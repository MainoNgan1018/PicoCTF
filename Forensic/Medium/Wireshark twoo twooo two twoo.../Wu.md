Vào Wireshark dùng chế độ tìm kiếm (bấm vào kính lúp trên thanh công cụ kí hiệu hoặc tổ hợp phím Ctrl + F)

Tìm được rất nhiều chuỗi có dạng picoCTF{..} chứa mã hash trong các gói tin HTTP và đây chỉ là thông tin gây nhiễu.

<img width="2835" height="1480" alt="image" src="https://github.com/user-attachments/assets/92e9da62-874c-4dcd-84c2-7f4d491401bb" />

<img width="1672" height="630" alt="Screenshot 2026-07-17 102751" src="https://github.com/user-attachments/assets/923b17a9-1010-4ce3-bfee-7bd1815e745d" />

Flag thực sự không nằm trong các gói tin HTTP mà được giấu trong lưu lượng DNS. Vì tôi lướt sơ qua và thấy hàng loạt các truy vấn DNS gửi đến các tên miền có dạng:

>[chuỗi_base64].reddshrimpandherring.com.

<img width="2860" height="1637" alt="Screenshot 2026-07-17 103722" src="https://github.com/user-attachments/assets/09c3c0bd-25a9-4ebd-88be-889ed26d2345" />

Sử dụng lệnh `tshark` để trích xuất nhanh các subdomain này:
```
tshark -r shark2.pcapng -T fields -e dns.qry.name | grep "reddshrimpandherring.com" | cut -d'.' -f1 > ordered_data.txt
```
Theo kinh nghiệm làm bài của tôi thì chữ picoCTF sang base64 bắt đầu từ `cGlj...` và kết thúc bằng `fQ==` nên tôi cop từ đó đến hết.

Kết quả là ra toàn kí tự lạ cho thấy các mảnh đang bị sắp xếp sai thứ tự.

<img width="1495" height="1465" alt="Screenshot 2026-07-17 110043" src="https://github.com/user-attachments/assets/7c9b5c22-085b-4183-ab2e-badafa8ef330" />

Sau đó tôi đi tìm gói có mảnh đầu tiên là bằng cách tìm kiếm theo chuỗi base64:

<img width="2865" height="1480" alt="image" src="https://github.com/user-attachments/assets/57fcb1b2-8aeb-4cbc-bda4-fead0d3e049e" />

Và gói tiếp theo phải bắt đầu là cụm `Rnt..`, tại sao tôi biết vì tôi dịch ngược định dạng cờ từ `picoCTF{` sang chuỗi base64 từ đó suy ra mảnh tiếp theo.

Ta thấy gói chứa mảnh đầu được gửi đến ip `18.217.1.57` nên ta sẽ filter thêm điều kiện này.

<img width="2845" height="1585" alt="image" src="https://github.com/user-attachments/assets/01739ca3-e642-46a6-9063-ed9e8a97fa86" />

Và gói tiếp theo đúng như dự đoán nên khả năng chỉ cần lấy theo lần lượt sẽ ra flag hoàn chỉnh.

<img width="1780" height="1157" alt="image" src="https://github.com/user-attachments/assets/1e39fcf2-4911-44f1-8b96-0a0cc87abd11" />

Nhìn wireshark và tìm cụm trong file `order_data.txt` mà ta đã trích xuất để lấy lần lượt.

<img width="1990" height="1255" alt="image" src="https://github.com/user-attachments/assets/342217a5-a7a7-47a9-9a9d-0983b066a0a5" />


Flag: picoCTF{dns_3xf1l_ftw_deadbeef}
