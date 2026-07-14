APK là viết tắt của Android Package Kit. Đây là định dạng tệp cài đặt (tương tự như tệp .exe trên Windows) được hệ điều hành Android sử dụng để phân phối và cài đặt các ứng dụng hoặc trò chơi.

Như gợi ý đã nêu file .apk về cơ bản là một file nén. Ta giải nén bằng lệnh `unzip`:

<img width="2237" height="655" alt="image" src="https://github.com/user-attachments/assets/21d4b6a4-fe5f-4ac5-a611-d3be2dc113b5" />

<img width="1730" height="917" alt="image" src="https://github.com/user-attachments/assets/11d617da-85bd-468a-9745-57d27b534de4" />

Nhìn ra trong đó có chứa flag.txt, dùng lệnh find để tìm đường dẫn đến file này:
```
find . -name "flag.txt"
```
<img width="2047" height="245" alt="image" src="https://github.com/user-attachments/assets/7fcba52d-3c39-40e8-8e20-323c024dd146" />

Xem nội dung bằng lệnh `cat` và kết quả là một mã Hex của flag. 
```
7069636f4354467b6178386d433052553676655f4e5838356c346178386d436c5f37343664666133397d
```
Chuyển nó sang dạng văn bản:

Cho lên CyberChef

<img width="2147" height="1187" alt="image" src="https://github.com/user-attachments/assets/643def6a-c5aa-4217-b792-c156dd23151a" />

Hoặc dùng lệnh:
```
echo "7069636f4354467b6178386d433052553676655f4e5838356c346178386d436c5f37343664666133397d" | xxd -r -p
```
Flag: picoCTF{ax8mC0RU6ve_NX85l4ax8mCl_746dfa39}
