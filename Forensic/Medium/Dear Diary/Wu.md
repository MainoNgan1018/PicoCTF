Dùng `mmls + ten_anh_dia` để liệt kê các phân vùng.

<img width="2622" height="500" alt="image" src="https://github.com/user-attachments/assets/10015051-071a-44cc-988e-2ada0244bb78" />

Trích xuất từng phân vùng.

Command line:
```
dd if=[TỆP_NGUỒN] bs=512 skip=[SECTOR_BẮT_ĐẦU] count=[SỐ_SECTOR] of=[TỆP_ĐÍCH]
```

<img width="2782" height="700" alt="image" src="https://github.com/user-attachments/assets/92070c9e-a5f2-4ee5-af99-3a4a09dc1529" />

Phân vùng thứ nhất là của hệ thống, thứ 2 là phân vùng ảo nên ta tập trung vào phân vùng 3.

-------------

>Phân tích về lệnh fls (lệnh của bộ công cụ The Sleuth Kit) và lệnh sudo mount (lệnh của hệ điều hành)

>Fls:

>-Không cần mount đĩa, không cần quyền truy cập hệ thống cao cấp. Mó đọc trực tiếp cấu trúc của file hệ thống (inode, directory entry) ngay trên file ảnh đĩa .img

>-Vì đọc trực tiếp, nó có thể nhìn thấy cả những thứ hệ thống tệp bình thường giấu đi (như các file bị xóa, các file bị ẩn)

>-Tuy nhiên ta không thể copy hay mở trực tiếp file bằng các chương trình thông thường, ta chỉ có thể nhìn thấy danh sách và dùng icat để trích xuất từng file một.

>Sudo mount:

>-Lệnh này yêu cầu hệ điều hành "giả lập phân vùng đĩa đó thành một thư mục thực thụ (như mnt/1). Sau khi mount ta có thể truy cập đĩa như một ổ cứng bình thường.

>-Rất tiện lợi khi ta có thể dùng ls, cat, cp, grep hoặc bất kì trình soạn thảo văn bản nào để xem file.

>-Hạn chế là hệ điều hành chỉ hiện thị những gì nó thấy là hợp lệ, nếu file đã bị xóa hoặc được đánh dấu là không tồn tại, ls sẽ không liệt kê nó ra ngay cả khi dữ liệu vẫn nằm trên đĩa.
----------------

Vì wsl hạn chế quyền mount (quyền này dùng trong máy thật hoặc máy ảo hệ điều hành Linux) nên ta dùng fls:
```
fls -r part3.img
```
<img width="2135" height="515" alt="image" src="https://github.com/user-attachments/assets/988ae310-8011-42f5-9f93-64165da327d4" />
Trích xuất nội dung file.

```
icat part3.img [SỐ_INODE_CỦA_FILE]
```

Nhìn kết quả ta thấy trong `root` có chứa 2 file `secret-secrets` và `ash_history`.

icat kết hợp với xem nội dung hex của từng file, đối với các file trong `secret-secrets` ta lại xem tiếp.

<img width="2530" height="1145" alt="image" src="https://github.com/user-attachments/assets/98bd3230-37d8-44e2-8cf2-0e28e82363f2" />

Các file trong `secret-secrets` không hiển thị gì. Dữ liệu thực tế nằm ở các khối bị xóa (deleted blocks). 

Khi ta icat 1845 (inode của its-all-in-the-name) ta thấy hex dump đó là dữ liệu của thư mục, không phải nội dung file, đó là lý do ta thấy tên các file bên trong.

Vì thế nên ta không dùng icat để lấy file (vì file đã bị xóa nên inode không còn trỏ tới data block hợp kệ nữa)

Ta dùng `hexdump -C` để đọc toàn bộ dữ liệu thô của phân vùng sau đó dùng tính năng `less` để cuộn qua đĩa cứng.

Command line:
```
hexdump -C part3.img | less
```

Gõ `/` và chữ `inno` muốn tìm kiếm.

<img width="2040" height="1397" alt="image" src="https://github.com/user-attachments/assets/167e4521-0e86-4178-947a-171972fe0d5c" />

Nhấn phím `n` để tìm kết quả tiếp theo trong file. Và ta thấy cụm "pic" là 1 phần của flag.

<img width="1947" height="1415" alt="image" src="https://github.com/user-attachments/assets/d4d1cc6d-c954-4329-9854-cec9f675cedc" />

Ta cứ bấm n liên tục để lấy các mảnh flag rồi ghép chúng lại.

<img width="1860" height="220" alt="image" src="https://github.com/user-attachments/assets/38137d25-768f-41a6-be3a-744f962dfa6f" />
<img width="1852" height="270" alt="image" src="https://github.com/user-attachments/assets/1b2482c4-161f-4db7-922a-726a87ebe8a4" />

----------------------------
Cuối cùng tóm tắt ý tưởng của bài này:

Hệ thống tệp (file system) của đề bài đã được làm giả để file có kích thước 0 byte, nhưng thực tế dữ liệu của các file bị xóa đó vẫn còn nằm trên các block (khối dữ liệu) của ổ đĩa.

Ta tìm từ khóa innocuous trong hexdump, không tìm tên file, mà ta đang tìm dấu vết của nội dung tệp tin cũ nằm ngay tại các sector mà hệ điều hành cũ đã từng ghi.

Tác giả bài này đã tạo file innocuous-file.txt lần 1 với 1 phần flag -> xóa... Cứ như thế, các phần của flag nằm rải rác ở các vị trí khác nhau trên đĩa, ngay gần các sector mà thư mục lưu trữ tên file đó.

Flag: picoCTF{1_533_n4m35_80d24b30}
