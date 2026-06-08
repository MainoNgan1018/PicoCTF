Khi tra các option của binwalk, tôi phát hiện ra option quét đệ quy, xong tôi nhớ đến bài này và áp dụng thử nhưng không được.

Binwalk bị lỗi ở lớp thứ 2: vì khi giải nén lớp đầu tiên, file con sinh ra luôn bị tác giả cố định đặt tên là flag hoặc gì đó và không hề có file mở rộng.

Mà binwalk hoạt động dựa trên phần mở rộng hệ thống để gọi công cụ giải nén tương tự nên khi không có nó không biết dẫn đến lỗi cảnh báo.

### **Các option :**

```
-e (extract): tự động bóc tách file nó thấy trong quá trình quét.
-M (matryoshka): quét đệ quy. Tức là sau khi giải nén ra file con, nó sẽ lao vào quét và giải nén các file con bên trong file con đó ( giống búp bê Nga ) .Thường đi kèm với -e
-B (signature): quét tìm chữ kí file
-W (hexdump): thực hiện so sánh Hex dump của nhiều file hoặc hiển thị phần thay đổi.
```
